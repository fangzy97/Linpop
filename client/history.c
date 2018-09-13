/********************************************************************************
 * Files         : history.c
 * Description   : 该模块用于查看聊天记录
 ********************************************************************************/
#include "function.h"

/* 
    名称：insert_history
    描述：该函数用于从文件中读取历史纪录
    做成日期：18/09/06
    参数：GtkTextBuffer *history_buffer
    返回值：void
    作者：方致远
*/
void insert_history(GtkTextBuffer *history_buffer)
{
    char *home = getenv("HOME");

    char path[64];
    char buf[MAX_LEN];

    memset(path, 0, sizeof(path));
    strcpy(path, home);
    strcat(path, "/");
    strcat(path, username);
    strcat(path, "/");
    strcat(path, username);
    strcat(path, ".txt");

    printf("%s\n", path);

    int fd = open(path, O_RDONLY, O_CREAT, 0777);
    int len = 0;
    GtkTextIter start, end;

    if (fd != -1)
    {
        memset(buf, 0, sizeof(buf));
        len = read(fd, buf, MAX_LEN);
        if (len > 0)
        {
            gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(history_buffer), &start, &end);
            gtk_text_buffer_insert(history_buffer, &end, buf, strlen(buf));
        }
        else
        {
            printf("读取错误\n");
        }
    }
    else
    {
        printf("打开文件错误\n");
    }
}

/* 
    名称：create_history
    描述：该函数用于建立显示聊天记录的窗口
    做成日期：18/09/06
    参数：void
    返回值：void
    作者：方致远
*/
void create_history()
{
	GtkWidget *win, *hbox, *text;
	GtkTextBuffer *history_buffer;

	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(win), "聊天记录");
	gtk_container_set_border_width(GTK_CONTAINER(win),10);
	g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(on_destroy), NULL);
	gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(win),800,600);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(win), hbox);

	GtkWidget *scwin = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(hbox), scwin, TRUE, TRUE, 5);

	text = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scwin), text);
	history_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));

	gtk_widget_show_all(win);

    insert_history(history_buffer);
}