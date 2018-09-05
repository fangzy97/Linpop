/* 选择日期 cale.c */
#include <gtk/gtk.h>
void on_ok_clicked (GtkButton* button,gpointer data)
{
guint year;
guint month;
guint date;
//注意月份是从0开始的,即0-11
gtk_calendar_get_date(GTK_CALENDAR(data),&year,&month,&date);
g_print("你选择的日期是 %d 年 %d 月 %d 日\n",year,month+1,date);
}
void cale_button_clicked ( GtkWidget *button1 , gpointer userdata)
{
GtkWidget *window;
GtkWidget *box;
GtkWidget *calendar;
GtkWidget *button;
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
g_signal_connect(G_OBJECT(window),"delete_event",
G_CALLBACK(gtk_main_quit),NULL);
gtk_window_set_title(GTK_WINDOW(window),"选择日期");
gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
gtk_container_set_border_width(GTK_CONTAINER(window),20);
box = gtk_vbox_new(FALSE,0);
gtk_container_add(GTK_CONTAINER(window),box);
calendar = gtk_calendar_new();
gtk_box_pack_start(GTK_BOX(box),calendar,FALSE,FALSE,5);
button = gtk_button_new_from_stock(GTK_STOCK_OK);
gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);
g_signal_connect(G_OBJECT(button),"clicked",
G_CALLBACK(on_ok_clicked),calendar);
gtk_widget_show_all(window);
gtk_main();
return FALSE;
}
