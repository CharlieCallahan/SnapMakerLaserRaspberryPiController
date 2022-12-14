#ifndef LINUXSOCKET_HPP
#define LINUXSOCKET_HPP
#include "vSocket.hpp"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

class LinuxInetAddr : public vInetAddress{
public:
    ~LinuxInetAddr(){}
    struct sockaddr_in addr;
};

class LinuxSocket : public vSocket{

public:
    LinuxSocket(int domain, int type, int protocol, bool& success);

    LinuxSocket(){};

    ~LinuxSocket(){
        close(this->desc);
    }

    int Bind(vInetAddress* address) override;

    int Listen(int backlog) override;

    int Recv(void* buffer, int bufferSize, int flags) override; 

    int Send(void* buffer, int len, int flags) override;

    vSocket* Accept(vInetAddress* clientAddrTarget) override;

    int Connect(vInetAddress* serverAddr) override;

    int SendTo(const void *buf, uint64_t len, int flags, vInetAddress *dest_addr) override;

    int RecvFrom(void *buf, uint64_t len, int flags, vInetAddress *src_addr) override;

public:
    int desc; //socket descriptor
};

#endif /* LINUXSOCKET_HPP */
