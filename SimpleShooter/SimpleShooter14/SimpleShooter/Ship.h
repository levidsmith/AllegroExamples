//2020 Levi D. Smith
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>

#include "GameManager.h"
#include "GameObject.h"
#include "Bullet.h"

class Ship : public GameObject {
    public:
        float vel_x;
        float vel_y;
        float fSpeed;
        bool isAlive;
        float fShootCooldown;
        
        
        Ship();

        void Draw();
        void Update();
        void shoot();
        class GameManager *gamemanager;
        void damagedRecieved();

    private:



};

