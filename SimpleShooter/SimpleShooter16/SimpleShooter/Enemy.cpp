//2020 Levi D. Smith
#include "Enemy.h"


Enemy::Enemy(float init_x, float init_y) : GameObject(init_x, init_y, 64, 64) {
    x = init_x;
    y = init_y;
    fSpeed = 2 * GameManager::UNIT_SIZE;
    vel_x = fSpeed;
    fLifetime = 0;
    isAlive = true;

    random_device rd;
    uniform_int_distribution<int> dist(5, 20);
    fShootDelay = dist(rd);
}

void Enemy::Update() {
    if (isAlive) {
        x += vel_x * GameManager::DELTA_TIME;
        fLifetime += GameManager::DELTA_TIME;

        if (fLifetime > 2) {
            vel_x *= -1;
            fLifetime -= 2;

            y += 32;
            if (y > GameManager::SCREEN_HEIGHT) {
                y -= (GameManager::SCREEN_HEIGHT + h);
            }
        }

        if (fShootDelay > 0) {
            fShootDelay -= GameManager::DELTA_TIME;
            if (fShootDelay <= 0) {
                shoot();
            }
        }

        if (checkCollision(gamemanager->ship)) {
            gamemanager->ship->damagedRecieved();
        }
    }

}

void Enemy::Draw() {
    if (isAlive) {
        //al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgb(0, 255, 0));

        ALLEGRO_BITMAP *img;

        if (((int) (fLifetime * 2)) % 2 == 0) {
            img = gamemanager->sprEnemy_01;
        } else {
            img = gamemanager->sprEnemy_02;

        }

        al_draw_bitmap(img, x, y, 0);

    }


}

void Enemy::damageReceived() {
    isAlive = false;
    gamemanager->checkGameOver();
    al_play_sample(gamemanager->soundEnemyDead, 1, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);


}

void Enemy::shoot() {
    if (isAlive) {
        Bullet *bullet = new Bullet(x, y);
        bullet->isFriendly = false;
        bullet->vel_y = bullet->fSpeed;
        bullet->gamemanager = gamemanager;

        gamemanager->bullets.push_back(bullet);

        random_device rd;
        uniform_int_distribution<int> dist(5, 20);
        fShootDelay = dist(rd);
        al_play_sample(gamemanager->soundEnemyShoot, 1, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);


    }
}