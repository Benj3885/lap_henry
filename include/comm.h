#ifndef COMM_H
#define COMM_H
#include "comm.h"
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <mutex>

#define inBuff 5
#define outBuff 5

struct out_state{
    volatile bool W = 0, A = 0, S = 0, D = 0;
    bool trajTrack = 0;
    char speed = 0;
};

struct pose{
    unsigned int x, y, z;
    unsigned int rx, ry, rz;
};
struct in_state{
    bool W = 0, A = 0, S = 0, D = 0;
    char speed = 0;
    pose p;
    
    uint last_read = 0;
};

struct lap_comm{
    // TCP info
    int socket_desc, sockfd, read_size;
    struct sockaddr_in server, client;

    // Data and variables
    char out_mess[outBuff];
    out_state os;
    char in_mess[inBuff];
    in_state is;
    std::mutex *read_mtx, *write_mtx;

    lap_comm(const int PORT);

    void main();
    void send_data_out();
    void get_data_in();

    in_state read_data();
    void write_data(char idx, int val);
};





#endif