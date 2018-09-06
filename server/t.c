#include<mysql/mysql.h>
#include<errno.h>
#include<stdio.h>

int check(char * username,char *password)
{
MYSQL conn;
MYSQL_RES *res;
  mysql_init(&conn); // 注意取地址符&
 if (mysql_real_connect(&conn, "localhost", "root", "123", "talk",0, NULL,0)) {
        printf("Connection success!\n");
    }
  
  
  char comm[1024]="\0";
  sprintf(comm,"select * from user where uaername = '%s' and password = '%s';",
            username,password);
    if (mysql_query(&conn,comm))
    {
        
    }
res=mysql_store_result(&conn);
int num=mysql_num_rows(res);
mysql_free_result(res);
mysql_close(&conn);
if(num)
return 1;
else
return 0;
}
// int main()
// {
// int b=check("zzz","zzz");
// int a=check("zzz","ppp");
// printf("%d\n",b);
// printf("%d",a);
// }
