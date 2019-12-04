#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "ui.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <mutex>
#include "comm.h"

#define SCREEN_W 1440
#define SCREEN_H 900



struct ui{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font;
    ALLEGRO_FONT *fontb;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_EVENT ev;

    ALLEGRO_BITMAP *button;
    ALLEGRO_BITMAP *okcom;
    ALLEGRO_BITMAP *nocom;
    ALLEGRO_BITMAP *com;

    ALLEGRO_BITMAP *speed;
    ALLEGRO_BITMAP *sp;

    ALLEGRO_BITMAP *obs;
    ALLEGRO_BITMAP *yesobs;

    ALLEGRO_BITMAP *robpos;
    ALLEGRO_BITMAP *map;

    ALLEGRO_BITMAP *box;

    ALLEGRO_BITMAP *mode;
    ALLEGRO_BITMAP *exp;
    ALLEGRO_BITMAP *climb;
    
    lap_comm *comm;

    out_state os;
    in_state is;

    char key; 

    std::mutex *read_mtx, *write_mtx;

    ui();

    void kbmain();
    void guimain();
    void create_frame(char xpos[], char ypos[], char zpos[], char speedn[], float a, float b, in_state is, char keypress);
    out_state read_os();
    void write_is(in_state is_main);
};

#endif