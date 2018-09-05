
#include <gtk/gtk.h>
#include "main.h" 
 
void deal_switch_page(GtkNotebook *notebook, gpointer page, guint page_num, gpointer data)
{
        printf("我是第%d个页面\n", page_num+1);
        return;
}
 
int main(int argc, char *argv[])
{
	//1.gtk环境
	gtk_init(&argc, &argv);

	//2.创建一个window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_default_size(GTK_WINDOW(window),1000,800);

	//3.创建笔记本控件
	GtkWidget *notebook = gtk_notebook_new();
	gtk_container_add(GTK_CONTAINER(window), notebook);

	//4.页标签的位置，可以有四种位置：上、下、左或右
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);//上面

	//5.创建一个水平布局
	GtkWidget *hbox = gtk_hbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(window), hbox);
		
	//第一个页面
	//第一个页面的label
	GtkWidget *label = gtk_label_new("会话窗口");
	//创建主盒子
	GtkWidget *main_box  =gtk_hbox_new(TRUE,5); 
	//把主盒子装入notebook的第一页，并设以label.
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), main_box, label);
	//创建水平分割面板
	GtkWidget *hpaned=gtk_hpaned_new();
	//水平分割面板装入总盒子
	gtk_box_pack_start(GTK_BOX(main_box),hpaned,TRUE,TRUE,0);
	//左，右盒子分别装入水平分割面板
	gtk_paned_pack1(GTK_PANED(hpaned),create_leftbox(),FALSE,FALSE);
	gtk_paned_pack2(GTK_PANED(hpaned),create_rightbox(),FALSE,FALSE);
	

	//7.第二个页面
	label = gtk_label_new("功能窗口");
	GtkWidget *vbox = gtk_vbox_new(TRUE, 5);
	GtkWidget *hbox1,*hbox2,*hbox3;
	GtkWidget *personal_information_button,*calc_button,*cale_button,*button4,*button5,*button6;

	personal_information_button= gtk_button_new_with_label("个性化设置");
	g_signal_connect(G_OBJECT(personal_information_button),"clicked",G_CALLBACK(personal_information_button_clicked),NULL);
	calc_button= gtk_button_new_with_label("计算器");
	g_signal_connect(G_OBJECT(calc_button),"clicked",G_CALLBACK(calc_button_clicked),NULL);
	cale_button= gtk_button_new_with_label("日历");
	g_signal_connect(G_OBJECT(cale_button),"clicked",G_CALLBACK(cale_button_clicked),NULL);
	
	hbox1=gtk_hbox_new(TRUE, 5);
	hbox2=gtk_hbox_new(TRUE, 5);
	hbox3=gtk_hbox_new(TRUE, 5);

	button4= gtk_button_new_with_label("4");
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

	//8.第三个页面,在指定位置添加页面，从0开始
	gtk_widget_show_all(window);

	//12.主事件循环
	gtk_main();

	return 0;
}
