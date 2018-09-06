#ifndef FUNCTION_H
#define FUNCTION_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_LEN 2048

struct info 
{
    gchar *name;
	gchar *sex;
	gchar *age;
	gchar *signature;
	int year;
	int month;
	int date;
};

extern char *file_path;
extern GtkWidget *path_entry;
extern gchar username[64];
extern GtkTextBuffer *buffer;
extern GtkWidget *target_entry;
extern GtkWidget *path_entry;
extern GtkTextBuffer *input_buffer;
extern GtkTextBuffer *file_buffer;
extern int isSet;
extern struct info p_info;

void on_file_select_ok (GtkWidget *button, GtkFileSelection *fs);
void File_button_clicked (GtkWidget *button,gpointer userdata);
void download_file(gchar buf[]);
void start_page();
int create_main ();
void calc_button_clicked ( GtkWidget *button1 , gpointer userdata);
void personal_information_button_clicked ( GtkWidget *button , gpointer userdata);
void cale_button_clicked ( GtkWidget *button1 , gpointer userdata);
void File_button_clicked (GtkWidget *button,gpointer userdata);
void on_send (GtkButton* button, gpointer data);
void on_send_file_click();
void new_folder(char username[],char str[]);
void create_history();
void on_destroy(GtkWidget *widget, GdkEvent *event, gpointer data);
void login_stats (int stats);

GtkWidget *create_leftbox();
GtkWidget *create_rightbox();


#endif