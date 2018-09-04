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

void send_file(char* src)
{
	char buf[MAX_LEN];
	memset(buf, 0, sizeof(buf));
	
    int fd = open(src,O_RDONLY);
	if (fd < 0)
	{
		
	}

}

//定义服务线程
void do_server(gpointer id)
{
	char tobuf[MAX_LEN];
	char target[64];
	char temp[MAX_LEN];
	int flag = 0;

	while (read(user[GPOINTER_TO_INT(id)].sd, user[GPOINTER_TO_INT(id)].buf, MAX_LEN) != -1)
	{
		if (strcmp(user[GPOINTER_TO_INT(id)].buf, "CONNECT_CLOSE") == 0)
			break;
		
		memset(tobuf, 0, sizeof(tobuf));
		memset(target, 0, sizeof(target));
		memset(temp, 0, sizeof(temp));

		sprintf(tobuf, "%s", user[GPOINTER_TO_INT(id)].name);
		sprintf(target, "%s", user[GPOINTER_TO_INT(id)].target);
		sprintf(temp, "%s", user[GPOINTER_TO_INT(id)].buf);
		strcat(tobuf, " ");
		strcat(tobuf, temp);
		strcpy(temp, tobuf);

		if (strcmp(target, "ALL") == 0)
		{
			for (int i = 0; i < MAX_USERS; i++)
			{
				if (user[i].in_use)
				{
					write(user[i].sd, tobuf, MAX_LEN);
					g_print("%s", tobuf);
				}
			}
		}
		else
		{
			flag = 0;
			for (int i = 0; i < MAX_USERS; i++)
			{
				if (user[i].in_use && strcmp(target, user[i].name) == 0)
				{
					write(user[i].sd, tobuf, MAX_LEN);
					g_print("%s", tobuf);
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				sprintf(tobuf, "Target offline\n");
				write(user[GPOINTER_TO_INT(id)].sd, tobuf, MAX_LEN);
			}
			else
			{
				write(user[GPOINTER_TO_INT(id)].sd, temp, MAX_LEN);
			}
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

	for(int i = 0; i < MAX_USERS; i++)
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

				int a = 0, b = 0, flag = 0;
				for (int i = 0; i < strlen(temp); i++)
				{
					if (temp[i] == ';')
						flag = 1;
					else if (flag == 0)
						user[count].name[a++] = temp[i];
					else
						user[count].target[b++] = temp[i];
				}
				
				g_thread_new(user[count].name, (GThreadFunc)do_server, (gpointer)count);
				count++;
			}
		}
	}

	close(sd);
	g_free(sin);

	return 0;
}
