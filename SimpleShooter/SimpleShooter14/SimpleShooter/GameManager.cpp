//2020 Levi D. Smith
#include "GameManager.h"

float GameManager::UNIT_SIZE = 64;
int GameManager::SCREEN_WIDTH = 1280;
int GameManager::SCREEN_HEIGHT = 720;
float GameManager::DELTA_TIME = 0.0167;

GameManager::GameManager() {


    LoadResources();

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);


    eventqueue = NULL;



    myfont = al_load_font("..\\Debug\\Arezzo-Cd-Regular.ttf", 32, 0);
    eventqueue = al_create_event_queue();
    al_register_event_source(eventqueue, al_get_keyboard_event_source());

    restart();

}

void GameManager::LoadResources() {
    string strPath;

    al_reserve_samples(2);

    soundShoot = al_load_sample("..\\shoot.wav");
    soundShipDead = al_load_sample("..\\player_dead.wav");
    soundEnemyDead = al_load_sample("..\\enemy_dead.wav");
    soundEnemyShoot = al_load_sample("..\\enemy_shoot.wav");


    ALLEGRO_SAMPLE *song = al_load_sample("..\\theme.wav");
    ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(song);
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
    al_play_sample_instance(songInstance);


}

void GameManager::restart() {
    keepLooping = true;
    isGameOver = false;

    ship = new Ship();
    ship->gamemanager = this;

    enemies.clear();
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            Enemy *enemy = new Enemy(64 + (j * 128), 64 + (i * 128));
            enemy->gamemanager = this;
            enemies.push_back(enemy);
        }
    }

    al_flush_event_queue(eventqueue);

}

void GameManager::Run() {
    while (keepLooping) {
        Update();
        Draw();
        al_rest(DELTA_TIME);

    }

}


void GameManager::Draw() {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_text(myfont, al_map_rgb(0, 255, 0), 32, 32, 0, "Step 14 - Sound effects and music");

    if (isGameOver) {
        al_draw_text(myfont, al_map_rgb(255, 128, 0), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, "GAME OVER");

    } else {

        //Draw all GameObjects
        ship->Draw();
        for (int i = 0; i < bullets.size(); ++i) {
            bullets[i]->Draw();
        }

        for (int i = 0; i < enemies.size(); ++i) {
            enemies[i]->Draw();
        }

    }


    al_flip_display();


}


void GameManager::Update() {
    int i, j;



    if (!isGameOver) {

        //Update all GameObjects
        ship->Update();
        for (i = 0; i < bullets.size(); ++i) {
            bullets[i]->Update();
        }

        for (i = 0; i < enemies.size(); ++i) {
            enemies[i]->Update();
        }


        handleInputGameRunning();

    } else {

        if (fGameOverDelay > 0) {
            fGameOverDelay -= DELTA_TIME;

            if (fGameOverDelay <= 0) {
                al_flush_event_queue(eventqueue);

                fGameOverDelay = 0;
            }
        }
        if (fGameOverDelay <= 0) {
            handleInputGameOver();
        }
    }


}

void GameManager::handleInputGameRunning() {
    bool hasEvent = al_get_next_event(eventqueue, &event);
    if (hasEvent && event.type == ALLEGRO_EVENT_KEY_DOWN) {
        int iKey = event.keyboard.keycode;

        switch (iKey) {
            case ALLEGRO_KEY_ESCAPE:
            case ALLEGRO_KEY_Q:
                keepLooping = false;
                break;

            case ALLEGRO_KEY_LEFT:
            case ALLEGRO_KEY_A:
                ship->vel_x = -ship->fSpeed;
                break;
            case ALLEGRO_KEY_RIGHT:
            case ALLEGRO_KEY_D:
                ship->vel_x = ship->fSpeed;
                break;
            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_W:
                ship->vel_y = -ship->fSpeed;
                break;
            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_S:
                ship->vel_y = ship->fSpeed;
                break;
            case ALLEGRO_KEY_SPACE:

                ship->shoot();
                break;
            default:
                break;

        }
    } else if (hasEvent && event.type == ALLEGRO_EVENT_KEY_UP) {
        int iKey = event.keyboard.keycode;
        switch (iKey) {
            case ALLEGRO_KEY_LEFT:
            case ALLEGRO_KEY_A:
                if (ship->vel_x < 0) {
                    ship->vel_x = 0;
                }
                break;
            case ALLEGRO_KEY_RIGHT:
            case ALLEGRO_KEY_D:
                if (ship->vel_x > 0) {
                    ship->vel_x = 0;
                }
                break;
            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_W:
                if (ship->vel_y < 0) {
                    ship->vel_y = 0;
                }
                break;
            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_S:
                if (ship->vel_y > 0) {
                    ship->vel_y = 0;
                }
                break;
            default:
                break;

        }
    }

    if (hasEvent && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        keepLooping = false;
    }


}

void GameManager::handleInputGameOver() {
    bool hasEvent = al_get_next_event(eventqueue, &event);
    if (hasEvent && event.type == ALLEGRO_EVENT_KEY_DOWN) {
        int iKey = event.keyboard.keycode;

        switch (iKey) {
            case ALLEGRO_KEY_ESCAPE:
            case ALLEGRO_KEY_Q:
                keepLooping = false;
                break;

            case ALLEGRO_KEY_SPACE:
                restart();

                break;
            default:
                break;

        }
    }

    if (hasEvent && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        keepLooping = false;
    }


}





void GameManager::checkGameOver() {
    int i;

    if (!isGameOver) {
        bool isEnemyAlive = false;

        for (i = 0; i < enemies.size(); i++) {
            if (enemies[i]->isAlive) {
                isEnemyAlive = true;
            }

        }

        if (!isEnemyAlive || !ship->isAlive) {
            isGameOver = true;
            fGameOverDelay = 2.0;
        }
    }


}