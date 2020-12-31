//2020 Levi D. Smith
using namespace std;
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "GameManager.h"

int main() {
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();


    GameManager *gamemanager = new GameManager();
    gamemanager->Run();

    delete(gamemanager);


    return 0;
}