#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include "comm.h"
#include "ui.h"
#include <chrono>
#include <thread>
 
#define PORT 8888

out_state os;

void decide_all(lap_comm *comm, ui *u);

int main(int argc, char *argv[]){
    lap_comm comm = lap_comm(PORT);

    ui u;

    int interval = 20;
    auto time_interval = std::chrono::milliseconds(interval);
    auto time = std::chrono::steady_clock::now();

    while(1){
        time += time_interval;
        //decide_all(&comm, &u);
        std::this_thread::sleep_until(time);
    }
     
    printf("We're done here\n");
     
    return 0;
}

void decide_all(lap_comm *comm, ui *u){

    os = u->read_os();

    comm->write_os(os);

}