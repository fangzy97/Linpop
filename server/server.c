/********************************************************************************
 * Files         : server.c
 * Description   : 该模块用于将用户名和密码插入数据库
 ********************************************************************************/
#include "server.h"

#define OURPORT 8088
#define MAX_USERS 10 
#define MAX_LEN 2048
#include<mysql/mysql.h>
MYSQL conn;

void connection(const char* host, const char* user, const char* password, const char* database) {
    mysql_init(&conn); // 注意取地址符&
 
    if (mysql_real_connect(&conn, host, user, password, database, 0, NULL, 0)) {
        printf("Connection success!\n");
    } else {
        fprintf(stderr, "Connection failed!\n");
        if (mysql_errno(&conn)) {
            fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
        }
        exit(EXIT_FAILURE);
    }
}
struct _client 
{
	gint sd;
	gboolean in_use;
	gchar name[64];
	gchar password[64];
	gchar buf[MAX_LEN];
	gchar target[64];
};
typedef struct _client client;

//用户数据信息
client user[MAX_USERS];

void sys_err(const char* ptr, int num)
{
	perror(ptr);
	exit(num);
}

void get_file(char* buf)
{
	int filefd = open("file.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);
	write(filefd, buf, strlen(buf));
	close(filefd);
}

/* 
    名称：getTarget
    描述：获取发送对象的相关通知
    做成日期：18/09/06
    参数：char* str
    返回值：char*
    作者：孙凡淑
*/
char* getTarget(char* str)
{
	char* result;
	result = (char*)malloc(sizeof(char) * 64);
	memset(result, 0, sizeof(result));

	int num = 0;
	for (int i = 2; i < strlen(str); i++)
	{
		if (str[i] == ';') break;

		result[num++] = str[i];
	}

	return result;
}

/* 
    名称：getMessage
    描述：在客户端法来的消息中获取有用消息
    做成日期：18/09/06
    参数：char* str
    返回值：char*
    作者：方致远
*/
char* getMessage(char* str)
{
	printf("get_message\n");
	printf("%s\n", str);

	char* result;
	result = (char*)malloc(sizeof(char) * MAX_LEN);
	memset(result, 0, sizeof(result));

	int flag = 0, num = 0;
	for (int i = 2; i < strlen(str); i++)
	{
		if (str[i] == ';' && flag == 0) 
		{
			flag = 1;
			continue;
		}

		if (flag == 1)
		{
			result[num++] = str[i];
		}
	}
	printf("%s\n", result);
	return result;
}

/* 
    名称：getMessage
    描述：用于定义服务线程，开启多线程
    做成日期：18/09/06
    参数：gpointer id
    返回值：void
    作者：方致远
*/
void do_server(gpointer id)
{
	char mod;
	char tobuf[MAX_LEN];
	char target[64];
	char temp[MAX_LEN], temp2[MAX_LEN];
	int flag = 0;

	while (read(user[GPOINTER_TO_INT(id)].sd, user[GPOINTER_TO_INT(id)].buf, MAX_LEN) != -1)
	{	
		memset(tobuf, 0, sizeof(tobuf));
		memset(target, 0, sizeof(target));
		memset(temp, 0, sizeof(temp));

		mod = user[GPOINTER_TO_INT(id)].buf[0];
		if (mod == '0')
		{
			printf("%s offline\n", user[GPOINTER_TO_INT(id)].name);
			break;
		}
		else if (mod == '1')
		{
			strcpy(tobuf, user[GPOINTER_TO_INT(id)].name);
			strcpy(target, getTarget(user[GPOINTER_TO_INT(id)].buf));
			strcpy(temp, getMessage(user[GPOINTER_TO_INT(id)].buf));
			strcat(tobuf, ": ");
			strcat(tobuf, temp);
			strcat(tobuf, "\n");

			memset(temp2, 0, sizeof(temp2));
			strcpy(temp2, "1:");
			strcat(temp2, tobuf);

			if (strcmp(target, "ALL") == 0)
			{
				for (int i = 0; i < MAX_USERS; i++)
				{
					if (user[i].in_use)
					{
						write(user[i].sd, temp2, MAX_LEN);
						g_print("%s\n", temp2);
					}
				}
			}
			else
			{
				for (int i = 0; i < MAX_USERS; i++)
				{
					if (user[i].in_use && (strcmp(user[i].name, target) == 0 || i == GPOINTER_TO_INT(id)))
					{
						write(user[i].sd, temp2, MAX_LEN);
						g_print("%s\n", temp2);
					}
				}
			}
		}
		else if (mod == '2')
		{
			printf("文件传输\n");

			strcpy(tobuf, user[GPOINTER_TO_INT(id)].name);
			strcpy(target, getTarget(user[GPOINTER_TO_INT(id)].buf));
			strcpy(temp, getMessage(user[GPOINTER_TO_INT(id)].buf));

			memset(temp2, 0, sizeof(temp2));
			strcpy(temp2, "2:");
			strcat(temp2, temp);

			if (strcmp(target, "ALL") == 0)
			{
				for (int i = 0; i < MAX_USERS; i++)
				{
					if (user[i].in_use)
					{
						write(user[i].sd, temp2, MAX_LEN);
						g_print("%s\n", temp2);
					}
				}
			}
			else
			{
				for (int i = 0; i < MAX_USERS; i++)
				{
					if (user[i].in_use && (strcmp(user[i].name, target) == 0))
					{
						write(user[i].sd, temp2, MAX_LEN);
						g_print("%s\n", temp2);
					}
				}
			}

			get_file(temp);
		}
	}
	user[GPOINTER_TO_INT(id)].in_use = FALSE;
	close(user[GPOINTER_TO_INT(id)].sd);
}

void getUserName(char *buf, int id)
{
	int num = 0;
	for (int i = 0; i < strlen(buf); i++)
	{
		if (buf[i] == ';') break;

		user[id].name[num++] = buf[i];
	}
}

void getPassword(char *buf, int id)
{
	int num = 0, flag = 0;
	for (int i = 0; i < strlen(buf); i++)
	{
		if (buf[i] == ';' && flag == 0)
		{
			flag = 1;
			continue;
		}
		if (flag == 1)
		{
			user[id].password[num++] = buf[i];
		}
	}
}

int main(int argc, char* argv[])
{
	gint sd, newsd;
	struct sockaddr_in *sin;
	gint slen;
	gint count = 0;
	gint flags;
	gchar buf[MAX_LEN];
	gchar tobuf[MAX_LEN];
	gint length,i,j;
	
	int flag;
	char login_sign[64];

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		g_print("create socket error");
		return -1;
	}

	memset(&sin, 0, sizeof(sin));
	sin = g_new(struct sockaddr_in, 1);
	sin->sin_family = AF_INET;
	sin->sin_port = htons(OURPORT);
	slen = sizeof(struct sockaddr_in);

	if (bind(sd, (struct sockaddr*)sin, slen) < 0)
	{
		g_print("bind error\n");
		return -1;
	}

	if(listen(sd, 8) < 0)
	{
		g_print("listen error!\n");
		return -1;
	}

	for(i = 0; i < MAX_USERS; i++)
		user[i].in_use = FALSE;

	flags = fcntl(sd, F_GETFL);
	fcntl(sd, F_SETFL, flags & ~O_NDELAY);

	while (1)
	{
		newsd = accept(sd, (struct sockaddr*)sin, &slen);
		if (newsd == -1)
		{
			g_print("accept error!\n");
			break;
		}
		else
		{
			if(count >= MAX_USERS)
			{
				sprintf(buf, "用户数量过多服务器不能连接。\n");
				write(newsd, buf, MAX_LEN);
				close(newsd);
			}
			else
			{
				flags = fcntl(user[i].sd, F_GETFL);
				fcntl(user[i].sd, F_SETFL, O_NONBLOCK);
				user[count].sd = newsd;
				user[count].in_use = TRUE;

				gchar temp[128];
				memset(temp, 0, sizeof(temp));
				read(newsd, temp, 128);

				getUserName(temp, count);
				getPassword(temp, count);

				// insert(user[count].name, user[count].password);
                char comm[1024]="\0";
                sprintf(comm,"insert into useronline values ('%s','%s');",user[count].name,user[count].password);
                mysql_query(&conn,comm);

				memset(login_sign, 0, sizeof(login_sign));
				// flag = check(user[count].name, user[count].password);
				// printf("%d\n", flag);

				g_thread_new(user[count].name, (GThreadFunc)do_server, (gpointer)count);
				count++;
			}
		}
	}

	close(sd);
	g_free(sin);
	mysql_close(&conn);
    exit(EXIT_SUCCESS);

	return 0;
}
