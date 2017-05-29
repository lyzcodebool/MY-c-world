/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Tue 16 May 2017 07:26:12 PM PDT
 ************************************************************************/

#include<stdio.h>
//服务器
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include"getstr.h"

int main(int argc, char *argv[])
{
    int server_fd, client_fd;//服务器端套接字，客户端套接字
    int len;//统计接收的字符串大小

    struct sockaddr_in my_addr;//服务器网络的地址结构体
    struct sockaddr_in remote_addr;//客户端网络地址结构体

    int sin_size;//保存结构体大小的变量

    char buf[BUFSIZ]; //数据传送的缓冲区
    memset(&my_addr, 0, sizeof(my_addr));//数据初始化，清零
    //结构体相关设定，设置ip和端口
    my_addr.sin_family = AF_INET;// 协议族定义，设置为ip通讯，相应的还有AP_INET为协议相关，udp
    my_addr.sin_addr.s_addr = INADDR_ANY;//服务器IP地址允许连接到所有本地地址上
    my_addr.sin_port = htons(8000); // 服务器端口号

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }//创建套接字，协议组为ip通信，用流式套接字，即tcp链接

    if(bind(server_fd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }//绑定，将套接字绑定到服务器的网络地址上

    listen(server_fd, 10);//监听套接字，监听的队列长度上限为5

    sin_size = sizeof(struct sockaddr_in);

    if((client_fd = accept(server_fd, (struct sockaddr*)&remote_addr, &sin_size)) == -1)
    {
        perror("accept");
        exit(1);
    }//等待服务器的链接请求，accept产生一个新的套接字，即产生一个新的进程，用来进行服务器和客户端之间的send&recv

    //收发数据，与客户端通信
    

        while((len = recv(client_fd, buf, sizeof(buf), 0)) > 0);
        {
            buf[len] = '\0';//字符结尾
            printf("client： %s\n", buf);
        }
        //向客户端发送消息
    //  scanf("%s",buf);
        while(gets(buf))
        {
            send(client_fd, buf, BUFSIZ, 0);
            if(strcmp(buf, "\n"))
            {
                break;
            }
        }
        //send(client_fd, buf, BUFSIZ, 0);

    close(client_fd);
    close(server_fd);//关闭socket
}
