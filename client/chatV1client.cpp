//==============================================================
// @Author: Chenrenhao
// @Created Time : 2021年09月17日 星期五 14时01分00秒
//=============================================================

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <string.h>
using namespace std;
void sendMessage(int sockfd)
{
    while(1)
    {
        char data[52];
        cout<<"输入要发送的信息:"<<endl;
        cin>>data;
        if(-1 == send(sockfd,data,sizeof(data),0))
        {
            perror("send faild");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        memset(data,0,sizeof(data));
    }
}
void ressiveMessage(int sockfd)
{
    while(1)
    {
        char buffer[512];
        memset(buffer,0,sizeof(buffer));
        if(-1 == recv(sockfd,buffer,512,0))
        {
            perror("recv faild");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        if(strlen(buffer) != 0)
        {
            cout<<"接收到的信息："<<buffer<<endl;
        }
        memset(buffer,0,sizeof(buffer));
    }
}

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        cout<<"usage:"<<endl;
        cout<<"./chatV1client.out host port"<<endl;
        exit(EXIT_FAILURE);
    }
    int socketfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(-1 == socketfd)
    {
        perror("create socket faild");
        exit(EXIT_FAILURE);
    }

    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(argv[1]);
    sa.sin_port = htons(atoi(argv[2]));
    if(-1 == connect(socketfd,(sockaddr *)&sa,sizeof(sa)))
    {
        perror("connect faild");
        close(socketfd);
        exit(EXIT_FAILURE);
    }
    cout<<"连接成功"<<endl;
    thread send(sendMessage,socketfd);
    thread ressive(ressiveMessage,socketfd);
    if(ressive.joinable())
        ressive.join();
    if(send.joinable())
        send.join();
    ressiveMessage(socketfd);
   return 0;
}
