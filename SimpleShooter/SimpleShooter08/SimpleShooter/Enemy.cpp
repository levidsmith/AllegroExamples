#include "Enemy.h"


Enemy::Enemy(float init_x, float init_y) : GameObject(init_x, init_y, 64, 64) {
    x = init_x;
    y = init_y;
    fSpeed = 2 * GameManager::UNIT_SIZE;
    vel_x = fSpeed;
    fLifetime = 0;
    isAlive = true;
}

void Enemy::Update() {
    x += vel_x * GameManager::DELTA_TIME;
    fLifetime += GameManager::DELTA_TIME;

    if (fLifetime > 2) {
        vel_x *= -1;
        fLifetime -= 2;
    }

}

void Enemy::Draw() {
    if (isAlive) {
        al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgb(0, 255, 0));
    }


}

void Enemy::damageReceived() {
    isAlive = false;

}