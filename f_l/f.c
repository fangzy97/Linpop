#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>

#define MAX_DIRPATH_LEN 512
#define DEFAULT_DIRPATH "Hello world"

void new_file(char dirpath[512],char username[64],char str[2048])  
{  
    //下面是写数据，将数字0~9写入到data.txt文件中  
    char name[70];
    strcpy(name,username);
    strcat(name,".txt");
    printf("%s\n",name);
    dirpath[strlen(dirpath)]='/';
    printf("%s\n",dirpath);

    char path[700];
    strcpy(path,dirpath);
    strcat(path,name);
    printf("%s\n",path);

    FILE *fpWrite=fopen(path,"ab+");  
    if(fpWrite==NULL)  
    {  
        printf("error\n");  
    }

    fprintf(fpWrite,"%s",str);  
    fclose(fpWrite);  
}  
void new_folder(char username[64],char str[2048])
{
	char dirpath[MAX_DIRPATH_LEN];
	struct stat file_start;
	int ret;
	strncpy(dirpath,getenv("HOME"),MAX_DIRPATH_LEN);
	dirpath[strlen(dirpath)]='/';
	strncpy(dirpath + strlen(dirpath), username, MAX_DIRPATH_LEN - strlen(dirpath));//默认的文件夹
    
    ret = stat(dirpath, &file_start);//检查文件夹状态
    if(ret<0)
    {
        if(errno == ENOENT)//是否已经存在该文件夹
        {
            ret = mkdir(dirpath,0777);//创建文件夹
            printf("creat dir '/%s'/\n", dirpath);
            if(ret < 0)
            {
                printf("Could not create directory \'%s\' \n", dirpath);
				printf("error\n");
            }
 
        }
        else
        {
            printf("bad file path\n");
        }
    }

    new_file(dirpath,username,str);
 } 
 
 int main()
 {
 	new_folder("haha","123");
 	new_folder("haha","567");
 }