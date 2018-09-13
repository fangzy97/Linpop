/********************************************************************************
 * Files         : create_leftbox.c
 * Description   : 该模块为客户端主界面左侧的构造模块
 ********************************************************************************/
#include "function.h"

char tupian[20]="images/0.jpg";
char tupian1[20]="images/1.jpg";
char tupian2[20]="images/2.jpg";
char tupian3[20]="images/3.jpg";
char tupian4[20]="images/4.jpg";
char tupian5[20]="images/6.jpg";
char tupian6[20]="images/7.jpg";
char tupian7[20]="images/8.jpg";
char tupian8[20]="images/9.jpg";

GtkWidget *imagemain;
//newbianliang
GtkWidget *imageyonghu;

/* 
    名称：gaitouxiang
    描述：该函数用于选择头像更换
    做成日期：18/09/06
    参数：GtkButton* button, gint data
    返回值：void
    作者：方致远
*/
void gaitouxiang(GtkButton* button, gint data)
{
    if(data==0)
        gtk_image_set_from_file(imagemain,"images/0.jpg");
    if(data==1)
        gtk_image_set_from_file(imagemain,"images/1.jpg");
    if(data==2)
        gtk_image_set_from_file(imagemain,"images/2.jpg");
    if(data==3)
        gtk_image_set_from_file(imagemain,"images/3.jpg");
    if(data==4)
        gtk_image_set_from_file(imagemain,"images/4.jpg");
    if(data==5)
        gtk_image_set_from_file(imagemain,"images/6.jpg");
    if(data==6)
        gtk_image_set_from_file(imagemain,"images/7.jpg");
    if(data==7)
        gtk_image_set_from_file(imagemain,"images/8.jpg");
    if(data==8)
        gtk_image_set_from_file(imagemain,"images/9.jpg");
    if(data==9)
        gtk_image_set_from_file(imagemain,"images/10.jpg");
}

void shuaxin(GtkButton* button,gint data)
{
    gtk_image_set_from_file(imageyonghu,"9-2.jpg");
}

/* 
    名称：chang_background
    描述：改变背景的函数
    做成日期：18/09/06
    参数：GtkButton* button, int w, int h, const gchar *path
    返回值：void
    作者：叶非凡
*/
void chang_background(GtkWidget *widget, int w, int h, const gchar *path)
{
	gtk_widget_set_app_paintable(widget, TRUE);		//允许窗口可以绘图
	gtk_widget_realize(widget);	
 
	/* 更改背景图时，图片会重叠
	 * 这时要手动调用下面的函数，让窗口绘图区域失效，产生窗口重绘制事件（即 expose 事件）。
	 */
	gtk_widget_queue_draw(widget);
 
	GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(path, NULL);	// 创建图片资源对象
	// w, h是指定图片的宽度和高度
	GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR);
 
	GdkPixmap *pixmap = NULL;
 
	/* 创建pixmap图像; 
	 * NULL：不需要蒙版; 
	 * 123： 0~255，透明到不透明
	 */
	gdk_pixbuf_render_pixmap_and_mask(dst_pixbuf, &pixmap, NULL, 128);
	// 通过pixmap给widget设置一张背景图，最后一个参数必须为: FASLE
	gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);
 
	// 释放资源
	g_object_unref(src_pixbuf);
	g_object_unref(dst_pixbuf);
	g_object_unref(pixmap);
}

/* 
    名称：chang_background1
    描述：改变背景的函数
    做成日期：18/09/06
    参数：(GtkButton* button,gpointer data)
    返回值：void
    作者：叶非凡
*/
void chang_background1(GtkButton* button,gpointer data)
{
    if(data==9)
        chang_background(main_window, 500, 400, "");
    if(data==1)
        chang_background(main_window, 500, 400, "background/background1.jpg");
    if(data==2)
        chang_background(main_window, 500, 400, "background/background2.jpg");
    if(data==3)
        chang_background(main_window, 500, 400, "background/background3.jpg");
    if(data==4)
        chang_background(main_window, 500, 400, "background/background4.jpg");
    if(data==5)
        chang_background(main_window, 500, 400, "background/background5.jpg");
    if(data==6)
        chang_background(main_window, 500, 400, "background/background6.jpg");
    if(data==7)
        chang_background(main_window, 500, 400, "background/background7.jpg");
    if(data==8)
        chang_background(main_window, 500, 400, "background/background8.jpg");
}

void on_delete(GtkButton* button, gpointer data)
{
    gtk_widget_destroy(data);
}

/* 
    名称：add_friend
    描述：该函数用于添加好友的事件
    做成日期：18/09/06
    参数：GtkButton* button,gpointer data
    返回值：void
    作者：叶非凡
*/
void add_friend(GtkButton* button,gpointer data)
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(on_delete),window);
    gtk_window_set_default_size(GTK_WINDOW(window),500,500);

    GtkWidget *vbox1 = gtk_vbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox1);
    GtkWidget *label=gtk_label_new("请输入要查找的用户名"); 
    gtk_box_pack_start(GTK_BOX(vbox1), label,FALSE,FALSE,5);

    GtkWidget *hbox1=gtk_hbox_new(TRUE,5);
    gtk_box_pack_start(GTK_BOX(vbox1), hbox1,FALSE,FALSE,5);
    GtkWidget *entry1=gtk_entry_new();
    gtk_entry_set_text(entry1,"搜索");
    gtk_box_pack_start(GTK_BOX(hbox1), entry1,FALSE,FALSE,5);
    GtkWidget *button00 = gtk_button_new_with_label("查找");//
    gtk_box_pack_start(GTK_BOX(hbox1), button00,FALSE,FALSE,5);

    GtkWidget *scwin = gtk_scrolled_window_new(NULL,NULL);
    gtk_box_pack_start(GTK_BOX(vbox1), scwin,FALSE,FALSE,5);

    GtkWidget *hbox2=gtk_hbox_new(TRUE,5);
    gtk_box_pack_start(GTK_BOX(vbox1), hbox2,FALSE,FALSE,5);

    GtkWidget *button10 = gtk_button_new_with_label("关闭");//
    gtk_box_pack_start(GTK_BOX(hbox2), button10,FALSE,FALSE,5);
    g_signal_connect(G_OBJECT(button10), "clicked", G_CALLBACK(on_delete),window);

    GtkWidget *button11 = gtk_button_new_with_label("添加好友");//
    gtk_box_pack_start(GTK_BOX(hbox2), button11,FALSE,FALSE,5);

    gtk_widget_show_all(window);
}

void my_delete(GtkButton *button, gpointer data)
{
    gtk_widget_destroy(data);
}

void chang_background0(GtkButton* button,gpointer data)
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(my_delete),window);
    gtk_window_set_default_size(GTK_WINDOW(window),500,500);
    //GtkWidget *image = gtk_image_new_from_file(tupian);
    //gtk_container_add(GTK_CONTAINER(main_window), image);

    GtkWidget *vbox = gtk_vbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *hbox1 = gtk_hbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(vbox), hbox1);
    GtkWidget *button00 = gtk_button_new_with_label("魅黑");//
    gtk_container_add(GTK_CONTAINER(hbox1), button00);
    //GtkWidget *image00 = gtk_image_new_from_file(tupian);
    //gtk_container_add(GTK_CONTAINER(button00), image00);
    GtkWidget *button01 = gtk_button_new_with_label("天蓝");//
    gtk_container_add(GTK_CONTAINER(hbox1), button01);
    //GtkWidget *image01 = gtk_image_new_from_file(tupian1);
    //gtk_container_add(GTK_CONTAINER(button01), image01);
    GtkWidget *button02 = gtk_button_new_with_label("星空");//
    gtk_container_add(GTK_CONTAINER(hbox1), button02);
    //GtkWidget *image02 = gtk_image_new_from_file(tupian2);
    //gtk_container_add(GTK_CONTAINER(button02), image02);

    g_signal_connect(G_OBJECT(button00),"clicked",G_CALLBACK(chang_background1),1);
    g_signal_connect(G_OBJECT(button01),"clicked",G_CALLBACK(chang_background1),2);
    g_signal_connect(G_OBJECT(button02),"clicked",G_CALLBACK(chang_background1),3);

    GtkWidget *hbox2 = gtk_hbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(vbox), hbox2);
    GtkWidget *button10 = gtk_button_new_with_label("灿红");//
    gtk_container_add(GTK_CONTAINER(hbox2), button10);
    //GtkWidget *image10 = gtk_image_new_from_file(tupian3);
    //gtk_container_add(GTK_CONTAINER(button10), image10);
    GtkWidget *button11 = gtk_button_new_with_label("鲜绿");//
    gtk_container_add(GTK_CONTAINER(hbox2), button11);
    //GtkWidget *image11 = gtk_image_new_from_file(tupian4);
    //gtk_container_add(GTK_CONTAINER(button11), image11);
    GtkWidget *button12 = gtk_button_new_with_label("几何");//
    gtk_container_add(GTK_CONTAINER(hbox2), button12);
    //GtkWidget *image12 = gtk_image_new_from_file(tupian5);
    //gtk_container_add(GTK_CONTAINER(button12), image12);
    g_signal_connect(G_OBJECT(button10),"clicked",G_CALLBACK(chang_background1),4);
    g_signal_connect(G_OBJECT(button11),"clicked",G_CALLBACK(chang_background1),5);
    g_signal_connect(G_OBJECT(button12),"clicked",G_CALLBACK(chang_background1),6);

    GtkWidget *hbox3 = gtk_hbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(vbox), hbox3);
    GtkWidget *button20 = gtk_button_new_with_label("粉红");//
    gtk_container_add(GTK_CONTAINER(hbox3), button20);
    //GtkWidget *image20 = gtk_image_new_from_file(tupian6);
    //gtk_container_add(GTK_CONTAINER(button20), image20);
    GtkWidget *button21 = gtk_button_new_with_label("兔子");//
    gtk_container_add(GTK_CONTAINER(hbox3), button21);
    //GtkWidget *image21 = gtk_image_new_from_file(tupian7);
    //gtk_container_add(GTK_CONTAINER(button21), image21);
    GtkWidget *button22 = gtk_button_new_with_label("经典");//
    gtk_container_add(GTK_CONTAINER(hbox3), button22);
    //GtkWidget *image22 = gtk_image_new_from_file(tupian8);
    //gtk_container_add(GTK_CONTAINER(button22), image22);

    g_signal_connect(G_OBJECT(button20),"clicked",G_CALLBACK(chang_background1),7);
    g_signal_connect(G_OBJECT(button21),"clicked",G_CALLBACK(chang_background1),8);
    g_signal_connect(G_OBJECT(button22),"clicked",G_CALLBACK(chang_background1),9);

    gtk_widget_show_all(window);
}

void xiugaitouxiang(GtkButton* button,gpointer data)
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_default_size(GTK_WINDOW(window),500,500);
    //GtkWidget *image = gtk_image_new_from_file(tupian);
    //gtk_container_add(GTK_CONTAINER(main_window), image);

    GtkWidget *vbox = gtk_vbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *hbox1 = gtk_hbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(vbox), hbox1);
    GtkWidget *button00 = gtk_button_new();//
    gtk_container_add(GTK_CONTAINER(hbox1), button00);
    GtkWidget *image00 = gtk_image_new_from_file(tupian);
    gtk_container_add(GTK_CONTAINER(button00), image00);
    GtkWidget *button01 = gtk_button_new();//
    gtk_container_add(GTK_CONTAINER(hbox1), button01);
    GtkWidget *image01 = gtk_image_new_from_file(tupian1);
    gtk_container_add(GTK_CONTAINER(button01), image01);
    GtkWidget *button02 = gtk_button_new();//
    gtk_container_add(GTK_CONTAINER(hbox1), button02);
    GtkWidget *image02 = gtk_image_new_from_file(tupian2);
    gtk_container_add(GTK_CONTAINER(button02), image02);

    g_signal_connect(G_OBJECT(button00),"clicked",G_CALLBACK(gaitouxiang),0);
    g_signal_connect(G_OBJECT(button01),"clicked",G_CALLBACK(gaitouxiang),1);
    g_signal_connect(G_OBJECT(button02),"clicked",G_CALLBACK(gaitouxiang),2);

    GtkWidget *hbox2 = gtk_hbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(vbox), hbox2);
    GtkWidget *button10 = gtk_button_new();//
    gtk_container_add(GTK_CONTAINER(hbox2), button10);
    GtkWidget *image10 = gtk_image_new_from_file(tupian3);
    gtk_container_add(GTK_CONTAINER(button10), image10);
    GtkWidget *button11 = gtk_button_new();//
    gtk_container_add(GTK_CONTAINER(hbox2), button11);
    GtkWidget *image11 = gtk_image_new_from_file(tupian4);
    gtk_container_add(GTK_CONTAINER(button11), image11);
    GtkWidget *button12 = gtk_button_new();//
    gtk_container_add(GTK_CONTAINER(hbox2), button12);
    GtkWidget *image12 = gtk_image_new_from_file(tupian5);
    gtk_container_add(GTK_CONTAINER(button12), image12);
    g_signal_connect(G_OBJECT(button10),"clicked",G_CALLBACK(gaitouxiang),3);
    g_signal_connect(G_OBJECT(button11),"clicked",G_CALLBACK(gaitouxiang),4);
    g_signal_connect(G_OBJECT(button12),"clicked",G_CALLBACK(gaitouxiang),5);

    GtkWidget *hbox3 = gtk_hbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(vbox), hbox3);
    GtkWidget *button20 = gtk_button_new();//
    gtk_container_add(GTK_CONTAINER(hbox3), button20);
    GtkWidget *image20 = gtk_image_new_from_file(tupian6);
    gtk_container_add(GTK_CONTAINER(button20), image20);
    GtkWidget *button21 = gtk_button_new();//
    gtk_container_add(GTK_CONTAINER(hbox3), button21);
    GtkWidget *image21 = gtk_image_new_from_file(tupian7);
    gtk_container_add(GTK_CONTAINER(button21), image21);
    GtkWidget *button22 = gtk_button_new();//
    gtk_container_add(GTK_CONTAINER(hbox3), button22);
    GtkWidget *image22 = gtk_image_new_from_file(tupian8);
    gtk_container_add(GTK_CONTAINER(button22), image22);

    g_signal_connect(G_OBJECT(button20),"clicked",G_CALLBACK(gaitouxiang),6);
    g_signal_connect(G_OBJECT(button21),"clicked",G_CALLBACK(gaitouxiang),7);
    g_signal_connect(G_OBJECT(button22),"clicked",G_CALLBACK(gaitouxiang),8);

    gtk_widget_show_all(window);
    gtk_main();
}

GtkWidget *create_leftbox()
{
    GtkWidget *vbox = gtk_vbox_new(TRUE, 5);
    //gtk_container_add(GTK_CONTAINER(window), vbox);
    GtkWidget *hbox1 = gtk_hbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(vbox), hbox1);
    GtkWidget *button0 = gtk_button_new();//
    gtk_container_add(GTK_CONTAINER(hbox1), button0);
    imagemain = gtk_image_new_from_file(tupian);//add the picture
    gtk_container_add(GTK_CONTAINER(button0), imagemain);
    //gtk_container_add(GTK_CONTAINER(hbox1), image);
    gtk_box_pack_start(GTK_BOX(hbox1), button0,FALSE,FALSE,5);
    GtkWidget *label=gtk_label_new(username);//replace with the nickname
    //gtk_container_add(GTK_CONTAINER(hbox1), label);

    g_signal_connect(G_OBJECT(button0),"clicked",G_CALLBACK(xiugaitouxiang),NULL);

    //
    GtkWidget *hbox_button = gtk_vbox_new(FALSE, 5);
    GtkWidget *button_add = gtk_button_new_with_label("   添加好友   ");
    GtkWidget *button_background = gtk_button_new_with_label("   更改背景   ");
    GtkWidget *button_refresh = gtk_button_new_with_label("   刷新   ");
    gtk_box_pack_start(GTK_BOX (hbox_button), button_add, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX (hbox_button), button_refresh, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX (hbox_button), button_background, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_button);
    g_signal_connect(G_OBJECT(button_background),"clicked",G_CALLBACK(chang_background0),NULL);
    g_signal_connect(G_OBJECT(button_add),"clicked",G_CALLBACK(add_friend),NULL);
    g_signal_connect(G_OBJECT(button_refresh),"clicked",G_CALLBACK(shuaxin),NULL);

    gtk_box_pack_start(GTK_BOX(hbox1), label,FALSE,FALSE,5);

    GtkWidget *scwin = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

    GtkWidget *pander1 = gtk_expander_new_with_mnemonic("friend list");//好友列表 
    gtk_box_pack_start(GTK_BOX(vbox),pander1,TRUE,TRUE,5);
    gtk_container_add(GTK_CONTAINER(pander1), scwin);
    gtk_expander_get_spacing (pander1);
    GtkWidget *vboxp1 = gtk_vbox_new(TRUE,5);//
    //gtk_container_add(GTK_CONTAINER(scwin), vboxp1);
    gtk_scrolled_window_add_with_viewport(scwin,vboxp1);
    GtkWidget *button2 = gtk_button_new();//
    //gtk_container_add(GTK_CONTAINER(vboxp1), button2);
    gtk_box_pack_start (vboxp1,button2,FALSE,TRUE,10);
    GtkWidget *hbox2 = gtk_hbox_new(FALSE,5);//
    gtk_container_add(GTK_CONTAINER(button2), hbox2);

    imageyonghu = gtk_image_new_from_file("images/9.jpg");//第一个好友的头像
    gtk_container_add(GTK_CONTAINER(hbox2), imageyonghu);
    GtkWidget *label1=gtk_label_new("9");//第一个好友的名字
    gtk_container_add(GTK_CONTAINER(hbox2), label1);

    GtkWidget *button12 = gtk_button_new();//
    gtk_box_pack_start (vboxp1,button12,FALSE,TRUE,10);
    GtkWidget *hbox12 = gtk_hbox_new(FALSE,5);//
    gtk_container_add(GTK_CONTAINER(button12), hbox12);
    GtkWidget *image12 = gtk_image_new_from_file("images/1.jpg");//第一个好友的头像
    gtk_container_add(GTK_CONTAINER(hbox12), image12);
    GtkWidget *label12=gtk_label_new("1");//第一个好友的名字
    gtk_container_add(GTK_CONTAINER(hbox12), label12);

    GtkWidget *button13 = gtk_button_new();//
    gtk_box_pack_start (vboxp1,button13,FALSE,TRUE,10);
    GtkWidget *hbox13 = gtk_hbox_new(FALSE,5);//
    gtk_container_add(GTK_CONTAINER(button13), hbox13);
    GtkWidget *image13 = gtk_image_new_from_file("images/2.jpg");//第一个好友的头像
    gtk_container_add(GTK_CONTAINER(hbox13), image13);
    GtkWidget *label13=gtk_label_new("2");//第一个好友的名字
    gtk_container_add(GTK_CONTAINER(hbox13), label13);

    //GtkWidget *separator1 = gtk_hseparator_new();//separator
    //gtk_box_pack_start (GTK_BOX (vbox), separator1, FALSE, TRUE, 5);


    GtkWidget *scwin2 = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin2),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

    GtkWidget *pander2 = gtk_expander_new_with_mnemonic("friend list");//好友列表 
    gtk_box_pack_start(GTK_BOX(vbox),pander2,TRUE,TRUE,5);
    gtk_container_add(GTK_CONTAINER(pander2), scwin2);
    gtk_expander_get_spacing (pander2);
    GtkWidget *vboxp2 = gtk_vbox_new(TRUE,5);//
    //gtk_container_add(GTK_CONTAINER(scwin), vboxp1);
    gtk_scrolled_window_add_with_viewport(scwin2,vboxp2);
    GtkWidget *button3 = gtk_button_new();//
    //gtk_container_add(GTK_CONTAINER(vboxp1), button2);
    gtk_box_pack_start (vboxp2,button3,FALSE,TRUE,10);
    GtkWidget *hbox3 = gtk_hbox_new(FALSE,5);//
    gtk_container_add(GTK_CONTAINER(button3), hbox3);
    GtkWidget *image3 = gtk_image_new_from_file("images/3.jpg");//第一个好友的头像
    gtk_container_add(GTK_CONTAINER(hbox3), image3);
    GtkWidget *label3=gtk_label_new("3");//第一个好友的名字
    gtk_container_add(GTK_CONTAINER(hbox3), label3);

    GtkWidget *button22 = gtk_button_new();//
    gtk_box_pack_start (vboxp2,button22,FALSE,TRUE,10);
    GtkWidget *hbox22 = gtk_hbox_new(FALSE,5);//
    gtk_container_add(GTK_CONTAINER(button22), hbox22);
    GtkWidget *image22 = gtk_image_new_from_file("images/4.jpg");//第一个好友的头像
    gtk_container_add(GTK_CONTAINER(hbox22), image22);
    GtkWidget *label22=gtk_label_new("4");//第一个好友的名字
    gtk_container_add(GTK_CONTAINER(hbox22), label22);

    GtkWidget *button23 = gtk_button_new();//
    gtk_box_pack_start (vboxp2,button23,FALSE,TRUE,10);
    GtkWidget *hbox23 = gtk_hbox_new(FALSE,5);//
    gtk_container_add(GTK_CONTAINER(button23), hbox23);
    GtkWidget *image23 = gtk_image_new_from_file("images/6.jpg");//第一个好友的头像
    gtk_container_add(GTK_CONTAINER(hbox23), image23);
    GtkWidget *label23=gtk_label_new("5");//第一个好友的名字
    gtk_container_add(GTK_CONTAINER(hbox23), label23);

    return vbox;
}