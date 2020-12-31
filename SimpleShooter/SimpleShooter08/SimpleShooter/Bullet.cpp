#include "Bullet.h"
#include "Ship.h"
#include "GameManager.h"

Bullet::Bullet(float init_x, float init_y) : GameObject(init_x, init_y, 16, 16) {
    x = init_x;
    y = init_y;
    fSpeed = 5 * GameManager::UNIT_SIZE;
    fLifetime = 0;
    vel_y = -fSpeed;

}

void Bullet::Update() {
    y += vel_y * GameManager::DELTA_TIME;
    

}

void Bullet::Draw() {
    al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgb(255, 255, 255));

}