/* client.c */
#include "function.h"

#define OURPORT 8088

gint sd; //套接字句柄
struct sockaddr_in s_in; //套接字数据结构
gchar username[64]; //用户名
gchar buf[MAX_LEN]; //写缓冲区
gchar get_buf[MAX_LEN]; //读缓冲区
gboolean isconnected = FALSE; //定义逻辑值表示是否连接

static GtkWidget *text;
static GtkWidget *path_text;
static GtkTextBuffer *buffer; //显示对话内容的文本显示缓冲区
static GtkWidget *message_entry; //显示输入消息的单行录入控件
static GtkWidget *name_entry; //输入用户名的单行录入控件
static GtkWidget *login_button; //登录按钮
static GtkWidget *target_entry;

GtkTextBuffer *file_buffer;
GtkWidget *path_entry;
char *file_path;

void sys_err(const char *ptr,int num)
{
    perror(ptr);
    exit(num);
}

void get_message()
{
	GtkTextIter iter;
	gchar get_buf[MAX_LEN];
	gchar buf[MAX_LEN];
	
	char mod;

	while(read(sd, buf, MAX_LEN) != -1) //只要读取数据成功就循环执行
	{
		printf("%s\n", buf);
		mod = buf[0];
		if (mod == '1')
		{
			g_print("%s", buf + 2);
			sprintf(get_buf, "%s", buf + 2);
			gdk_threads_enter(); //进入
			gtk_text_buffer_get_end_iter(buffer, &iter);
			gtk_text_buffer_insert(buffer, &iter, get_buf, -1);
			memset(buf, 0, sizeof(buf));
			gdk_threads_leave();
		}
		else if (mod == '2')
		{
			printf("download\n");
			download_file(buf);
		}
	}
}

gboolean do_connect() //连接多人聊天服务器
{
	GtkTextIter iter;
	gint slen;
	sd = socket(AF_INET,SOCK_STREAM,0);//创建
	if (sd < 0)
	{
		gtk_text_buffer_get_end_iter(buffer, &iter);
		gtk_text_buffer_insert(buffer, &iter, "打开套接字时出错！\n", -1);
		return FALSE;
	}
	
	memset(&s_in, 0, sizeof(s_in));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(OURPORT);
	s_in.sin_addr.s_addr = inet_addr("192.168.153.135");
	slen = sizeof(struct sockaddr_in);
	
	if (connect(sd, (struct sockaddr*)&s_in, slen) < 0)
	{
		gtk_text_buffer_get_end_iter(buffer, &iter);
		gtk_text_buffer_insert(buffer, &iter, "连接服务器时出错！\n",-1);
		return FALSE;
	}
	else
	{
		gtk_text_buffer_get_end_iter(buffer, &iter);
		gtk_text_buffer_insert(buffer, &iter, username, -1);
		gtk_text_buffer_get_end_iter(buffer, &iter);
		gtk_text_buffer_insert(buffer, &iter, "\n成功与服务器连接....\n", -1);
		
		gchar temp[64];
		memset(temp, 0, sizeof(temp));
		strcpy(temp, username);
		write(sd, temp, 64);//向服务器发送用户名

		isconnected = TRUE;
		return TRUE;
	}
}

void on_destroy(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	sprintf(username, "guest");

	if(do_connect() == TRUE)
	{
		gtk_widget_set_sensitive(login_button, FALSE);
		g_thread_new(username, (GThreadFunc)get_message, NULL);

	}
	gtk_widget_destroy(widget);
}

void on_button_clicked(GtkButton *button, gpointer data)
{
	const gchar* name;
	const gchar* tar;

	name = gtk_entry_get_text(GTK_ENTRY(name_entry));
	sprintf(username, "%s", name);

	//tar = gtk_entry_get_text(GTK_ENTRY(target_entry));
	// if (strcmp(tar, "") == 0)
	// {
	// 	sprintf(target, "%s", "ALL");
	// }
	// else
	// {
	// 	sprintf(target, "%s", tar);
	// }

	if(do_connect())
	{
		gtk_widget_set_sensitive(login_button, FALSE);
		g_thread_new(username, (GThreadFunc)get_message, NULL);
	}
	gtk_widget_destroy(data);
}

void get_file()
{
	int fd = open(file_path, O_RDONLY);
	char buf[MAX_LEN + 64];
	if (fd < 0)
	{
		sys_err("open", -3);
	}

	const char* target;
	target = gtk_entry_get_text(GTK_ENTRY(target_entry));

	while (1)
	{
		memset(buf, 0, sizeof(buf));
		int len = read(fd, buf, sizeof(char) * MAX_LEN);

		if (len == 0) break;	//读取出错

		char *temp = NULL;
		temp = (char*)malloc(sizeof(char) * MAX_LEN + 64);
		memset(temp, 0, sizeof(temp));

		strcpy(temp, "2:");
		strcat(temp, target);
		strcat(temp, ";");
		strcat(temp, buf);
		len = len + strlen(target) + 3;

		// 考虑一次没读完
		int _tmp = 0;
		while (1)
		{
			int ret = write(sd, temp + _tmp, len - _tmp);
			if (ret > 0)
			{
				_tmp += ret;
			}
			if (_tmp == ret)
			{
				break;
			}
			if (ret < 0)
			{
				perror("write");
				break;
			}
		}

		if (temp != NULL)
		{
			free(temp);
			temp = NULL;
		}
	}
}

void download_file(gchar buf[])
{
	int filefd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	write(filefd, buf + 2, strlen(buf) - 2);
	close(filefd);
}

void on_send_file_click()
{
	printf("%s\n", file_path);
	get_file();
}

void create_win()
{
	GtkWidget *win, *vbox, *hbox, *hbox1;
	GtkWidget *button, *login_name;

	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(win), "输入用户名");
	gtk_container_set_border_width(GTK_CONTAINER(win),10);
	g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(on_destroy), NULL);
	gtk_window_set_modal(GTK_WINDOW(win), TRUE);
	gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(win), vbox);
	
	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 5);

	login_name = gtk_label_new("用  户  名： ");
	gtk_box_pack_start(GTK_BOX(hbox), login_name, TRUE, TRUE, 5);

	name_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox), name_entry, TRUE, TRUE, 5);
	
	// hbox1 = gtk_hbox_new(FALSE, 0);
	// gtk_box_pack_start(GTK_BOX(vbox), hbox1, TRUE, TRUE, 5);

	// target_name = gtk_label_new("聊天目标：");
	// gtk_box_pack_start(GTK_BOX(hbox1), target_name, TRUE, TRUE, 5);

	// target_entry = gtk_entry_new();
	// gtk_box_pack_start(GTK_BOX(hbox1), target_entry, TRUE, TRUE, 5);

	button = gtk_button_new_from_stock(GTK_STOCK_OK);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_clicked), win);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE,5);

	gtk_widget_show_all(win);
}

void on_send (GtkButton* button, gpointer data)
{
	const char* message;
	const char* target;
	if(isconnected == FALSE) return;
	
	message = gtk_entry_get_text(GTK_ENTRY(message_entry));
	target = gtk_entry_get_text(GTK_ENTRY(target_entry));

	memset(buf, 0, sizeof(buf));
	strcpy(buf, "1:");
	strcat(buf, target);
	strcat(buf, ";");
	strcat(buf, message);

	write(sd, buf, MAX_LEN);//发送
	gtk_entry_set_text(GTK_ENTRY(message_entry), "");
}

void on_login(GtkWidget *button, gpointer data)
{ 
	create_win();
}

void on_delete_event (GtkWidget *widget, GdkEvent* event, gpointer data)
{
	strcpy(buf, "0:CONNECT_CLOSE");
	write(sd, buf, MAX_LEN);
	close(sd);//关闭
	gtk_main_quit();
}

int main (int argc, char* argv[])
{
	GtkWidget *window;
	GtkWidget *vbox, *hbox, *hbox1, *hbox2, *button, *button2, *label, *label1, *label2, *view;

	gtk_init(&argc,&argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "客户端");
	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(on_delete_event), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);
	label = gtk_label_new("点击登录按钮连接服务器");
	gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 5);
	login_button = gtk_button_new_with_label("登录");
	gtk_box_pack_start(GTK_BOX(hbox), login_button, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(on_login), NULL);

	view = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	text = gtk_text_view_new();
	gtk_box_pack_start(GTK_BOX(vbox),view,TRUE,TRUE,5);
	gtk_container_add(GTK_CONTAINER(view),text);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));

	hbox1 = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, FALSE, 5);

	label1 = gtk_label_new("发送目标：");
	gtk_box_pack_start(GTK_BOX(hbox1), label1, FALSE, FALSE, 5);

	// target_entry不动
	target_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox1), target_entry, FALSE, FALSE, 5);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);

	label = gtk_label_new("输入消息：");
	gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 5);

	// message_entry不动
	message_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox), message_entry, FALSE, FALSE, 5);

	// button不动
	button = gtk_button_new_with_label("发送消息");
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_send), NULL);

	hbox2 = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 5);

	label2 = gtk_label_new("文件路径：");
	gtk_box_pack_start(GTK_BOX(hbox2), label2, FALSE, FALSE, 5);

	// path_entry不动
	// path_entry = gtk_entry_new();
	// gtk_box_pack_start(GTK_BOX(hbox2), path_entry, FALSE, FALSE, 5);
	GtkWidget *button3;
	button3 = gtk_button_new_with_label("选择文件");
	gtk_box_pack_start(GTK_BOX(hbox2), button3, FALSE, FALSE, 5);
	g_signal_connect_swapped(G_OBJECT(button3), "clicked", G_CALLBACK(File_button_clicked), NULL);

	// button2不动
	button2 = gtk_button_new_with_label("发送文件");
	gtk_box_pack_start(GTK_BOX(hbox2), button2, FALSE, FALSE, 5);
	g_signal_connect_swapped(G_OBJECT(button2), "clicked", G_CALLBACK(on_send_file_click), NULL);

	//GtkWidget *file_text = gtk_scrolled_window_new(NULL,NULL);

	// 这里显示文件目录（未做） 怎么接受另一个函数结束信号
	path_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(vbox), path_entry, FALSE, FALSE, 5);

	gtk_widget_show_all(window);

	gdk_threads_enter();
	gtk_main();
	gdk_threads_leave();
	
	return FALSE;
}
