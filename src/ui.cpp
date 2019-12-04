#include "ui.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "comm.h"
#include <mutex>
#include <thread>
#include <math.h>


ui::ui(){
    write_mtx = new std::mutex;
    read_mtx = new std::mutex;

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_primitives_addon();

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

        read_mtx->lock();

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_W:
                    os.W = 1;
                    printf("Pressing\n");
                    break;
                case ALLEGRO_KEY_A:
                    os.A = 1;
                    break;
                case ALLEGRO_KEY_S:
                    os.S = 1;
                    break;
                case ALLEGRO_KEY_D:
                    os.D = 1;
                    break;
                case ALLEGRO_KEY_R:
                    os.speed = (os.speed < 200 ? os.speed + 1 : os.speed);
                    key = 'R';
                    break;
                case ALLEGRO_KEY_F:
                    os.speed = (os.speed > 0 ? os.speed - 1 : os.speed);
                    key = 'F';
                    break;
            } 
        } else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_W:
                    os.W = 0;
                    break;
                case ALLEGRO_KEY_A:
                    os.A = 0;
                    break;
                case ALLEGRO_KEY_S:
                    os.S = 0;
                    break;
                case ALLEGRO_KEY_D:
                    os.D = 0;
                    break;
                case ALLEGRO_KEY_R:
                    key = 0;
                    break;
                case ALLEGRO_KEY_F:
                    key = 0;
                    break;
            }
        }

        read_mtx->unlock();
    }
}

void ui::guimain(){

    display = al_create_display(SCREEN_W, SCREEN_H);
    al_set_window_position(display, 0, 0);

    font = al_load_font("fonts/Calibri Regular.ttf", 36, 0);
    fontb = al_load_font("fonts/Calibri Regular.ttf", 50, 0);

    box = al_load_bitmap("figures/ok.png");
    button =  al_load_bitmap("figures/test.png");
    okcom=  al_load_bitmap("figures/ok2.png");
    nocom=  al_load_bitmap("figures/no.png");
    com=  al_load_bitmap("figures/connect.png");
    yesobs =  al_load_bitmap("figures/obs.png");
    obs =  al_load_bitmap("figures/obstacle.png");
    robpos =  al_load_bitmap("figures/pos.png");
    speed =  al_load_bitmap("figures/speed.png");
    sp =  al_load_bitmap("figures/sp.png");
    map = al_load_bitmap("figures/map.png");

    //STUFF TO CHANGE, DATA FROM IMU AND SPEED
    char x[] = "8";
    char y[] = "9";
    char z[] = "10";

    char s[] = "233";

    float imux = 20;
    float imuy = 20;

    int interval = 250;
    auto time_interval = std::chrono::milliseconds(interval);
    auto time = std::chrono::steady_clock::now();

    while(1){
        time += time_interval;
        create_frame(x,y,z,s, imux, imuy, is, key);
        std::this_thread::sleep_until(time);
    }
}

void ui::create_frame(char xpos[], char ypos[], char zpos[], char speedn[], float a, float b, in_state is, char keypress){
    al_clear_to_color(al_map_rgb(0, 0, 0));

    //Main butons
    al_draw_bitmap(com, 100, 50, 0);
    al_draw_bitmap(obs, 100, 250, 0);
    al_draw_bitmap(speed, 600, 450, 0);
    al_draw_bitmap(sp, 600, 650, 0);
    al_draw_bitmap(robpos, 1035, 450, 0);

    //Map

    al_draw_bitmap(map, 1000, 10, 0);

    //Notifications

    al_draw_bitmap(okcom, 450, 45, 0);
    al_draw_bitmap(nocom, 450, 45, 0);
    al_draw_bitmap(yesobs, 450, 200, 0);

    //Arrows
    al_draw_bitmap(button, 800, 575, 0);
    al_draw_rotated_bitmap(button, 100, 100, 800, 725, M_PI, 0);

    al_draw_bitmap(button, 200, 400, 0);
    al_draw_rotated_bitmap(button, 100, 100, 200, 700, M_PI, 0);
    al_draw_rotated_bitmap(button, 100, 100, 350, 650, M_PI/2, 0);
    al_draw_rotated_bitmap(button, 100, 100, 150, 550, -M_PI/2, 0);

    //Motion boxes

    if(is.W) al_draw_bitmap(box, 175, 400,0);
    if(is.S) al_draw_bitmap(box, 175, 685,0);
    if(is.A) al_draw_rotated_bitmap(box, 100, 100,  65, 625, M_PI/2, 0);
    if(is.D) al_draw_rotated_bitmap(box, 100, 100, 350, 625, M_PI/2, 0);
    if(keypress == 'R') al_draw_bitmap(box, 775, 575,0); 
    if(keypress == 'F') al_draw_bitmap(box, 775, 710,0); 

    //al_draw_bitmap(box, 775, 575,0); 
    //al_draw_bitmap(box, 775, 710,0); 
    //al_draw_rotated_bitmap(box, 100, 100, 350, 625, 3.14/2, 0);
    //al_draw_rotated_bitmap(box, 100, 100, 65, 625, 3.14/2, 0);
    //al_draw_bitmap(box, 175, 400,0); 
    //al_draw_bitmap(box, 175, 685,0);

    //Text
    al_draw_text(font, al_map_rgb(255,255,255), 640, 675, 0, speedn);

            //FOR THE COMMANDS
    al_draw_text(font, al_map_rgb(255,255,255), 233, 430, 0, "W");
    al_draw_text(font, al_map_rgb(255,255,255), 243, 735, 0, "S");

    al_draw_text(font, al_map_rgb(255,255,255), 395, 580, 0, "D");
    al_draw_text(font, al_map_rgb(255,255,255), 85, 580, 0, "A");

    al_draw_text(font, al_map_rgb(255,255,255), 840, 610, 0, "R");
    al_draw_text(font, al_map_rgb(255,255,255), 843, 770, 0, "F");

            //FOR THE POSITION
    al_draw_text(fontb, al_map_rgb(255,255,255), 1070, 550, 0, "X = ");
    al_draw_text(fontb, al_map_rgb(255,255,255), 1070, 625, 0, "Y = ");
    al_draw_text(fontb, al_map_rgb(255,255,255), 1070, 700, 0, "Z = ");
    al_draw_text(fontb, al_map_rgb(255,255,255), 1150, 550, 0, xpos);
    al_draw_text(fontb, al_map_rgb(255,255,255), 1150, 625, 0, ypos);
    al_draw_text(fontb, al_map_rgb(255,255,255), 1150, 700, 0, zpos);

    al_draw_line(1003.3, 380, 1397, 380, al_map_rgb(0,255,0), 4);
    
    //Mapping
    
    al_draw_pixel(1200+a, 380-b, al_map_rgb(255,0,0));

    al_flip_display();
    
}


out_state ui::read_os(){
    std::lock_guard<std::mutex> lock(*read_mtx);
    return os;
}

void ui::write_is(in_state is_main){
    std::lock_guard<std::mutex> lock(*write_mtx);
    is = is_main;
}