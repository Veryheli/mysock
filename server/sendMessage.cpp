//##############################################################
//# Author: Chenrenhao
//# Created Time : 2021年09月15日 星期三 21时41分31秒
//#=============================================================

#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
#define PORT 2222
#define IPADDRESS "192.168.31.123"
#define QUEUE 20 //连接请求列队
int main()
{
    char data[] = "hello world this message is from server";
    int server_socket;

    //创建套接字,第一个参数表示使用ip v4协议，第二个参数表示使用字节流套接字，第三个参数一般为0
    
    server_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//若成功则返回一个sockfd（套接字描述符）
    if(-1 == server_socket)
    {
        perror("create socket failed");
        exit(EXIT_FAILURE);
    }
    sockaddr_in server_addr;//sockaddr 是一个结构体类型，一般用来储存地址和端口，用于信息的显示及储存

    //设置结构体中的相关参数
    
    server_addr.sin_family= AF_INET;//ip4协议族
    server_addr.sin_port = htons(PORT);//本地端口
    //server_addr.sin_addr.s_addr = inet_addr(IPADDRESS);//设置端口
    //INADDR_ANY 就是值地址为0.0.0.0的地址，这个地址事实上是表示不确定的地址或者“所有地址”、“任意地址”
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //将主机无符号长整型数转化为网络字节顺序
    //将套接字和sockaddr进行绑定,第一个参数是套接字描述符，第二个参数要将sockaddr_in的地址转化为sockaddr类型的指针,第三个参数是结构体
    //sockaddr的字节数
    if(-1 == bind(server_socket,(sockaddr *)&server_addr,sizeof(server_addr)))
    {
        perror("bind() error");//如果绑定失败返回错误信息
        close(server_socket);
        exit(EXIT_FAILURE);
        
    }
    if(-1 == listen(server_socket,QUEUE))//创建监听,第一个参数是套接字描述符,第二个参数是连接请求列队
    {
        perror("listen() error");//如果绑定失败返回错误信息
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        int connectfd = accept(server_socket,NULL,NULL);
        if(0 > connectfd)
        {
            perror("accept failed");
            close(server_socket);
            exit(EXIT_FAILURE);
        }
        int writeSize = 0;
        size_t totalWriteSize = 0;
        while(totalWriteSize <= sizeof(data))
        {
            writeSize = write(connectfd,data + totalWriteSize,sizeof(data) - totalWriteSize);
            if(-1 == writeSize)
            {
                perror("write failed");
                close(connectfd);
                close(server_socket);
                exit(EXIT_FAILURE);
            }else if(0 == writeSize)
            {
                break;
            }
            totalWriteSize += writeSize;
        }
        if( -1 == shutdown(connectfd,SHUT_RDWR) )
        {
            perror("shutdown failed");
            close(server_socket);
            close(connectfd);
            exit(EXIT_FAILURE);
        }
        close(connectfd);

    }
    close(server_socket);
    return 0;
}

