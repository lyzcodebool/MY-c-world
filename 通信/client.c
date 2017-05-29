/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Tue 16 May 2017 08:05:50 PM PDT
 ************************************************************************/

#include<stdio.h>
//客户端
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include"getstr.h"

int main(int argc, char *argv)
{
    int client_fd;
    int len;
    struct sockaddr_in remote_addr;//服务器网络地址结构体

    char buf[BUFSIZ];//数据缓冲区
    memset(&remote_addr, 0, sizeof(remote_addr));

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//服务器的IP地址
    remote_addr.sin_port = htons(8000);//服务器端口号

    if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    if(connect(client_fd, (struct sockaddr*)&remote_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }

    printf("connect to server successful!\n");

    //发送和接收数据
    while(1)
    {
//        scanf("%s", buf);
        gets(buf);
        len =  send(client_fd,buf, BUFSIZ, 0);
        if(strcmp(buf, "\n"))
        {
                break;
        }
       // send(client_fd, buf, BUFSIZ,0);

        //接受服务器端信
    }

    close(client_fd);
}
