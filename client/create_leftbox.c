#include <gtk/gtk.h>
#include <stdio.h>
GtkWidget *create_leftbox()
{

    GtkWidget *vbox = gtk_vbox_new(TRUE, 5);
    //gtk_container_add(GTK_CONTAINER(window), vbox);
    GtkWidget *hbox1 = gtk_hbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(vbox), hbox1);
    GtkWidget *image = gtk_image_new_from_file("0.jpg");//add the picture
    //gtk_container_add(GTK_CONTAINER(hbox1), image);
    gtk_box_pack_start(GTK_BOX(hbox1), image,FALSE,FALSE,5);
    GtkWidget *label=gtk_label_new("username");//replace with the nickname
    //gtk_container_add(GTK_CONTAINER(hbox1), label);

    //
    GtkWidget *hbox_button = gtk_hbox_new(FALSE, 5);
    GtkWidget *button_add = gtk_button_new_with_label("   添加好友   ");
    GtkWidget *button_refresh = gtk_button_new_with_label("   刷新   ");
    gtk_box_pack_start(GTK_BOX (hbox_button), button_add, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX (hbox_button), button_refresh, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_button);


    gtk_box_pack_start(GTK_BOX(hbox1), label,FALSE,FALSE,5);
    GtkWidget *pander1 = gtk_expander_new_with_mnemonic("friend list");//好友列表 
    gtk_container_add(GTK_CONTAINER(vbox), pander1);

    GtkWidget *button2 = gtk_button_new();//
    gtk_container_add(GTK_CONTAINER(pander1), button2);
    GtkWidget *hbox2 = gtk_hbox_new(FALSE,5);//
    gtk_container_add(GTK_CONTAINER(button2), hbox2);
    GtkWidget *image1 = gtk_image_new_from_file("1.jpg");//第一个好友的头像
    gtk_container_add(GTK_CONTAINER(hbox2), image1);
    GtkWidget *label1=gtk_label_new("username");//第一个好友的名字
    gtk_container_add(GTK_CONTAINER(hbox2), label1);

    GtkWidget *separator1 = gtk_hseparator_new();//separator
    gtk_box_pack_start (GTK_BOX (vbox), separator1, FALSE, TRUE, 5);

    GtkWidget *pander2 = gtk_expander_new_with_mnemonic("group list");//群聊列表
    gtk_container_add(GTK_CONTAINER(vbox), pander2);
    GtkWidget *button3 = gtk_button_new();//
    gtk_container_add(GTK_CONTAINER(pander2), button3);
    GtkWidget *hbox3 = gtk_hbox_new(FALSE,5);//
    gtk_container_add(GTK_CONTAINER(button3), hbox3);
    GtkWidget *image2 = gtk_image_new_from_file("2.jpg");//第一个群聊的头像 
    gtk_container_add(GTK_CONTAINER(hbox3), image2);
    GtkWidget *label2=gtk_label_new("username");//第一个群聊的名字 
    gtk_container_add(GTK_CONTAINER(hbox3), label2);
    //gtk_expander_set_label_fill (pander2,TRUE);//子项的初始状态

    return vbox;
}

