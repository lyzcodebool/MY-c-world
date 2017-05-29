/*************************************************************************
	> File Name: client2.c
	> Author: 
	> Mail: 
	> Created Time: Tue 02 May 2017 04:03:25 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    int client_sockfd;
    int len;
    struct sockaddr_in remote_addr; //服务器端网络地址结构体

    char buf[BUFSIZ]; //数据传送的缓冲区
    memset(&remote_addr, 0, sizeof(remote_addr)); //数据初始化，清零

    remote_addr.sin_family = AF_INET; //设置为IP通讯
    remote_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//服务器IP地址
    remote_addr.sin_port = htons(8000); //服务器端口号

    //创建服务器端套接字-IPv4协议，面向连接通信，TCP协议
    if((client_sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return 1;
    }

    //将套接字绑定到服务器的网络地址上
    if(connect(client_sockfd, (struct sockaddr *)&remote_addr,sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        return 1;
    }

    printf("Connected to surver!\n");
    len = recv(client_sockfd, buf, BUFSIZ, 0); //接收服务器端信息

    buf[len] = '\0';
    printf("%s", buf); //打印服务端信息

    //循环的发送接受信息并打印接收信息 --recv返回接收到的字节数，send返回发送的字节数
    while(1)
    {
       // buf[len] = '\0';
        scanf("%s",buf);
        if(!strcmp(buf, "quit"))
        {
            break;
        }
        send(client_sockfd, buf, strlen(buf), 0);
        len = recv(client_sockfd, buf, BUFSIZ, 0);
        //len = recv(client_sockfd, buf, BUFSIZ, 0);
        buf[len] = '\0';
        printf("Server: %s\n", buf);
        //len = send(client_sockfd, buf, strlen(buf), 0);
    }

    close(client_sockfd);//关闭套接字
    return 0;
}
