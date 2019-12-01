#ifndef COMM_H
#define COMM_H
#include "comm.h"
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <mutex>

#define inBuff 33
#define outBuff 5

struct out_state{
    volatile bool W = 0, A = 0, S = 0, D = 0;
    bool trajTrack = 0;
    char speed = 0;
};

union fval{
    float f = 0;
    uint8_t c[4];
};

struct integrated_data{
    fval x, y, z;
    fval vx, vy, vz;
    fval rx, ry, rz;
    fval temp;
};

struct in_state{
    bool W = 0, A = 0, S = 0, D = 0;
    char speed = 0;
};

struct in_data{
    in_state is;
    integrated_data id;
};


struct lap_comm{
    // TCP info
    int socket_desc, sockfd, read_size;
    struct sockaddr_in server, client;

    // Data and variables
    char out_mess[outBuff];
    out_state os;
    char in_mess[inBuff];
    in_data id;
    std::mutex *read_mtx, *write_mtx;

    lap_comm(const int PORT);

    void main();
    void send_data_out();
    void get_data_in();

    in_data read_data();
    void write_data(char idx, int val);
};
#endif