//2020 Levi D. Smith
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

class GameObject {
    public:
        float x;
        float y;

        float w;
        float h;

        virtual void Update() = 0;
        virtual void Draw() = 0;

        GameObject(float init_x, float init_y, float init_w, float init_h);
        bool checkCollision(GameObject *gobj);
        
};

