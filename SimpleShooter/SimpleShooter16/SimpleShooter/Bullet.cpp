//2020 Levi D. Smith
#include "Bullet.h"
#include "Ship.h"
#include "GameManager.h"

Bullet::Bullet(float init_x, float init_y) : GameObject(init_x, init_y, 16, 16) {
    x = init_x;
    y = init_y;
    fSpeed = 5 * GameManager::UNIT_SIZE;
    fLifetime = 0;
    vel_y = -fSpeed;
    isAlive = true;

}

void Bullet::Update() {
    if (isAlive) {
        y += vel_y * GameManager::DELTA_TIME;

        int i;
        if (isFriendly) {

            for (i = 0; i < gamemanager->enemies.size(); ++i) {
                if (gamemanager->enemies[i]->isAlive && checkCollision(gamemanager->enemies[i])) {
                    gamemanager->enemies[i]->damageReceived();
                    destroy();
                }
            }
        } else {
            if (gamemanager->ship->isAlive && checkCollision(gamemanager->ship)) {
                gamemanager->ship->damagedRecieved();
                destroy();

            }
        }


    }
    

}

void Bullet::Draw() {
    if (isAlive) {
        ALLEGRO_COLOR c;
        if (isFriendly) {
            c = al_map_rgb(0, 255, 255);
        } else {
            c = al_map_rgb(255, 0, 0);
        }

        //al_draw_filled_rectangle(x, y, x + w, y + h, c);
        al_draw_tinted_bitmap(gamemanager->sprBullet, c, x, y, 0);
    }

}

void Bullet::destroy() {
    isAlive = false;
}