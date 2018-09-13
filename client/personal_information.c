/********************************************************************************
 * Files         : personal_information.c.c
 * Description   : 该模块为客户端提供储存用户信息的功能
 ********************************************************************************/
#include <gtk/gtk.h>
#include<stdlib.h>
#include "function.h"

GtkWidget *entry1,*entry2,*entry3,*entry4,*spin1,*spin2,*spin3;

/* 
    名称：confirm_button_clicked
    描述：用于处理点击确定键的事件
    做成日期：18/09/06
    参数：GtkWidget *button , gpointer userdata
    返回值：void
    作者：唐容川
*/
void confirm_button_clicked ( GtkWidget *button , gpointer userdata)
{
	strcpy(p_info.name, gtk_entry_get_text (entry1));
	strcpy(p_info.sex, gtk_entry_get_text (entry2));
	strcpy(p_info.age, gtk_entry_get_text (entry3));
	strcpy(p_info.signature, gtk_entry_get_text (entry4));
	
	// strcpy(p_info.year, getNumber(gtk_spin_button_get_value_as_int(spin1)));
	// strcpy(p_info.month, getNumber(gtk_spin_button_get_value_as_int(spin2)));
	// strcpy(p_info.date, getNumber(gtk_spin_button_get_value_as_int(spin3)));
	p_info.year = gtk_spin_button_get_value_as_int(spin1);
	p_info.month = gtk_spin_button_get_value_as_int(spin2);
	p_info.date = gtk_spin_button_get_value_as_int(spin3);

	gtk_widget_destroy(userdata);
}

/* 
    名称：personal_information_button_clicked
    描述：用于启动用户信息界面
    做成日期：18/09/06
    参数：GtkWidget *button , gpointer userdata
    返回值：void
    作者：唐容川
*/
void personal_information_button_clicked ( GtkWidget *button , gpointer userdata)
{
	//声明窗口控制的指针
	GtkWidget* window;
	//声明2个框架
	GtkWidget* frame_personal_infomation,*frame_birthday;
	//4label
	GtkWidget* user_label,*age_label,*signature_label,*sex_label,*label;
	
	//1 button
	GtkWidget* confirm_button;
	//声明4个盒子
	GtkWidget *v_box,*v_h_box,*v_h_v_box,*v_h_h_box,*v_h_h_v_box1,*v_h_h_v_box2,*v_h_h_v_box3;
	//定义一个调节的
	GtkAdjustment* adj1;


	//创建窗口
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//设置窗口的标题
	gtk_window_set_title(GTK_WINDOW(window), "滚动按钮");
	//为信号连接退出函数
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	//为容器设置边缘宽度
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	

	v_box=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),v_box);
	

	//创建一个框架
	frame_personal_infomation = gtk_frame_new("personal information");
	gtk_box_pack_start(GTK_BOX(v_box), frame_personal_infomation, FALSE, FALSE, 5);

	//new button
	confirm_button = gtk_button_new_with_label("confirm");
	gtk_box_pack_start(GTK_BOX(v_box), confirm_button, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(confirm_button),"clicked",G_CALLBACK(confirm_button_clicked),window);
	//new v_h_box
	v_h_box=gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(frame_personal_infomation), v_h_box);

	//new v_h_v_box
	v_h_v_box=gtk_vbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(v_h_box), v_h_v_box, FALSE, FALSE, 5);
	
	//创建一个框架,把框架放到v_h_box中
	frame_birthday = gtk_frame_new("my_birthday");
	gtk_box_pack_start(GTK_BOX(v_h_box), frame_birthday, FALSE, FALSE, 5);

	//new v_h_h_box&put it into the frame_birthday
	v_h_h_box=gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(frame_birthday), v_h_h_box);
	gtk_container_set_border_width(GTK_CONTAINER(v_h_h_box),10);
	
	//create 4 labels and put it in the v_h_v_box
	user_label = gtk_label_new("    name     :");
	sex_label = gtk_label_new("      sex        :");
  	age_label = gtk_label_new("      age        :");
	signature_label=gtk_label_new("signature:");
	entry1=gtk_entry_new();
	entry2=gtk_entry_new();
	entry3=gtk_entry_new();
	entry4=gtk_entry_new();

	gtk_entry_set_text(entry1,p_info.name);
	gtk_entry_set_text(entry2,p_info.sex);
	gtk_entry_set_text(entry3,p_info.age);
	gtk_entry_set_text(entry4,p_info.signature);
/*
	p_info->name=gtk_entry_get_text (entry1);
	p_info->sex=gtk_entry_get_text (entry2);
	p_info->age=gtk_entry_get_text (entry3);
	p_info->signature=gtk_entry_get_text (entry4);
	p-info->year=gtk_spin_button_get_value_as_int(spin1);
	p-info->year=gtk_spin_button_get_value_as_int(spin2);
	p-info->year=gtk_spin_button_get_value_as_int(spin3);
*/

	GtkWidget *h_box1=gtk_hbox_new(FALSE,0);
	GtkWidget *h_box2=gtk_hbox_new(FALSE,0);
	GtkWidget *h_box3=gtk_hbox_new(FALSE,0);
	GtkWidget *h_box4=gtk_hbox_new(FALSE,0);


	gtk_box_pack_start(GTK_BOX(h_box1),user_label, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(h_box1),entry1, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(h_box2),sex_label, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(h_box2),entry2, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(h_box3),age_label, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(h_box3),entry3, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(h_box4),signature_label, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(h_box4),entry4, TRUE, FALSE, 5);


	gtk_box_pack_start(GTK_BOX(v_h_v_box),h_box1, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(v_h_v_box),h_box2, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(v_h_v_box),h_box3, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(v_h_v_box),h_box4, FALSE, FALSE, 5);
	
	
	//创建一个纵向的规则排列的盒子
	v_h_h_v_box1 = gtk_vbox_new(TRUE,0);
	v_h_h_v_box2 = gtk_vbox_new(TRUE,0);
	v_h_h_v_box3 = gtk_vbox_new(TRUE,0);
	//把v_h_h_vbox1放入v_h_h_box里
	gtk_box_pack_start(GTK_BOX(v_h_h_box), v_h_h_v_box1, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(v_h_h_box), v_h_h_v_box2, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(v_h_h_box), v_h_h_v_box3, TRUE, TRUE, 5);
	
	//创建一个标签
	label = gtk_label_new("年: ");
	//把标签放入盒子中
	gtk_box_pack_start(GTK_BOX(v_h_h_v_box1), label, FALSE, FALSE, 2);
	//创建一个滚轮的按钮
	spin1 = gtk_spin_button_new_with_range(1900, 2100, 1);
	//把旋转按钮放入盒子中
	gtk_box_pack_start(GTK_BOX(v_h_h_v_box1), spin1, FALSE, FALSE, 2);
	//设置年
	gtk_spin_button_set_value(spin1, p_info.year);
	
	//创建一个标签
	label = gtk_label_new("月: ");
	//把标签放入盒子中
	gtk_box_pack_start(GTK_BOX(v_h_h_v_box2), label, FALSE, FALSE, 2);
	//创建一个旋转按钮
	spin2 = gtk_spin_button_new_with_range(1, 12, 1);
	//把旋转按钮加入盒子中
	gtk_box_pack_start(GTK_BOX(v_h_h_v_box2), spin2, FALSE, FALSE, 2);
	//设置年
	gtk_spin_button_set_value(spin2, p_info.month);
	
	//创建一个标签
	label = gtk_label_new("日: ");
	//把标签放入vbox3中
	gtk_box_pack_start(GTK_BOX(v_h_h_v_box3), label, FALSE, FALSE, 2);
	//创建一个旋转按钮
	spin3 = gtk_spin_button_new_with_range(1, 31, 1);
	//把旋转按钮加入盒子中
	gtk_box_pack_start(GTK_BOX(v_h_h_v_box3), spin3, FALSE, FALSE, 2);
	//设置年
	gtk_spin_button_set_value(spin3, p_info.date);

	//显示全部窗口	
	gtk_widget_show_all(window);
	//主事件循环
	gtk_main();
	//代码返回逻辑值FALSE
	return FALSE;
}
	
