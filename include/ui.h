#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "ui.h"
#include <allegro5/allegro.h>
#include "comm.h"

#define SCREEN_W 1440
#define SCREEN_H 900

ALLEGRO_DISPLAY *display;
ALLEGRO_FONT *font;
ALLEGRO_FONT *fontb;


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

struct ui{
    
    lap_comm *comm;

    in_state is;

    char key; 

    ui(lap_comm *comm_obj);

    void kbmain();
    void guimain();
    void create_frame(char xpos[], char ypos[], char zpos[], char speedn[], float a, float b, char keypress);
};

#endif