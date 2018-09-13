/********************************************************************************
 * Files         : register_window.c
 * Description   : 该模块为客户端主界面左侧的构造模块
 ********************************************************************************/
#include <gtk/gtk.h>
GtkWidget *window_test;

static gint delete_event()
{
    /* 如果你的 "delete_event" 信号处理函数返回 FALSE，GTK 会发出 "destroy" 信号。
    * 返回 TRUE，你不希望关闭窗口。
    * 当你想弹出“你确定要退出吗?”对话框时它很有用。*/
    gtk_widget_hide_all(window_test);

    return FALSE; //注意必须为TRUE，否则子窗口点击关闭按钮后，就摧毁了，而不是隐藏了。
}

static GtkWidget* entry1;
static GtkWidget* entry2;
static GtkWidget* entry3;
static GtkWidget* entry4;

void on_clicked(GtkWidget* button,gpointer data)
{
	gtk_widget_destroy(data);
}

/* 
    名称：on_button_clicked2
    描述：打印注册的用户名和密码
    做成日期：18/09/06
    参数：GtkWidget* button,gpointer data
    返回值：void
    作者：叶非凡
*/
void on_button_clicked2(GtkWidget* button,gpointer data)
{
	const gchar *username=gtk_entry_get_text(GTK_ENTRY(entry1));
	const gchar *password=gtk_entry_get_text(GTK_ENTRY(entry2));
	g_print("username:%s",username);
	g_print("\n");
	g_print("password:%s",password);
	g_print("\n");
}

/* 
    名称：create_test_window
    描述：用于处理点击确定键的事件
    做成日期：18/09/06
    参数：void
    返回值：void
    作者：叶非凡
*/
GtkWidget *create_test_window()
{

	GtkWidget *window_test;
	GtkWidget *table;
	GtkWidget *button1;	
	GtkWidget *button2;	
	GtkWidget *button3;	
	GtkWidget *button4;	
	GtkWidget *button5;	
	GtkWidget *button6;	
	GtkWidget* label1;
	GtkWidget* label2;
	GtkWidget* label3;
	GtkWidget* label4;
	GtkWidget *frame;	
	//初始化GTK
	//创建最上层主窗口
	window_test = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//连接信号"delete_event",使得窗口关闭时发生
	g_signal_connect(G_OBJECT(window_test),"delete_event",G_CALLBACK(on_clicked), window_test); 
	//设置窗口标题
	gtk_window_set_title(GTK_WINDOW(window_test),"register");
	//设定窗口的默认宽高
	gtk_window_set_default_size(GTK_WINDOW(window_test),250,350);
	//设定窗口的位置,让窗口总在最前端
	gtk_window_set_position(GTK_WINDOW(window_test),GTK_WIN_POS_CENTER);
	//设定容器边框的宽度
	gtk_container_set_border_width(GTK_CONTAINER(window_test),10);
	//ŽŽœš¿òŒÜ
	frame = gtk_frame_new("");

	//°Ñ¿òŒÜ·ÅœøŽ°¿Ú
	gtk_container_add(GTK_CONTAINER(window_test),frame);
	
	//ŽŽœšžñ×ŽÈÝÆ÷£¬ÐÐÊý¡¢ÁÐÊý¡¢ÊÇ·ñŸùÔÈ·ÖÅä
	table= gtk_table_new(10,10,FALSE);
	//Éè¶šÈÝÆ÷±ß¿òµÄ¿í¶È
	gtk_container_set_border_width(GTK_CONTAINER(table),10);
	//ÎªËùÓÐµÄÐÐºÍÁÐÖ®ŒäÉèÖÃÏàÍ¬µÄ¿Õ°×£¬ŸùÎª5žöÏñËØ
	gtk_table_set_row_spacings(GTK_TABLE(table),5);
	gtk_table_set_col_spacings(GTK_TABLE(table),5);
	//°Ñžñ×ŽÈÝÆ÷·Åœø¿òŒÜ
	gtk_container_add(GTK_CONTAINER(frame),table);	

	label1 = gtk_label_new("username"); 
	gtk_table_attach(GTK_TABLE(table),label1,0,5,2,3,GTK_FILL,GTK_FILL,0,0);
	entry1 = gtk_entry_new(); 
	gtk_table_attach(GTK_TABLE(table),entry1,6,10,2,3,GTK_FILL,GTK_FILL,0,0);

	label2 = gtk_label_new("password"); 
	gtk_table_attach(GTK_TABLE(table),label2,0,5,3,4,GTK_FILL,GTK_FILL,0,0);
	entry2 = gtk_entry_new(); 
	gtk_table_attach(GTK_TABLE(table),entry2,6,10,3,4,GTK_FILL,GTK_FILL,0,0);
	gtk_entry_set_visibility(GTK_ENTRY(entry2),FALSE);  

	label3 = gtk_label_new("confirm password"); 
	gtk_table_attach(GTK_TABLE(table),label3,0,5,4,5,GTK_FILL,GTK_FILL,0,0);
	entry3 = gtk_entry_new(); 
	gtk_table_attach(GTK_TABLE(table),entry3,6,10,4,5,GTK_FILL,GTK_FILL,0,0);
	gtk_entry_set_visibility(GTK_ENTRY(entry3),FALSE);  

	/*
	label4 = gtk_label_new("your mother's name"); 
	gtk_table_attach(GTK_TABLE(table),label4,0,5,5,6,GTK_FILL,GTK_FILL,0,0);
	entry4 = gtk_entry_new(); 
	gtk_table_attach(GTK_TABLE(table),entry4,6,10,5,6,GTK_FILL,GTK_FILL,0,0);
	*/

	button1 = gtk_button_new_with_label("register");
	//把按钮放入格状容器，“0，1，0，1”表示四个坐标，从左往右，从上到下，GTK_FILL：可填充，“0，0”间隔距离
	gtk_table_attach(GTK_TABLE(table),button1,3,8,10,11,GTK_FILL,GTK_FILL,0,0);

	//gtk_widget_show_all(window_test); 
	//gtk_main(); 
	return window_test; 
}