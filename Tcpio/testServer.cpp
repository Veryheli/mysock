//[==============================================================]
//[ @Author: Chenrenhao 
//[ @Created Time : 2021年09月22日 星期三 21时43分08秒
//[==============================================================]

#include <iostream>
#include "TcpServer.h"  //已经包含了基本的socket头文件
void TestServer(char ipaddr[],int port)
{
    Singal_Client_Server s;
    s.initialize(ipaddr,port);
}
int main(int argc,char * argv[])
{
    if(argc != 3)
    {
        std::cout<<"arguments error!"<<std::endl;
        std::cout<<"------------------usage:-------------------"<<std::endl;
        std::cout<<"./testServer [IPADDRESS] [PORT]"<<std::endl;
        exit(EXIT_FAILURE);
    }
    TestServer(argv[1],atoi(argv[2]));
    return 0;
}
