#include "keyboard.h"
#include <allegro5/allegro.h>
#include "comm.h"
#include <thread>

keyboard::keyboard(lap_comm *comm_obj){
    comm = comm_obj;

    const int SCREEN_W = 640;
    const int SCREEN_H = 480;

    al_init();
    al_install_keyboard();
    al_create_display(SCREEN_W, SCREEN_H);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    std::thread kbthread(&keyboard::kbmain, this);
    kbthread.detach();
}

void keyboard::kbmain(){
    while(1){
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_W:
                    comm->write_data(0, 1);
                    break;
                case ALLEGRO_KEY_A:
                    comm->write_data(1, 1);
                    break;
                case ALLEGRO_KEY_S:
                    comm->write_data(2, 1);
                    break;
                case ALLEGRO_KEY_D:
                    comm->write_data(3, 1);
                    break;
                case ALLEGRO_KEY_R:
                    comm->write_data(4, 1);
                    break;
                case ALLEGRO_KEY_F:
                    comm->write_data(4, -1);
                    break;
            } 
        } else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_W:
                    comm->write_data(0, 0);
                    break;
                case ALLEGRO_KEY_A:
                    comm->write_data(1, 0);
                    break;
                case ALLEGRO_KEY_S:
                    comm->write_data(2, 0);
                    break;
                case ALLEGRO_KEY_D:
                    comm->write_data(3, 0);
                    break;
            }
        }
    }
}