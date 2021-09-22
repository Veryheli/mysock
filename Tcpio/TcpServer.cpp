//[==============================================================]
//[ @Author: Chenrenhao 
//[ @Created Time : 2021年09月22日 星期三 16时57分09秒
//[==============================================================]
#include <iostream>
#include "TcpServer.h"
#include <string.h>
#include <stdlib.h>
Singal_Client_Server::Singal_Client_Server()
{
    memset(this->buffer,0,sizeof(this->buffer));
    memset(&this->client_SA,0,sizeof(this->client_SA));
    memset(&this->server_SA,0,sizeof(this->server_SA));
    memset(client_sockfd,0,sizeof(client_sockfd));
    this->sockfd = -1;
}
bool Singal_Client_Server::initialize(char ipaddr[],int port)
{
    bool initialize_Success = false;
    this->sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == this->sockfd)
    {
        perror("sock creat failed");
        exit(EXIT_FAILURE);
    }
    this->server_SA.sin_addr.s_addr = inet_addr(ipaddr);
    this->server_SA.sin_family = AF_INET;
    this->server_SA.sin_port = htons(port);
    if(-1 == bind(this->sockfd,(struct sockaddr*)&this->server_SA,sizeof(this->server_SA))) 
    {
        perror("bind failed");
        close(this->sockfd);
        exit(EXIT_FAILURE);
    }
    if(-1 == listen(this->sockfd,QUEEN))
    {
        perror("listen failed");
        close(this->sockfd);
        exit(EXIT_FAILURE);
    }
    std::cout<<"server start success"<<std::endl;
    while(int i = 0 < 101)
    {
        socklen_t size = sizeof(this->server_SA);
        this->client_sockfd[i] = accept(this->sockfd,(struct sockaddr *)&this->client_SA,&size);
        if(-1 == this->client_sockfd[i])
        {
            perror("client failed");
            close(this->sockfd);
            for(int m = 0;m < i;m ++)
            {
                close(this->client_sockfd[m]);
            }
            exit(EXIT_FAILURE);
        }
        if(i != 100) 
        {
            ++i;
        }
    }
    return initialize_Success;
}
