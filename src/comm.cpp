#include "comm.h"
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <stdio.h>
#include <chrono>
#include <thread>
#include <mutex>

lap_comm::lap_comm(const int PORT){
    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
     
    
    //Bind
    if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        //print the error message
        printf("Socket bind failed\n");
        exit(0);
    }
    printf("Socket bind done\n");
     
    //Listen
    listen(socket_desc, 3);
    
    int c = sizeof(struct sockaddr_in);
     
    printf("Waiting for incoming connections...\n");
    sockfd = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (sockfd < 0){
        printf("Accept failed\n");
        exit(0);
    }

    printf("Connection accepted\n");

    read_mtx = new std::mutex();
    write_mtx = new std::mutex();

    std::thread commthread(&lap_comm::main, this);
    commthread.detach();
}

void lap_comm::main(){
    int interval = 20;
    auto time_interval = std::chrono::milliseconds(interval);
    auto time = std::chrono::steady_clock::now();

    while(1){
        time += time_interval;
        //send_data_out();
        get_data_in();
        std::this_thread::sleep_until(time);
    }
}

void lap_comm::send_data_out(){
    write_mtx->lock();

    printf("%d %d %d %d\n", os.W, os.A, os.S, os.D);

    out_mess[0] = (char)os.W;
    out_mess[1] = (char)os.A;
    out_mess[2] = (char)os.S;
    out_mess[3] = (char)os.D;
    out_mess[4] = os.speed;

    write_mtx->unlock();

    write(sockfd, out_mess, 5);
    
}

void lap_comm::write_data(char idx, int val){
    std::lock_guard<std::mutex> lock(*write_mtx);

    switch(idx){
        case 0:
            os.W = val;
            break;
        case 1:
            os.A = val;
            break;
        case 2:
            os.S = val;
            break;
        case 3:
            os.D = val;
            break;
        case 4:
            os.speed = val;
            break;
        case 5:
            os.trajTrack = val;
            break;
    }
}

void lap_comm::get_data_in(){
    recv(sockfd, in_mess, inBuff, 0);
    
    read_mtx->lock();

    id.is.W = in_mess[0];
    id.is.A = in_mess[1];
    id.is.S = in_mess[2];
    id.is.D = in_mess[3];
    id.is.speed = in_mess[4];

    int idx = 5;
    for(int i = 0; i < 4; i++){
        id.id.x.c[i] = in_mess[idx]; idx++;
    }
    for(int i = 0; i < 4; i++){
        id.id.y.c[i] = in_mess[idx]; idx++;
    }
    for(int i = 0; i < 4; i++){
        id.id.z.c[i] = in_mess[idx]; idx++;
    }
    for(int i = 0; i < 4; i++){
        id.id.rx.c[i] = in_mess[idx]; idx++;
    }
    for(int i = 0; i < 4; i++){
        id.id.ry.c[i] = in_mess[idx]; idx++;
    }
    for(int i = 0; i < 4; i++){
        id.id.rz.c[i] = in_mess[idx]; idx++;
    }
    for(int i = 0; i < 4; i++){
        id.id.temp.c[i] = in_mess[idx]; idx++;
    }

    printf("%f\n", id.id.x.f);

    read_mtx->unlock();
}

in_data lap_comm::read_data(){
    std::lock_guard<std::mutex> lock(*read_mtx);
    return id;
}