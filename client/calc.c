/********************************************************************************
 * Files         : calc.c
 * Description   : 该模块用于显示日历
 ********************************************************************************/
#include <gtk/gtk.h>
#include <stdlib.h>118
static GtkWidget *entry;
//定义单行输入控件来显示输入输出的数字
gint count = 0 ;
//计位
gdouble nn = 0 ;
//计数一
gdouble mm = 0 ;
//计数二
gint s = 0 ;
//算法
gboolean first = TRUE; //首次输入
gboolean have_dot = FALSE; //是否有小数点
gboolean have_result = FALSE; //是否有结果输出
gchar number[100]; //保存用户输入的数字

/* 
    名称：clear_all
    描述：清除与计算有关的相关信息
    做成日期：18/09/06
    参数：void
    返回值：void
    作者：唐容川
*/
void clear_all(void)
{
    //清除所有相关标记
    gint i;
    gtk_entry_set_text(GTK_ENTRY(entry),"");
    nn = 0;
    mm = 0 ;
    s = 0;
    count = 0 ;
    first = TRUE;
    have_dot = FALSE;
    have_result = FALSE;
    for(i = 0 ; i < 100 ; i++)
    number[i] = '\0';
}

/* 
    名称：on_num_clicked
    描述：处理用户选择数字后的信息
    做成日期：18/09/06
    参数：GtkButton* button被点击按钮 gpointer data有关数据
    返回值：void
    作者：唐容川
*/
void on_num_clicked (GtkButton* button,gpointer data)
{
    //当数定键按下时执行
    const gchar *num;
    gint i;
    if(have_result)
    clear_all();//有结果则全部清除
    if(count == 6) return; //够6位数则不能再输入数字
    count++;
    num = gtk_button_get_label(GTK_BUTTON(button));//取数
    i = g_strlcat(number,num,100);//保存
    if(first)
    nn = strtod(number,NULL);//数一
    else
    mm = strtod(number,NULL);//数二
    gtk_entry_set_text(GTK_ENTRY(entry),number);//显示
}

/* 
    名称：on_dot_clicked
    描述：处理小数点
    做成日期：18/09/06
    参数：GtkButton* button被点击按钮 gpointer data有关数据
    返回值：void
    作者：唐容川
*/
void on_dot_clicked(GtkButton* button,gpointer data)
{
    //当小数点按下时
    gint i;
    if(have_result)
    clear_all();//全部清除

    if(have_dot == FALSE) //如果无小数点则可以
    {
        have_dot = TRUE;
        i = g_strlcat(number,".",100);
        gtk_entry_set_text(GTK_ENTRY(entry),number);
    }
    //如果有小数点则不输出第 5 章
}

void on_clear_clicked(GtkButton* button,gpointer data)
{
    clear_all();//全部清除
}

void on_suan_clicked(GtkButton* button,gpointer data)
{
    //当计算按钮 +,-,*,/ 按下时
    gint i;
    switch(GPOINTER_TO_INT(data))
    {
        case 1: //"+"
        s = 1;
        gtk_entry_set_text(GTK_ENTRY(entry),"");
        first = FALSE ; count = 0; break;
        case 2: //"-"
        s = 2;
        gtk_entry_set_text(GTK_ENTRY(entry),"");
        first = FALSE ; count = 0; break;
        case 3: //"*"
        s = 3;
        gtk_entry_set_text(GTK_ENTRY(entry),"");
        first = FALSE ; count = 0; break;
        case 4: //"/"
        s = 4;
        gtk_entry_set_text(GTK_ENTRY(entry),"");
        first = FALSE ; count = 0; break;
    }
    have_dot = FALSE;
    for(i = 0 ; i < 100 ; i++) //清除数字
        number[i] = '\0';
}

void on_eq_clicked (GtkButton* button,gpointer data)
{
    //当等号键按钮按下时
    double numb;
    gchar num[100];
    gchar *result;
    switch(s)
    {
        case 1: //"+"
        numb = nn+mm;
        break;
        case 2: //"-"
        numb = nn-mm;
        break;
        case 3: //"*"
        numb = nn*mm;
        break;
        case 4: //"/"
        numb = nn/mm;
        break;
    }
    result = g_ascii_dtostr(num,100,numb);
    gtk_entry_set_text(GTK_ENTRY(entry),result);
    have_result = TRUE;
    }
    void calc_button_clicked ( GtkWidget *button1 , gpointer userdata)
    {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *hbox,*hbox1,*hbox2,*hbox3,*hbox4;
    GtkWidget *button;
    GtkWidget *label;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"delete_event",
    G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"计算器");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    hbox = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);
    label = gtk_label_new("Calculator");
    gtk_box_pack_start(GTK_BOX(hbox),label,TRUE,TRUE,5);
    button = gtk_button_new_with_label("C");
    gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,5);
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_clear_clicked),NULL);
    entry = gtk_entry_new();
    gtk_widget_set_direction(entry,GTK_TEXT_DIR_RTL);
    gtk_box_pack_start(GTK_BOX(vbox),entry,FALSE,FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox1,FALSE,FALSE,5);
    button = gtk_button_new_with_label("3");
    gtk_box_pack_start(GTK_BOX(hbox1),button,TRUE,TRUE,5);
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_num_clicked),NULL);
    button = gtk_button_new_with_label("2");
    gtk_box_pack_start(GTK_BOX(hbox1),button,TRUE,TRUE,5);
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_num_clicked),NULL);
    button = gtk_button_new_with_label("1");
    gtk_box_pack_start(GTK_BOX(hbox1),button,TRUE,TRUE,5);
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_num_clicked),NULL);
    button = gtk_button_new_with_label("+");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_suan_clicked),(gpointer)1);
    gtk_box_pack_start(GTK_BOX(hbox1),button,TRUE,TRUE,5);
    hbox2 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox2,FALSE,FALSE,5);
    button = gtk_button_new_with_label("6");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_num_clicked),NULL);
    gtk_box_pack_start(GTK_BOX(hbox2),button,TRUE,TRUE,5);
    button = gtk_button_new_with_label("5");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_num_clicked),NULL);
    gtk_box_pack_start(GTK_BOX(hbox2),button,TRUE,TRUE,5);
    button = gtk_button_new_with_label("4");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_num_clicked),NULL);
    gtk_box_pack_start(GTK_BOX(hbox2),button,TRUE,TRUE,5);
    button = gtk_button_new_with_label("-");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_suan_clicked),(gpointer)2);
    gtk_box_pack_start(GTK_BOX(hbox2),button,TRUE,TRUE,5);
    hbox3 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox3,FALSE,FALSE,5);
    button = gtk_button_new_with_label("9");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_num_clicked),NULL);
    gtk_box_pack_start(GTK_BOX(hbox3),button,TRUE,TRUE,5);
    button = gtk_button_new_with_label("8");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_num_clicked),NULL);
    gtk_box_pack_start(GTK_BOX(hbox3),button,TRUE,TRUE,5);
    button = gtk_button_new_with_label("7");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_num_clicked),NULL);
    gtk_box_pack_start(GTK_BOX(hbox3),button,TRUE,TRUE,5);
    button = gtk_button_new_with_label("*");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_suan_clicked),(gpointer)3);
    gtk_box_pack_start(GTK_BOX(hbox3),button,TRUE,TRUE,5);
    hbox4 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox4,FALSE,FALSE,5);
    button = gtk_button_new_with_label("0");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_num_clicked),NULL);
    gtk_box_pack_start(GTK_BOX(hbox4),button,TRUE,TRUE,5);
    button = gtk_button_new_with_label(".");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_dot_clicked),NULL);
    gtk_box_pack_start(GTK_BOX(hbox4),button,TRUE,TRUE,5);
    button = gtk_button_new_with_label("=");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_eq_clicked),NULL);
    gtk_box_pack_start(GTK_BOX(hbox4),button,TRUE,TRUE,5);
    button = gtk_button_new_with_label("/");
    g_signal_connect(G_OBJECT(button),"clicked",
    G_CALLBACK(on_suan_clicked),(gpointer)4);
    gtk_box_pack_start(GTK_BOX(hbox4),button,TRUE,TRUE,5);
    gtk_widget_show_all(window);
    gtk_main();
    return FALSE;
}
