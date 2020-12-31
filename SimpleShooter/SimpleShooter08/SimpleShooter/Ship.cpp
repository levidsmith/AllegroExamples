#include "Ship.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Bullet.h"

Ship::Ship() : GameObject((1280-32) / 2, 600, 32, 64) {
    fSpeed = 5 * GameManager::UNIT_SIZE;
    vel_x = 0;
    vel_y = 0;

}


void Ship::Update() {
    //Move the ship
    x += vel_x * GameManager::DELTA_TIME;
    y += vel_y * GameManager::DELTA_TIME;

    //Bounds Checking
    if (x + w > GameManager::SCREEN_WIDTH) {
        x = GameManager::SCREEN_WIDTH - w;
    }

    if (x < 0) {
        x = 0;
    }

    if (y + h > GameManager::SCREEN_HEIGHT) {
        y = GameManager::SCREEN_HEIGHT - h;
    }

    if (y < 0) {
        y = 0;
    }

}

void Ship::Draw() {
    al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgb(0, 255, 255));

}

void Ship::shoot() {
    Bullet *bullet = new Bullet(x, y);
    gamemanager->bullets.push_back(bullet);
    
}