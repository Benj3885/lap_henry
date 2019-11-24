#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "ui.h"
#include <allegro5/allegro.h>
#include "comm.h"

#define SCREEN_W 640
#define SCREEN_H 480


struct ui{
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_EVENT ev;
    lap_comm *comm;

    ui(lap_comm *comm_obj);

    void kbmain();
    void guimain();
};

#endif