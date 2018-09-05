/* server.c */
#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <netinet/in.h>

#define OURPORT 8088
#define MAX_USERS 10 
#define MAX_LEN 2048

struct _client 
{
	gint sd;
	gboolean in_use;
	gchar name[64];
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
	int filefd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	write(filefd, buf + 2, strlen(buf) - 2);
	close(filefd);
}

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

char* getMessage(char* str)
{
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

	return result;
}

//定义服务线程
void do_server(gpointer id)
{
	char mod;
	char tobuf[MAX_LEN];
	char target[64];
	char temp[MAX_LEN];
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

			if (strcmp(target, "ALL") == 0)
			{
				for (int i = 0; i < MAX_USERS; i++)
				{
					if (user[i].in_use)
					{
						write(user[i].sd, tobuf, MAX_LEN);
						printf("%s\n", tobuf);
					}
				}
			}
			else
			{
				for (int i = 0; i < MAX_USERS; i++)
				{
					if (user[i].in_use && (strcmp(user[i].name, target) == 0 || i == GPOINTER_TO_INT(id)))
					{
						write(user[i].sd, tobuf, MAX_LEN);
						printf("%s\n", tobuf);
					}
				}
			}
		}
		else if (mod == '2')
		{
			printf("文件传输\n");
			get_file(user[GPOINTER_TO_INT(id)].buf);
		}
	}
	user[GPOINTER_TO_INT(id)].in_use = FALSE;
	close(user[GPOINTER_TO_INT(id)].sd);
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

				gchar temp[64];
				memset(temp, 0, sizeof(temp));
				read(newsd, user[count].name, 64);
				
				g_thread_new(user[count].name, (GThreadFunc)do_server, (gpointer)count);
				count++;
			}
		}
	}

	close(sd);
	g_free(sin);

	return 0;
}
