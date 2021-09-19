//==============================================================
// @Author: Chenrenhao
// @Created Time : 2021年09月17日 星期五 13时18分56秒
//=============================================================

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <string.h>
#include <vector>
using namespace std;
vector<int> allClients;
static void sendMessage(int sockfd)
{
    char data[512];
    while(1)
    {
        cout<<"输入要发送的信息";
        cin>>data;
        for(auto it = allClients.begin();it != allClients.end();it ++)
        {
            if(-1 == send(*it,data,sizeof(data),0))
            {
                perror("send faild");
                close(*it);
                exit(EXIT_FAILURE);
            }
        }
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
void communicate(int sockfd)
{
    thread rec(ressiveMessage,sockfd);
    rec.detach();
    thread sen(sendMessage,sockfd);
    sen.detach();
}
int main(int argc,char *argv[])
{
    sockaddr_in other;
    socklen_t len = sizeof(sockaddr_in);
    if(argc != 2)
    {
        cout<<"usage:"<<endl;
        cout<<"./chatV1.out port"<<endl;
        exit(EXIT_FAILURE);
    }
    //第一步，创建套接字
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(-1 == sockfd)
    {
        perror("create socket faild");
        exit(EXIT_FAILURE);
    }
    //第二部，设置相关参数
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    //第三部，将socket描述符和相关的配置绑定
    if(-1 == bind(sockfd,(sockaddr*)&server,sizeof(server)))
    {
        perror("bind faild");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    //第四步，创建监听
    if(-1 == listen(sockfd,10))
    {
        perror("listen faild");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        int lastcon = -1;

        int connectfd = accept(sockfd,(sockaddr *)&other,&len);
        if(-1 == connectfd)
        {
            perror("connect faild");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        cout<<"用户"<<other.sin_addr.s_addr<<"已连接！"<<endl;
        if(lastcon != connectfd)
        {
            allClients.push_back(connectfd);
        }
        lastcon = connectfd;
        communicate(connectfd);
    }
   return 0;
}
