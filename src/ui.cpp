#include "ui.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "comm.h"
#include <thread>

ui::ui(lap_comm *comm_obj){
    comm = comm_obj;

    al_init();

    al_install_keyboard();

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    std::thread kbthread(&ui::kbmain, this);
    kbthread.detach();

    std::thread guithread(&ui::guimain, this);
    guithread.detach();
}

void ui::kbmain(){
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

void ui::guimain(){
    al_create_display(SCREEN_W, SCREEN_H);
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
    ALLEGRO_FONT *font = al_load_font("fonts/Calibri Regular.ttf", 36, 0);

    al_clear_to_color(al_map_rgb(0,0,0));

    al_draw_text(font, color, 300, 300, 0, "TRIAL TEST");

    al_flip_display();

    while(1){

    }
}