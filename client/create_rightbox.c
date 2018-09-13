/********************************************************************************
 * Files         : create_rightbox.c
 * Description   : 该模块为客户端主界面右侧的构造模块
 ********************************************************************************/
#include "function.h"

GtkTextBuffer *buffer; //显示对话内容的文本显示缓冲区
GtkTextBuffer *input_buffer; //消息输入框文本显示缓冲区
GtkTextBuffer *file_buffer; //消息输入框文本显示缓冲区
GtkWidget *target_entry;
GtkWidget *path_entry;

/* 
    名称：create_rightbox
    描述：该函数是右侧界面的入口函数
    做成日期：18/09/06
    参数：void
    返回值：GtkWidget*
    作者：唐容川
*/
GtkWidget *create_rightbox()
{
	//main_box实例化并放入window
	GtkWidget *main_box = gtk_vbox_new(FALSE, 0);
	//gtk_container_add(GTK_CONTAINER(window), main_box);

	//组件1，label,放入main_box
	GtkWidget *label = gtk_label_new("联系人名字");
	gtk_box_pack_start(GTK_BOX(main_box), label, FALSE, FALSE, 5);

	//组件2，分割界面，放入vpaned_box
	GtkWidget *vpaned = gtk_vpaned_new();
	gtk_box_pack_start(GTK_BOX(main_box), vpaned, TRUE, TRUE, 5);

	//组件2，text_box，放入main_box
	GtkWidget *text_box = gtk_vbox_new(FALSE,0);
	gtk_paned_pack1(GTK_PANED(vpaned), text_box, FALSE, FALSE);
	
	//组件2.1创建滚动窗口,初始化，text_box
	GtkWidget *scwin = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(text_box), scwin, TRUE, TRUE, 5);

	//组件2.1.1滚动窗口内创建文本框，加入滚动窗口
	GtkWidget *view1 = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scwin), view1);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view1));
	//gtk_text_view_set_left_margin (GTK_TEXT_VIEW (view1), 30);

	//组件2.2，type_box,放入分割面板
	GtkWidget *type_box = gtk_vbox_new(FALSE, 0);
	gtk_paned_pack2(GTK_PANED(vpaned), type_box, FALSE, FALSE);

	//组件2.2.1，toolbar_box,放入type_box
	GtkWidget *toolbar_box = gtk_hbox_new(TRUE, 0);
	gtk_box_pack_start(GTK_BOX(type_box), toolbar_box, FALSE, FALSE, 5);

	// 组件2.2.1.1文件选择按钮
	GtkWidget *button_file;
	button_file = gtk_button_new_with_label("file");
	gtk_box_pack_start(GTK_BOX(toolbar_box), button_file, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(button_file), "clicked", G_CALLBACK(File_button_clicked), NULL);

	// 2.2.1.2表情按钮
	GtkWidget *button_emotion;
	button_emotion=gtk_button_new_with_label("emotion");
	gtk_box_pack_start(GTK_BOX(toolbar_box), button_emotion, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(button_emotion), "clicked", G_CALLBACK(addFace), NULL);

	// 2.2.1.3发送按钮
	GtkWidget *button_send;
	button_send=gtk_button_new_with_label("send");	
	gtk_box_pack_start(GTK_BOX(toolbar_box), button_send, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(button_send), "clicked", G_CALLBACK(on_send), NULL);

	GtkWidget *button_history;
	button_history = gtk_button_new_with_label("history");
	gtk_box_pack_start(GTK_BOX(toolbar_box), button_history, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(button_history), "clicked", G_CALLBACK(create_history), NULL);

	GtkWidget *target_area = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(type_box), target_area, FALSE, FALSE, 5);

	GtkWidget *target_label;
	target_label = gtk_label_new("聊天目标：");
	gtk_box_pack_start(GTK_BOX(target_area), target_label, FALSE, FALSE, 5);

	target_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(target_area), target_entry, FALSE, FALSE, NULL);

	// 组件3.2，创建滚动窗口,初始化，加入type_box
	scwin = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(type_box), scwin, TRUE, TRUE, 5);

	// 组件3.2.1 滚动窗口内创建文本框，加入滚动窗口
	GtkWidget *view2 = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scwin), view2);
	input_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view2));

	GtkWidget *file_area;
	file_area = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(type_box), file_area, FALSE, FALSE, 5);

	GtkWidget *file_label;
	file_label = gtk_label_new("目标文件：");
	gtk_box_pack_start(GTK_BOX(file_area), file_label, FALSE, FALSE, 5);

	GtkWidget *file_text;
	file_text = gtk_text_view_new();
	gtk_box_pack_start(GTK_BOX(file_area), file_text, FALSE, FALSE, 5);
	file_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(file_text));
	// path_entry = gtk_entry_new();
	// gtk_box_pack_start(GTK_BOX(file_area), path_entry, TRUE, FALSE, 5);

	GtkWidget *file_send;
	file_send = gtk_button_new_with_label("确认发送");
	gtk_box_pack_start(GTK_BOX(file_area), file_send, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(file_send), "clicked", G_CALLBACK(on_send_file_click), NULL);

	return main_box;
}
