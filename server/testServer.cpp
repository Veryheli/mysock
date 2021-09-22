//[==============================================================]
//[ @Author: Chenrenhao 
//[ @Created Time : 2021年09月22日 星期三 21时43分08秒
//[==============================================================]

#include <iostream>
#include "../Tcpio/TcpServer.h"  //已经包含了基本的socket头文件
#include <string.h>
void TestServer(char ipaddr[],int port)
{
    Singal_Client_Server s;
    s.initialize(ipaddr,port);
}
int main(int argc,char * argv[])
{
    if(argc > 3 || argc == 1)
    {
        std::cout<<std::endl;
        std::cout<<"arguments error!"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"With the argument \"--help\" to get more infomation"<<std::endl;
        exit(EXIT_FAILURE);
    }
    if(argc == 2)
    {
        if(0 == strcmp(argv[1],"--help"))
        {
            std::cout<<"------------------usage:-------------------"<<std::endl;
            std::cout<<std::endl;
            std::cout<<"./testServer [IPADDRESS] [PORT]"<<std::endl;
            std::cout<<std::endl;
            std::cout<<"[IPADDRESS] : The ip address of you server"<<std::endl;
            std::cout<<"[PORT] : The port which you want to use"<<std::endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            std::cout<<std::endl;
            std::cout<<"arguments error!"<<std::endl;
            std::cout<<std::endl;
            std::cout<<"With the argument \"--help\" to get more infomation"<<std::endl;
            exit(EXIT_FAILURE);
        }
    }
    TestServer(argv[1],atoi(argv[2]));
    return 0;
}
