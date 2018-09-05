#include <gtk/gtk.h>
void
on_file_select_ok (GtkWidget *button,GtkFileSelection *fs)
{
GtkWidget *dialog;
gchar message[1024];
const gchar *filename;
filename = gtk_file_selection_get_filename(fs);
if(g_file_test(filename,G_FILE_TEST_IS_DIR))
sprintf(message,"你选择的目录是:%s",filename);
else
sprintf(message,"你选择的文件是:%s",filename);
dialog = gtk_message_dialog_new(NULL,
GTK_DIALOG_DESTROY_WITH_PARENT,
GTK_MESSAGE_INFO,
GTK_BUTTONS_OK,
message,
NULL);
gtk_widget_destroy(GTK_WIDGET(fs));
gtk_dialog_run(GTK_DIALOG(dialog));
gtk_widget_destroy(dialog);
}
void
File_button_clicked (GtkWidget *button,gpointer userdata)
{
GtkWidget* dialog ;
dialog = gtk_file_selection_new("请选择一个文件或目录:");
gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
gtk_signal_connect(GTK_OBJECT(dialog),"destroy",
GTK_SIGNAL_FUNC(gtk_widget_destroy),&dialog);
gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(dialog)->ok_button),"clicked",GTK_SIGNAL_FUNC(on_file_select_ok),
GTK_FILE_SELECTION(dialog));
gtk_signal_connect_object(
GTK_OBJECT(GTK_FILE_SELECTION(dialog)->cancel_button),
"clicked",
GTK_SIGNAL_FUNC(gtk_widget_destroy),
GTK_OBJECT(dialog));
gtk_widget_show(dialog);
}

