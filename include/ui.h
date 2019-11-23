#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "keyboard.h"
#include <allegro5/allegro.h>
#include "comm.h"


struct keyboard{
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_EVENT ev;
    lap_comm *comm;

    keyboard(lap_comm *comm_obj);

    void kbmain();
};

#endif