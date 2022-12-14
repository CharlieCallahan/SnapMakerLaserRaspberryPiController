#include "LinuxSocket.hpp"

LinuxSocket::LinuxSocket(int domain, int type, int protocol, bool& success){
    this->desc = socket(domain, type, protocol);
    if (desc < 0){
        printf("Unable to create socket, code: %i\n",desc);
        success = false;
    } else {
        success = true;
    }
}

int LinuxSocket::Bind(vInetAddress* address){
    LinuxInetAddr* lAddr = dynamic_cast<LinuxInetAddr*>( address);
    if(bind(this->desc, (sockaddr*)&lAddr->addr, sizeof(sockaddr))<0){
        printf("Couldn't bind to the port\n");
        return -1;
    }
    return 1;
}

int LinuxSocket::Listen(int backlog){
    if(listen(desc, backlog) < 0){
        printf("Error while listening\n");
        return -1;
    }
    return 1;
}
 
int LinuxSocket::Recv(void* buffer, int bufferSize, int flags){
    return recv(desc, buffer, bufferSize, flags);
}

int LinuxSocket::Send(void* buffer, int len, int flags){
    return send(desc, buffer, len, flags);
}

vSocket* LinuxSocket::Accept(vInetAddress* clientAddrTarget){
    LinuxInetAddr* lAddr = dynamic_cast<LinuxInetAddr*>(clientAddrTarget);
    int client_size = sizeof(sockaddr);

    int clientSockDesc = accept(desc, (sockaddr*)&lAddr->addr, (socklen_t*)&client_size);
    if (clientSockDesc < 0){
        return NULL;
    }
    LinuxSocket* newSocket = new LinuxSocket();
    newSocket->desc = clientSockDesc;
    
    return newSocket;
}

int LinuxSocket::Connect(vInetAddress* serverAddr){
    LinuxInetAddr* lAddr = dynamic_cast<LinuxInetAddr*>(serverAddr);
    return connect(desc, (sockaddr*) &lAddr->addr, sizeof(sockaddr));
}

int LinuxSocket::SendTo(const void *buf, uint64_t len, int flags, vInetAddress *dest_addr){
    LinuxInetAddr* lAddr = dynamic_cast<LinuxInetAddr*>(dest_addr);

    return sendto(desc, buf, len, flags, (sockaddr*) &lAddr->addr, sizeof(sockaddr));
}

int LinuxSocket::RecvFrom(void *buf, uint64_t len, int flags, vInetAddress *src_addr){
    LinuxInetAddr* lAddr = dynamic_cast<LinuxInetAddr*>(src_addr);
    int addrSz = sizeof(sockaddr);
    return recvfrom(desc,buf,len,flags,(sockaddr*) &lAddr->addr,(socklen_t*)&addrSz);

}