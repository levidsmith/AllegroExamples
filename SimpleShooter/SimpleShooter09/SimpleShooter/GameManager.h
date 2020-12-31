//2020 Levi D. Smith
#pragma once
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <vector>

#include "GameObject.h"
#include "Ship.h"
#include "Bullet.h"
#include "Enemy.h"

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
        static float DELTA_TIME;

        vector<Bullet *> bullets;
        class Ship *ship;
        vector<class Enemy *> enemies;


    private:
        bool keepLooping;

};

