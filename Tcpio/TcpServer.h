//[==============================================================]
//[ @Author: Chenrenhao 
//[ @Created Time : 2021年09月22日 星期三 16时46分51秒
//[==============================================================]

#pragma once
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#define MAX_ 125
#define QUEEN 10
#define MAX_CLIENTS 100
class Singal_Client_Server
{
private:
    int sockfd;
    struct sockaddr_in server_SA;
public:
    struct sockaddr_in client_SA;
    int client_sockfd[MAX_CLIENTS];
    char buffer[MAX_];
    Singal_Client_Server();
    bool initialize(char ipaddr[],int port);
    //创建套接字，绑定信息，设置监听，全部成功返回true
};
