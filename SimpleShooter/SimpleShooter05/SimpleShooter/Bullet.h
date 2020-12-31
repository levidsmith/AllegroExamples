#pragma once
#include "GameObject.h"
class Bullet : public GameObject {

    public:
        float vel_y;
        float fSpeed;
        bool isAlive;
        float fLifetime;
        Bullet(float init_x, float init_y);

        void Draw();
        void Update();


};

