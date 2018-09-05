#include "function.h"
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
	//gtk_text_view_set_left_margin (GTK_TEXT_VIEW (view1), 30);

	//组件2.2，type_box,放入分割面板
	GtkWidget *type_box=gtk_vbox_new(FALSE, 0);
	gtk_paned_pack2(GTK_PANED(vpaned), type_box, FALSE, FALSE);

	//组件2.2.1，toolbar_box,放入type_box
	GtkWidget *toolbar_box=gtk_hbox_new(TRUE, 0);
	gtk_box_pack_start(GTK_BOX(type_box), toolbar_box, FALSE, FALSE, 5);

	//组件2.2.1.1,2.2.1.2,2.2.1.3，文件选择按钮，表情按钮，发送按钮。放入toolbar_box
	GtkWidget *button_file,*button_emotion,*button_send;
	button_file=gtk_button_new_with_label("file");
	button_emotion=gtk_button_new_with_label("emotion");
	button_send=gtk_button_new_with_label("send");
	gtk_box_pack_start(GTK_BOX(toolbar_box),button_file,FALSE,FALSE,5);
	g_signal_connect(G_OBJECT(button_file),"clicked",G_CALLBACK(File_button_clicked),NULL);
	gtk_box_pack_start(GTK_BOX(toolbar_box),button_emotion,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(toolbar_box),button_send,FALSE,FALSE,5);

	//组件3.2，创建滚动窗口,初始化，加入type_box
	scwin = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(type_box),scwin,TRUE,TRUE,5);

	//组件3.2.1 滚动窗口内创建文本框，加入滚动窗口
	GtkWidget *view2 = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scwin),view2);

	return main_box;

}
