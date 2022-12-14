#ifndef VSOCKET_HPP
#define VSOCKET_HPP
#include <cstdint>

enum vSocketFlag {
    msg_dontwait
};

/**
 * @brief Passed to vSocket.connect 
 * 
 */
class vInetAddress{
public:
    virtual ~vInetAddress(){}
};

/**
 * @brief Virtualized socket, so that actual implementation can be provided separately for each os
 * 
 */

class vSocket{
public:
    virtual ~vSocket(){};

    /**
     * @brief Bind socket to address
     * 
     * @param address pointer to address object
     * @return int -1 if failed
     */
    virtual int Bind(vInetAddress* address)=0;

    /**
     * @brief Marks this socket as a passive socket, which should be used to accept incoming
     * connection requests. Call this before calling accept
     * @param backlog max # of connection requests on the queue before clients get rejected 
     * @return int -1 if failed
     */
    virtual int Listen(int backlog)=0; 

    /**
     * @brief recieves bytes from the socket
     * 
     * @param buffer buffer to write bytes into
     * @param bufferSize max size of buffer
     * @param flags flags
     * @return int number of bytes recieved
     */
    virtual int Recv(void* buffer, int bufferSize, int flags)=0; 

    /**
     * @brief sends len bytes in buffer over connection
     * 
     * @param buffer buffer to send bytes from
     * @param len number of bytes to send
     * @param flags flags
     * @return int number of bytes sent
     */
    virtual int Send(void* buffer, int len, int flags)=0;

    /**
     * @brief extracts the first connection request on the queue or
     * pauses thread execution until a client connects to this socket if
     * the socket is not flagged as non-blocking.
     * the new socket will not be in the listening state.
     * @param clientAddrTarget 
     * @param clientPortTarget 
     * @return Socket* new socket describing 
     */
    virtual vSocket* Accept(vInetAddress* clientAddrTarget)=0;

    /**
     * @brief attempts to connect socket to the server at address
     * 
     * @param serverAddr pointer to address info for server
     * @return int -1 if failed
     */
    virtual int Connect(vInetAddress* serverAddr)=0;

    /**
     * @brief Sends buffer to destination address
     *        Use this for UDP connections
     * 
     * @param buf buffer containing data to send
     * @param len bytes in buffer
     * @param flags flags
     * @param dest_addr 
     * @return int -1 if failed
     */
    virtual int SendTo(const void *buf, uint64_t len, int flags, vInetAddress *dest_addr)=0;

    /**
     * @brief Recieves data from socket, fills in src address with address of sender
     *        Use this for UDP connections
     * @param buf target buffer
     * @param len target buffer size
     * @param flags 
     * @param src_addr target src_addr
     * @return int number of bytes filled in, or -1 if no bytes were available in socket.
     */
    virtual int RecvFrom(void *buf, uint64_t len, int flags, vInetAddress *src_addr)=0;

};
#endif /* VSOCKET_HPP */
