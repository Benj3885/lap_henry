#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include "comm.h"
#include "ui.h"
#include <chrono>
#include <thread>
 
#define PORT 8888

int main(int argc, char *argv[]){
    lap_comm comm = lap_comm(PORT);

    ui u = ui(&comm);

    int interval = 200;
    auto time_interval = std::chrono::milliseconds(interval);
    auto time = std::chrono::steady_clock::now();

    while(1){
        time += time_interval;

        std::this_thread::sleep_until(time);
    }
     
    printf("We're done here\n");
     
    return 0;
}