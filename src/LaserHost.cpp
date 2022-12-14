#include "LaserHost.hpp"
#include "vLog.hpp"

LaserHost::LaserHost(){
    bool success;
    this->listenerSocket = new LinuxSocket(AF_INET, SOCK_STREAM, 0, success);
    
    if(!success){
        vLog("Failed to create listening socket!\n");
        exit(-1);
    }

    LinuxInetAddr listenAddr;

	memset(&listenAddr.addr, 0, sizeof(listenAddr.addr));
    listenAddr.addr.sin_family = AF_INET;
    listenAddr.addr.sin_addr.s_addr = htonl(INADDR_ANY);
    listenAddr.addr.sin_port = htonl(1001);
    listenerSocket->Bind(&listenAddr);
    
    if(listenerSocket->Listen(8) < 0 ){ //listen with up to 8 connections on the queue
        vLog("Error setting up listening socket\n");
        exit(-1);
    }
}

void LaserHost::run(){
    while(1){
        LinuxInetAddr newConnAddr;
        LinuxSocket* newConn = dynamic_cast<LinuxSocket*>(listenerSocket->Accept(&newConnAddr));
        {
        char tmp[100];
        snprintf(tmp, sizeof(tmp), "Client Connected: IP: %s port: %i\n", inet_ntoa(newConnAddr.addr.sin_addr), ntohs(newConnAddr.addr.sin_port));
        std::string msg = tmp;
        vLog(msg);
        }

        //recieve commands from socket
        while(1) {
            LaserHostCommand cmd;                  //MSG_DONTWAIT
            int bytesRcvd = newConn->Recv((void*)cmd, sizeof(cmd), 0);
            if(bytesRcvd > 0){
                this->handleCommand(cmd);
            } else {
                break;
            }
        }

        delete newConn;
    }
}

void LaserHost::handleCommand(LaserHostCommand cmd){
    if(cmd == LaserHostCommand::ENABLE){
        std::cout << "ENABLE!\n";
    }
}
