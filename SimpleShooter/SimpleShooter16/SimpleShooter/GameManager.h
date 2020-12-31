//2020 Levi D. Smith
#pragma once
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <string>

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
        ALLEGRO_JOYSTICK *joystick;

        static float UNIT_SIZE;
        static int SCREEN_WIDTH;
        static int SCREEN_HEIGHT;
        static float DELTA_TIME;

        vector<Bullet *> bullets;
        class Ship *ship;
        vector<class Enemy *> enemies;

        bool isGameOver;
        float fGameOverDelay;

        void checkGameOver();

        ALLEGRO_SAMPLE *soundShoot;
        ALLEGRO_SAMPLE *soundEnemyDead;
        ALLEGRO_SAMPLE *soundShipDead;
        ALLEGRO_SAMPLE *soundEnemyShoot;

        int iDebugButtonPressed;
        string strDebugStick;
        bool useJoystickEvent;
        bool useJoystickPolling;
        ALLEGRO_JOYSTICK_STATE joystick_state;

        ALLEGRO_BITMAP *sprShip;
        ALLEGRO_BITMAP *sprEnemy_01;
        ALLEGRO_BITMAP *sprEnemy_02;
        ALLEGRO_BITMAP *sprBullet;


    private:
        bool keepLooping;
        void restart();
        void handleInputGameRunning();
        void handleInputGameOver();
        void LoadResources();

        void oldSchoolTransparency(ALLEGRO_BITMAP *img);

};

