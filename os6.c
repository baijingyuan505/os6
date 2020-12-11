#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

#define size 200

void createFile(char* path);
void writeFile(char* path,char* buffer);
void readFile(char* path);
void modifyAuthority(char* path);
void checkAuthority(char* path);

void createFile(char* path)
{
    mode_t auth;
    int file;
    auth=S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IROTH;
    printf("Please enter the path of the file:\n");
    scanf("%s",path);
    printf("The path you enter is:%s\n",path);
    file=open(path,O_RDWR|O_CREAT,auth);
    if(file!=-1)
    {
       printf("Create file successfully!\n");
       close(file);
       }
    else
       printf("Fail to create!\n");
}
void writeFile(char* path,char* buffer)
{
    int file;
    printf("Please enter the file path!\n");
    scanf("%s",path);
    file=open(path,O_WRONLY|O_APPEND);
    if(file!=-1)
    {
       printf("Please enter your string:\n");
       scanf("%s",buffer);
       write(file,buffer,strlen(buffer));
       close(file);
    }
    else
       printf("Can't find this file!\n");
}
void readFile(char* path)
{
    int file;
    printf("Please enter the file path!\n");
    scanf("%s",path);
    file=open(path,O_RDONLY);
    if(file!=-1)
    {
       char buf[size];
       int length=0;
       printf("Please enter the size you want to read:\n");
       scanf("%d",&length);
       read(file,buf,length);
       printf("The thing is:\n");
       printf("%s\n",buf);
       close(file);
    }
    else
       printf("Can't find this file!\n");
}
void modifyAuthority(char* path)
{
    int file;
    mode_t mode;
    int arg;
    printf("Please enter the file path!\n");
    scanf("%s",path);
    printf("Please enter a 8 octal number to modify authority:\n");
    scanf("%o",&mode);
    arg=chmod(path,mode);
    if(arg==0)
      printf("modify successfully!\n");
    else
      printf("Error!\n");
}
void checkAuthority(char* path)
{
    struct stat buf;
    printf("Please enter the file path!\n");
    scanf("%s",path);
    stat(path,&buf);
    printf("The authority of this file is:%o\n",buf.st_mode);
}

int main()
{
    char buffer[size];
    char path[size];
    printf("Welcome to filetools application!\n");
    int choice;
    while(1)
    {
       printf("Please enter your instruction:\n");
       printf("0:exit 1:create file 2:write 3:read 4:modify authority 5:check authorrity\n");
       scanf("%d",&choice);
       switch(choice)
       {
           case 0: printf("Thank you for using!\n");
                   return 0;
           case 1: createFile(path);
                   break;
           case 2: writeFile(path,buffer);
                   break;
           case 3: readFile(path);
                   break;
           case 4: modifyAuthority(path);
                   break;
           case 5: checkAuthority(path);
                   return 0;
       }
    }
    return 0;

}
