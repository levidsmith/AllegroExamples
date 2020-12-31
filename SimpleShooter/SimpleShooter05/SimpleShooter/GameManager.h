#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "GameObject.h"
#include "Ship.h"

class GameManager {
    public:
        GameManager();
        void Run();
        void Update();
        void Draw();
        ALLEGRO_DISPLAY *display;
        ALLEGRO_EVENT_QUEUE *eventqueue;
        ALLEGRO_EVENT event;
        ALLEGRO_FONT *myfont;

        static float UNIT_SIZE;
        static int SCREEN_WIDTH;
        static int SCREEN_HEIGHT;

    private:
        bool keepLooping;
        Ship *ship;

};

