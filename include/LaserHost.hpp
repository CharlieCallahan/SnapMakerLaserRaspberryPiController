#ifndef LASER_HOST_HPP
#define LASER_HOST_HPP
#include "LinuxSocket.hpp"

enum LaserHostCommand{
    NOT_USED,
    ENABLE
};

/**
 * @brief This controls the communication with the external computer and also sends commands to the 
 * laser over the CAN bus
 * 
 */
class LaserHost{
    
    LaserHost();
    
    /**
     * @brief handles new connections
     * listens for commands 
     * executes commands
     * 
     */
    void run();

    void handleCommand(LaserHostCommand cmd);
    
    vSocket* listenerSocket;
    
};

#endif LASER_HOST_HPP