#include <gtk/gtk.h>
#include <stdio.h>


char tupian[20]="0.jpg";
char tupian1[20]="1.jpg";
char tupian2[20]="2.jpg";
char tupian3[20]="3.jpg";
char tupian4[20]="4.jpg";
char tupian5[20]="6.jpg";
char tupian6[20]="7.jpg";
char tupian7[20]="8.jpg";
char tupian8[20]="9.jpg";

GtkWidget *imagemain;

void gaitouxiang(GtkButton* button,gint data)
{
if(data==1)
gtk_image_set_from_file(imagemain,"0.jpg");
if(data==2)
gtk_image_set_from_file(imagemain,"1.jpg");
if(data==3)
gtk_image_set_from_file(imagemain,"2.jpg");
if(data==4)
gtk_image_set_from_file(imagemain,"3.jpg");
if(data==5)
gtk_image_set_from_file(imagemain,"4.jpg");
if(data==6)
gtk_image_set_from_file(imagemain,"6.jpg");
if(data==7)
gtk_image_set_from_file(imagemain,"7.jpg");
if(data==8)
gtk_image_set_from_file(imagemain,"8.jpg");
if(data==9)
gtk_image_set_from_file(imagemain,"9.jpg");

}


void xiugaitouxiang(GtkButton* button,gpointer data)
{
GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(gtk_main_quit),NULL);
gtk_window_set_default_size(GTK_WINDOW(window),500,500);
//GtkWidget *image = gtk_image_new_from_file(tupian);
//gtk_container_add(GTK_CONTAINER(window1), image);

GtkWidget *vbox = gtk_vbox_new(TRUE, 5);
gtk_container_add(GTK_CONTAINER(window), vbox);
/*
GtkWidget *hbox1 = gtk_hbox_new(TRUE, 5);
gtk_container_add(GTK_CONTAINER(vbox), hbox1);
GtkWidget *button0 = gtk_button_new();//
gtk_container_add(GTK_CONTAINER(hbox1), button0);
GtkWidget *image = gtk_image_new_from_file(tupian);
gtk_container_add(GTK_CONTAINER(button0), image);
//g_signal_connect(G_OBJECT(button0),"clicked",G_CALLBACK(gaitouxiang),NULL);
GtkWidget *button01 = gtk_button_new();
gtk_container_add(GTK_CONTAINER(hbox1), button01);
GtkWidget *image1 = gtk_image_new_from_file(tupian);
gtk_container_add(GTK_CONTAINER(button01), image1);
GtkWidget *button02 = gtk_button_new();
gtk_container_add(GTK_CONTAINER(hbox1), button02);
GtkWidget *image2 = gtk_image_new_from_file(tupian);
gtk_container_add(GTK_CONTAINER(button02), image2);
*/

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

g_signal_connect(G_OBJECT(button00),"clicked",G_CALLBACK(gaitouxiang),1);
g_signal_connect(G_OBJECT(button01),"clicked",G_CALLBACK(gaitouxiang),2);
g_signal_connect(G_OBJECT(button02),"clicked",G_CALLBACK(gaitouxiang),3);

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
g_signal_connect(G_OBJECT(button10),"clicked",G_CALLBACK(gaitouxiang),4);
g_signal_connect(G_OBJECT(button11),"clicked",G_CALLBACK(gaitouxiang),5);
g_signal_connect(G_OBJECT(button12),"clicked",G_CALLBACK(gaitouxiang),6);

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

g_signal_connect(G_OBJECT(button20),"clicked",G_CALLBACK(gaitouxiang),7);
g_signal_connect(G_OBJECT(button21),"clicked",G_CALLBACK(gaitouxiang),8);
g_signal_connect(G_OBJECT(button22),"clicked",G_CALLBACK(gaitouxiang),9);

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
GtkWidget *label=gtk_label_new("username");//replace with the nickname
//gtk_container_add(GTK_CONTAINER(hbox1), label);

g_signal_connect(G_OBJECT(button0),"clicked",G_CALLBACK(xiugaitouxiang),NULL);

//
GtkWidget *hbox_button = gtk_vbox_new(FALSE, 5);
GtkWidget *button_add = gtk_button_new_with_label("   添加好友   ");
GtkWidget *button_refresh = gtk_button_new_with_label("   刷新   ");
gtk_box_pack_start(GTK_BOX (hbox_button), button_add, TRUE, TRUE, 0);
gtk_box_pack_start(GTK_BOX (hbox_button), button_refresh, TRUE, TRUE, 0);
gtk_container_add(GTK_CONTAINER(vbox), hbox_button);


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
GtkWidget *image1 = gtk_image_new_from_file("1.jpg");//第一个好友的头像
gtk_container_add(GTK_CONTAINER(hbox2), image1);
GtkWidget *label1=gtk_label_new("username");//第一个好友的名字
gtk_container_add(GTK_CONTAINER(hbox2), label1);

GtkWidget *button12 = gtk_button_new();//
gtk_box_pack_start (vboxp1,button12,FALSE,TRUE,10);
GtkWidget *hbox12 = gtk_hbox_new(FALSE,5);//
gtk_container_add(GTK_CONTAINER(button12), hbox12);
GtkWidget *image12 = gtk_image_new_from_file("1.jpg");//第一个好友的头像
gtk_container_add(GTK_CONTAINER(hbox12), image12);
GtkWidget *label12=gtk_label_new("username");//第一个好友的名字
gtk_container_add(GTK_CONTAINER(hbox12), label12);

GtkWidget *button13 = gtk_button_new();//
gtk_box_pack_start (vboxp1,button13,FALSE,TRUE,10);
GtkWidget *hbox13 = gtk_hbox_new(FALSE,5);//
gtk_container_add(GTK_CONTAINER(button13), hbox13);
GtkWidget *image13 = gtk_image_new_from_file("1.jpg");//第一个好友的头像
gtk_container_add(GTK_CONTAINER(hbox13), image13);
GtkWidget *label13=gtk_label_new("username");//第一个好友的名字
gtk_container_add(GTK_CONTAINER(hbox13), label13);

//GtkWidget *separator1 = gtk_hseparator_new();//separator
//gtk_box_pack_start (GTK_BOX (vbox), separator1, FALSE, TRUE, 5);


GtkWidget *scwin2 = gtk_scrolled_window_new(NULL,NULL);
gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin2),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

/*
GtkWidget *pander1 = gtk_expander_new_with_mnemonic("friend list");//好友列表 
gtk_box_pack_start(GTK_BOX(vbox),pander1,TRUE,TRUE,5);
gtk_container_add(GTK_CONTAINER(pander1), scwin);
gtk_expander_get_spacing (pander1);
GtkWidget *vboxp1 = gtk_vbox_new(TRUE,5);//
//gtk_container_add(GTK_CONTAINER(scwin), vboxp1);
gtk_scrolled_window_add_with_viewport(scwin,vboxp2);
*/
/*
GtkWidget *pander2 = gtk_expander_new_with_mnemonic("group list");//群聊列表
gtk_box_pack_start(GTK_BOX(vbox),pander2,TRUE,TRUE,5);
gtk_container_add(GTK_CONTAINER(pander2), scwin2);
gtk_expander_get_spacing (pander2);
GtkWidget *vboxp2 = gtk_vbox_new(TRUE,5);//
//gtk_container_add(GTK_CONTAINER(scwin), vboxp1);
gtk_scrolled_window_add_with_viewport(scwin2,vboxp2)

GtkWidget *button3 = gtk_button_new();//
gtk_box_pack_start (vboxp2,button3,FALSE,TRUE,10);
GtkWidget *hbox3 = gtk_hbox_new(FALSE,5);//
gtk_container_add(GTK_CONTAINER(button3), hbox3);
GtkWidget *image2 = gtk_image_new_from_file("2.jpg");//第一个群聊的头像 
gtk_container_add(GTK_CONTAINER(hbox3), image2);
GtkWidget *label2=gtk_label_new("username");//第一个群聊的名字 
gtk_container_add(GTK_CONTAINER(hbox3), label2);

GtkWidget *button22 = gtk_button_new();//
gtk_box_pack_start (vboxp2,button22,FALSE,TRUE,10);
GtkWidget *hbox22 = gtk_hbox_new(FALSE,5);//
gtk_container_add(GTK_CONTAINER(button22), hbox22);
GtkWidget *image22 = gtk_image_new_from_file("1.jpg");//第一个群聊的头像 
gtk_container_add(GTK_CONTAINER(hbox22), image22);
GtkWidget *label22=gtk_label_new("username");//第一个群聊的名字 
gtk_container_add(GTK_CONTAINER(hbox22), label22);
//gtk_expander_set_label_fill (pander2,TRUE);//子项的初始状态
*/

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
GtkWidget *image3 = gtk_image_new_from_file("1.jpg");//第一个好友的头像
gtk_container_add(GTK_CONTAINER(hbox3), image3);
GtkWidget *label3=gtk_label_new("username");//第一个好友的名字
gtk_container_add(GTK_CONTAINER(hbox3), label3);

GtkWidget *button22 = gtk_button_new();//
gtk_box_pack_start (vboxp2,button22,FALSE,TRUE,10);
GtkWidget *hbox22 = gtk_hbox_new(FALSE,5);//
gtk_container_add(GTK_CONTAINER(button22), hbox22);
GtkWidget *image22 = gtk_image_new_from_file("1.jpg");//第一个好友的头像
gtk_container_add(GTK_CONTAINER(hbox22), image22);
GtkWidget *label22=gtk_label_new("username");//第一个好友的名字
gtk_container_add(GTK_CONTAINER(hbox22), label22);

GtkWidget *button23 = gtk_button_new();//
gtk_box_pack_start (vboxp2,button23,FALSE,TRUE,10);
GtkWidget *hbox23 = gtk_hbox_new(FALSE,5);//
gtk_container_add(GTK_CONTAINER(button23), hbox23);
GtkWidget *image23 = gtk_image_new_from_file("1.jpg");//第一个好友的头像
gtk_container_add(GTK_CONTAINER(hbox23), image23);
GtkWidget *label23=gtk_label_new("username");//第一个好友的名字
gtk_container_add(GTK_CONTAINER(hbox23), label23);

return vbox;
}

