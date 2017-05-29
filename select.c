/*************************************************************************
	> File Name: select.c
	> Author: 
	> Mail: 
	> Created Time: Mon 01 May 2017 03:19:44 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<unistd.h>

#define MYPORT 4000 //服务器要监听的本地端口
#define BACKLOG 10 //能够同时接受多少个链接

void main()
{
    /*在socket_fd 上进行监听；new_fd接收新的链接*/
    int sock_fd, new_fd, numbytes;
    char buf[100];
    //自己的地址信息
    struct sockaddr_in my_addr;
    //连接者的地址信息
    struct sockaddr_in their_addr;


    int sin_size;
    //这里就是我们一直强调的错误检查，如果调用socket（）出错，则返回
   if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET;

    my_addr.sin_port = htons(MYPORT);

    my_addr.sin_addr.s_addr = INADDR_ANY;

    bzero(&(my_addr.sin_zero), 8);

    if(bind(sock_fd, (struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    if(listen(sock_fd, 10)== -1)
    {
        perror("listen");
        exit(1);
    }

    while(1)
    {
        //这是主accept()循环
        sin_size = sizeof(struct sockaddr_in);
        
        if((new_fd = accept(sock_fd, (struct sockaddr *) &their_addr, &sin_size)) == -1)
        {
            perror("accept");
            continue;
        }

        printf ("server:got contion from %s\n", inet_ntoa(their_addr.sin_addr));
        
       // len = read()
            if(send(new_fd, buf, 14, 0) == -1)
            {
            perror("send");
                close(new_fd);
            exit(0);
            }
            close(new_fd);

    if((numbytes = recv(sock_fd, buf, 14, 0)) == -1)
        {
            perror("recv");
            exit(1);
        }
        buf[numbytes] = '\0';
        printf("%s\n", buf);
        
    }
    while(waitpid(-1, NULL, WNOHANG ) > 0);
}
