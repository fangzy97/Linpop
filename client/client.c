/********************************************************************************
 * Files         : client.c
 * Description   : 该模块为客户端主界面，所有功能围绕它展开
 ********************************************************************************/
#include "function.h"

#define OURPORT 8088
#define M_IP "127.0.0.1"

gint sd; //套接字句柄
struct sockaddr_in s_in; //套接字数据结构
gchar username[64]; //用户名
gchar password[64]; //密码
gchar buf[MAX_LEN]; //写缓冲区
gchar get_buf[MAX_LEN]; //读缓冲区
gboolean isconnected = FALSE; //定义逻辑值表示是否连接

GtkWidget *main_window;
static GtkWidget *text;
static GtkWidget *path_text;
//static GtkTextBuffer *buffer; //显示对话内容的文本显示缓冲区
static GtkWidget *message_entry; //显示输入消息的单行录入控件
static GtkWidget *name_entry; //输入用户名的单行录入控件
static GtkWidget *password_entry; //输入用户名的单行录入控件
static GtkWidget *login_button; //登录按钮
// static GtkWidget *target_entry;

GtkTextBuffer *file_buffer;
GtkWidget *path_entry;
char *file_path;

int isSet;
struct info p_info;

void sys_err(const char *ptr,int num)
{
    perror(ptr);
    exit(num);
}

/* 
    名称：on_okclicked
    描述：该函数用于读取服务器发送的信息
    做成日期：18/09/05
    参数：gpointer data传入的需要操作的界面
    返回值：void
    作者：方致远
*/
void get_message(gpointer data)
{
	GtkTextIter iter;
	gchar get_buf[MAX_LEN];
	gchar buf[MAX_LEN];
	
	char mod;
	int flag;

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
			new_folder(username, get_buf);
			memset(buf, 0, sizeof(buf));
			gdk_threads_leave();
		}
		else if (mod == '2')
		{
			printf("download\n");
			download_file(buf);
		}
		else if (mod == '3')
		{
			flag = (int)(buf[2] - '0');
			
			if (flag == 0)
			{
				GtkWidget *dialog;
				gchar message[64];
				sprintf(message, "用户名或密码错误");

				dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, 
					GTK_MESSAGE_INFO, GTK_BUTTONS_OK, message, NULL);

				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog);
			}
			else
			{
				gtk_widget_destroy(data);
				// 启动主界面
				create_main();
			}
		}
	}
}

/* 
    名称：do_connect
    描述：该函数用于读取服务器发送的信息
    做成日期：18/09/05
    参数：void
    返回值：void
    作者：方致远
*/
gboolean do_connect() //连接多人聊天服务器
{
	GtkTextIter iter;
	gint slen;
	sd = socket(AF_INET,SOCK_STREAM,0);//创建
	if (sd < 0)
	{
		printf("打开套接字时出错！\n");
		// gtk_text_buffer_get_end_iter(buffer, &iter);
		// gtk_text_buffer_insert(buffer, &iter, "打开套接字时出错！\n", -1);
		return FALSE;
	}
	
	memset(&s_in, 0, sizeof(s_in));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(OURPORT);
	s_in.sin_addr.s_addr = inet_addr(M_IP);
	slen = sizeof(struct sockaddr_in);
	
	if (connect(sd, (struct sockaddr*)&s_in, slen) < 0)
	{
		printf("连接服务器时出错！\n");
		// gtk_text_buffer_get_end_iter(buffer, &iter);
		// gtk_text_buffer_insert(buffer, &iter, "连接服务器时出错！\n",-1);
		return FALSE;
	}
	else
	{
		// gtk_text_buffer_get_end_iter(buffer, &iter);
		// gtk_text_buffer_insert(buffer, &iter, username, -1);
		// gtk_text_buffer_get_end_iter(buffer, &iter);
		// gtk_text_buffer_insert(buffer, &iter, "\n成功与服务器连接....\n", -1);
		printf("成功与服务器连接....\n");
		
		gchar temp[128];
		memset(temp, 0, sizeof(temp));
		strcpy(temp, username);
		strcat(temp, ";");
		strcat(temp, password);

		write(sd, temp, 64);//向服务器发送用户名

		isconnected = TRUE;
		return TRUE;
	}
}

void on_destroy(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	sprintf(username, "guest");
	sprintf(password, " ");

	if(do_connect() == TRUE)
	{
		g_thread_new(username, (GThreadFunc)get_message, NULL);

	}
	gtk_widget_destroy(widget);
}

/* 
    名称：on_button_clicked
    描述：读取用户名和密码并尝试连接到服务器
    做成日期：18/09/05
    参数：GtkButton *button被点击按钮, gpointer data传输数据
    返回值：void
    作者：方致远
*/
void on_button_clicked(GtkButton *button, gpointer data)
{
	const gchar* name;
	const gchar* pw;

	name = gtk_entry_get_text(GTK_ENTRY(name_entry));
	sprintf(username, "%s", name);

	pw = gtk_entry_get_text(GTK_ENTRY(password_entry));
	sprintf(password, "%s", pw);

	if (strcmp(username, "1") != 0 && strcmp(username, "2") != 0 && strcmp(username, "3") != 0)
	{
		login_stats(1);
	}
	else
	{
		if (strcmp(password, "123") != 0)
		{
			login_stats(2);
		}
		else
		{
			if(do_connect())
			{
				g_thread_new(username, (GThreadFunc)get_message, data);
				gtk_widget_destroy(data);
				// 启动主界面
				create_main();
			}
			else
			{
				GtkWidget *dialog;
				gchar message[64];
				sprintf(message, "无法连接到服务器");

				dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, 
					GTK_MESSAGE_INFO, GTK_BUTTONS_OK, message, NULL);

				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog);
			}
		}
	}
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
		// printf("文件指针位置为：%ld\n", lseek(fd, 0, SEEK_CUR));
		printf("%s", buf);
		
		if (len <= 0) break;	//读取出错
	
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
	printf("读取结束\n");
}

void download_file(gchar buf[])
{
	int filefd = open("file.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);
	write(filefd, buf + 2, strlen(buf) - 2);
	close(filefd);

	GtkTextIter iter;
	gtk_text_buffer_get_end_iter(buffer, &iter);
	gtk_text_buffer_insert(buffer, &iter, "文件传输完成", -1);		
}

void on_send_file_click()
{
	if (file_path != NULL)
	{
		printf("%s\n", file_path);
		get_file();
	}
	else
	{
		GtkWidget *dialog;
		gchar message[64];
		memset(message, 0, sizeof(message));
		sprintf(message, "请选择文件！");

		dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, 
        	GTK_MESSAGE_INFO, GTK_BUTTONS_OK, message, NULL);

		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
}

void create_register()
{
	GtkWidget *register_win;
	register_win = create_test_window();
	gtk_widget_show_all(register_win);
}

void create_win(gpointer data)
{
	GtkWidget *win, *vbox, *hbox, *hbox1, *hbox2;
	GtkWidget *button, *login_name, *password, *target_name;

	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(win), "输入用户名");
	gtk_container_set_border_width(GTK_CONTAINER(win),10);
	g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(on_destroy), NULL);
	gtk_window_set_modal(GTK_WINDOW(win), TRUE);
	gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(win), vbox);
	
	GtkWidget *image_one = gtk_image_new_from_file("login.gif");
	gtk_container_add(GTK_CONTAINER(vbox), image_one);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 5);
	hbox2 = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox2, TRUE, TRUE, 5);

	login_name = gtk_label_new("用  户  名： ");
	gtk_box_pack_start(GTK_BOX(hbox), login_name, TRUE, TRUE, 5);

	name_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox), name_entry, TRUE, TRUE, 5);

	password = gtk_label_new("密         码： ");
	gtk_box_pack_start(GTK_BOX(hbox2), password, TRUE, TRUE, 5);

	password_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox2), password_entry, TRUE, TRUE, 5);
	gtk_entry_set_visibility(GTK_ENTRY(password_entry),FALSE);

	GtkWidget *button_box;
	button_box = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), button_box, TRUE, TRUE, 5);

	button = gtk_button_new_from_stock(GTK_STOCK_OK);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_clicked), win);
	gtk_box_pack_start(GTK_BOX(button_box), button, TRUE, TRUE,5);

	GtkWidget *register_button;
	register_button = gtk_button_new_with_label("register");
	gtk_box_pack_start(GTK_BOX(button_box), register_button, TRUE, TRUE, 5);
	g_signal_connect(G_OBJECT(register_button), "clicked", G_CALLBACK(create_register), NULL);

	gtk_widget_show_all(win);
	gtk_widget_destroy(data);
}

void on_send (GtkButton* button, gpointer data)
{
	const char* message;
	const char* target;
	GtkTextIter start, end;

	if(isconnected == FALSE) return;

	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(input_buffer), &start, &end);
	message = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(input_buffer), &start, &end, FALSE);

	gtk_text_buffer_set_text(input_buffer, "", 0);

	target = gtk_entry_get_text(GTK_ENTRY(target_entry));

	char *buf = (char*)malloc(sizeof(char) * MAX_LEN);
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
	create_win(data);
}

void on_delete_event (GtkWidget *widget, GdkEvent* event, gpointer data)
{
	strcpy(buf, "0:CONNECT_CLOSE");
	write(sd, buf, MAX_LEN);
	close(sd);//关闭
	gtk_main_quit();
}

int create_main ()
{
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(main_window), "客户端");
	g_signal_connect(G_OBJECT(main_window), "delete_event", G_CALLBACK(on_delete_event), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(main_window), 10);
	gtk_window_set_default_size(GTK_WINDOW(main_window),1000,800);

	// 笔记本控件
	GtkWidget *notebook = gtk_notebook_new();
	gtk_container_add(GTK_CONTAINER(main_window), notebook);

	//4.页标签的位置，可以有四种位置：上、下、左或右
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);//上面

	//5.创建一个水平布局
	GtkWidget *hbox = gtk_hbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(main_window), hbox);

	//第一个页面
	//第一个页面的label
	GtkWidget *label = gtk_label_new("会话窗口");
	//创建主盒子
	GtkWidget *main_box = gtk_hbox_new(TRUE, 5); 
	//把主盒子装入notebook的第一页，并设以label.
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), main_box, label);
	//创建水平分割面板
	GtkWidget *hpaned = gtk_hpaned_new();
	//水平分割面板装入总盒子
	gtk_box_pack_start(GTK_BOX(main_box), hpaned, TRUE, TRUE, 0);

	//左，右盒子分别装入水平分割面板
	gtk_paned_pack1(GTK_PANED(hpaned),create_leftbox(),FALSE,FALSE);
	gtk_paned_pack2(GTK_PANED(hpaned),create_rightbox(),FALSE,FALSE);

	//7.第二个页面
	label = gtk_label_new("功能窗口");
	GtkWidget *vbox = gtk_vbox_new(TRUE, 5);
	GtkWidget *hbox1, *hbox2, *hbox3;
	GtkWidget *personal_information_button, *calc_button, *cale_button, *button4, *button5, *button6;

	personal_information_button= gtk_button_new_with_label("个性化设置");
	g_signal_connect(G_OBJECT(personal_information_button),"clicked",G_CALLBACK(personal_information_button_clicked),NULL);
	calc_button= gtk_button_new_with_label("计算器");
	g_signal_connect(G_OBJECT(calc_button),"clicked",G_CALLBACK(calc_button_clicked),NULL);
	cale_button= gtk_button_new_with_label("日历");
	g_signal_connect(G_OBJECT(cale_button),"clicked",G_CALLBACK(cale_button_clicked),NULL);

	hbox1=gtk_hbox_new(TRUE, 5);
	hbox2=gtk_hbox_new(TRUE, 5);
	hbox3=gtk_hbox_new(TRUE, 5);

	button4= gtk_button_new_with_label("三角点格棋");
	// g_signal_connect(G_OBJECT(button4),"clicked",G_CALLBACK(open_chess),NULL);

	button5= gtk_button_new_with_label("5");
	button6= gtk_button_new_with_label("6");

	gtk_box_pack_start(GTK_BOX(vbox), hbox1,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox2,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox3,TRUE,TRUE,0);

	gtk_box_pack_start(GTK_BOX(hbox1), personal_information_button,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox1), calc_button,TRUE,TRUE,0);

	gtk_box_pack_start(GTK_BOX(hbox2), cale_button,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox2), button4,TRUE,TRUE,0);

	gtk_box_pack_start(GTK_BOX(hbox3), button5,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox3), button6,TRUE,TRUE,0);
 
 
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);

/*
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(main_window), vbox);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);

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
*/
	gtk_widget_show_all(main_window);
	
	return FALSE;
}

void initialize()
{
	p_info.name=(gchar*)malloc(30*sizeof(gchar));
	p_info.sex=(gchar*)malloc(30*sizeof(gchar));
	p_info.age=(gchar*)malloc(30*sizeof(gchar));
	p_info.signature=(gchar*)malloc(30*sizeof(gchar));
	// p_info.year=(gchar*)malloc(30*sizeof(gchar));
	// p_info.month=(gchar*)malloc(30*sizeof(gchar));
	// p_info.date=(gchar*)malloc(30*sizeof(gchar));

	sprintf(p_info.name,"设置您的姓名");
	sprintf(p_info.sex,"设置您的性别");
	sprintf(p_info.age,"设置您的年龄");
	sprintf(p_info.signature,"设置您的个性签名");
	// sprintf(p_info.year,"1900");
	// sprintf(p_info.month,"1");
	// sprintf(p_info.date,"1");
	p_info.year = 1900;
	p_info.month = 1;
	p_info.date = 1;

	isSet = 0;
}

int main (int argc, char* argv[])
{
	initialize();

	file_path = NULL;

	GtkWidget *window;
	GtkWidget *vbox, *vbox1,*vbox2,*vbox3,*hbox, *hbox1, *hbox2, *hbox3;
	GtkWidget *button, *button2, *label, *label1, *label2,*label3, *view;

	gtk_init(&argc,&argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "客户端");
	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(on_delete_event), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	GtkWidget *image_one = gtk_image_new_from_file("image2.png");
	gtk_container_add(GTK_CONTAINER(vbox), image_one);

	hbox = gtk_hbox_new(FALSE, 0);
	hbox3 = gtk_hbox_new(FALSE, 0);
	vbox1 = gtk_vbox_new(FALSE, 0);
	vbox2 = gtk_vbox_new(FALSE, 0);
	vbox3 = gtk_vbox_new(FALSE, 0);

	label3 = gtk_label_new("NINE ver1.0");
	gtk_box_pack_start(GTK_BOX(vbox3), label3, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), vbox3, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);

	label = gtk_label_new("点击登录按钮连接服务器");
	gtk_box_pack_start(GTK_BOX(vbox1), label, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), vbox1, FALSE, FALSE, 5);

	login_button = gtk_button_new_with_label("登录");
	gtk_box_pack_start(GTK_BOX(vbox2), login_button, TRUE, FALSE, 5);

	//this function is linked to the login window	
	g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(on_login), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), vbox2, FALSE, FALSE, 5);

	gtk_widget_show_all(window);

	gdk_threads_enter();
	gtk_main();
	gdk_threads_leave();

	return 0;
}