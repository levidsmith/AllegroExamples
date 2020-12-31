//2020 Levi D. Smith
#include "Ship.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Bullet.h"

Ship::Ship() : GameObject((1280-32) / 2, 600, 32, 64) {
    fSpeed = 5 * GameManager::UNIT_SIZE;
    vel_x = 0;
    vel_y = 0;
    isAlive = true;
    fShootCooldown = 0;

}


void Ship::Update() {
    if (isAlive) {
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

        if (fShootCooldown > 0) {
            fShootCooldown -= GameManager::DELTA_TIME;
            if (fShootCooldown < 0) {
                fShootCooldown = 0;
            }
        }
    }

}

void Ship::Draw() {
    if (isAlive) {
//        al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgb(0, 255, 255));
        if (gamemanager->sprShip != NULL) {
            al_draw_bitmap(gamemanager->sprShip, x, y, 0);
           // al_set_blender(ALLEGRO_DEST_MINUS_SRC, ALLEGRO_ONE, ALLEGRO_ZERO);
            //al_draw_tinted_bitmap(gamemanager->sprShip, al_map_rgba_f(1, 0, 1, 1), x, y, 0);
        }
    }

}

void Ship::shoot() {
    if (isAlive && (fShootCooldown <= 0)) {
        Bullet *bullet = new Bullet(x, y);
        bullet->gamemanager = gamemanager;
        bullet->isFriendly = true;


        gamemanager->bullets.push_back(bullet);
        fShootCooldown = 0.5;
        al_play_sample(gamemanager->soundShoot, 1, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
    
}

void Ship::damagedRecieved() {
    isAlive = false;
    gamemanager->checkGameOver();
    al_play_sample(gamemanager->soundShipDead, 1, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

}

void Ship::moveLeft() {
    vel_x = -fSpeed;

}

void Ship::moveRight() {
    vel_x = fSpeed;

}

void Ship::moveDown() {
    vel_y = fSpeed;
}

void Ship::moveUp() {
    vel_y = -fSpeed;

}

void Ship::stopHorizontal() {
    vel_x = 0;
}

void Ship::stopVertical() {
    vel_y = 0;
}