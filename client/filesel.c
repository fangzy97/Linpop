/********************************************************************************
 * Files         : filesel.c
 * Description   : 该模块为客户端主界面左侧的构造模块
 ********************************************************************************/
#include "function.h"

/* 
    名称：on_file_select_ok
    描述：该函数用于文件选择器的确定时间被触发时
    做成日期：18/09/06
    参数：GtkWidget *button, GtkFileSelection *fs
    返回值：void
    作者：唐容川
*/
void on_file_select_ok (GtkWidget *button, GtkFileSelection *fs)
{
    if (file_path != NULL)
    {
        free(file_path);
        file_path = NULL;
    }
    
    file_path = (char*)malloc(sizeof(char) * 4096);
    memset(file_path, 0, sizeof(file_path));

    GtkWidget *dialog;
    gchar message[1024];
    const gchar *filename;
    filename = gtk_file_selection_get_filename(fs);

    memset(message, 0, sizeof(message));
    if(g_file_test(filename,G_FILE_TEST_IS_DIR))
    {
        sprintf(message,"你选择的目录是:%s",filename);
    }
    else
    {
        sprintf(message,"你选择的文件是:%s",filename);
    }
    
    strcpy(file_path, filename);
    printf("%s\n", file_path);

    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(file_buffer), &start, &end);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(file_buffer), &end, filename, strlen(filename));

    // gtk_entry_set_text(GTK_ENTRY(path_entry), "");
    // gtk_entry_set_text(GTK_ENTRY(path_entry), filename);

    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, 
        GTK_MESSAGE_INFO, GTK_BUTTONS_OK, message, NULL);

    gtk_widget_destroy(GTK_WIDGET(fs));
    gtk_dialog_run(GTK_DIALOG(dialog));
    
    gtk_widget_destroy(dialog);
}

/* 
    名称：File_button_clicked
    描述：该函数用于文件选择器的确定时间被触发时
    做成日期：18/09/06
    参数：GtkWidget *button,gpointer userdata
    返回值：void
    作者：唐容川
*/
void File_button_clicked (GtkWidget *button,gpointer userdata)
{
    GtkWidget* dialog ;
    dialog = gtk_file_selection_new("请选择一个文件或目录:");

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_signal_connect(GTK_OBJECT(dialog), "destroy", GTK_SIGNAL_FUNC(gtk_widget_destroy), &dialog);
    gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(dialog)->ok_button), "clicked", 
        GTK_SIGNAL_FUNC(on_file_select_ok), GTK_FILE_SELECTION(dialog));
    
    gtk_signal_connect_object(GTK_OBJECT(GTK_FILE_SELECTION(dialog)->cancel_button), 
        "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy), GTK_OBJECT(dialog));

    gtk_widget_show(dialog);
}

