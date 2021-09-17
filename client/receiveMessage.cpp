//##############################################################
//# Author: Chenrenhao
//# Created Time : 2021年09月16日 星期四 18时37分57秒
//#=============================================================

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
#define PORT 2222
#define IPADDRESS "192.168.31.123"
int main()
{
    int socketfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if( -1 == socketfd )
    {
        perror("create socket failed");
        exit(EXIT_FAILURE);
    }
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PORT);
    sa.sin_addr.s_addr = inet_addr(IPADDRESS);
    if(-1 == connect(socketfd,(sockaddr *)&sa,sizeof(sa)))
    {
        perror("connect failed");
        close(socketfd);
        exit(EXIT_FAILURE);
    }
    char resiveBuffer[512];
    int totalRead = 0;
    int readSize = 0;
    while(1)
    {
        while(1)
        {
            readSize = read(socketfd,resiveBuffer + totalRead,sizeof(resiveBuffer) - totalRead);
            if(0 == readSize)
            {
                break;
            }else if(-1 == readSize)
            {
                perror("read failed");
                close(socketfd);
                exit(EXIT_FAILURE);
            }
            totalRead += readSize;
        }
        totalRead = 0;
        readSize = 0;
        cout<<resiveBuffer<<endl;
    }
    close(socketfd);
    resiveBuffer[totalRead] = 0;
    return 0;
}

