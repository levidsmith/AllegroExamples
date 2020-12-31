#pragma once
#include "GameObject.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "GameManager.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Ship.h"


class Enemy : public GameObject {

    public:
        float vel_x;
        float fSpeed;
        float fLifetime;
        bool isAlive;
        Enemy(float init_x, float init_y);

        void Draw();
        void Update();
        class GameManager *gamemanager;
        void damageReceived();

private:



};

