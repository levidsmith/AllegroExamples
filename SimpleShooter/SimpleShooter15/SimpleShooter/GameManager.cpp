//2020 Levi D. Smith
#include "GameManager.h"

float GameManager::UNIT_SIZE = 64;
int GameManager::SCREEN_WIDTH = 1280;
int GameManager::SCREEN_HEIGHT = 720;
float GameManager::DELTA_TIME = 0.0167;

GameManager::GameManager() {

    useJoystickEvent = false;
    useJoystickPolling = true;

    LoadResources();

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);


    eventqueue = NULL;



    myfont = al_load_font("..\\Debug\\Arezzo-Cd-Regular.ttf", 32, 0);
    eventqueue = al_create_event_queue();
    al_register_event_source(eventqueue, al_get_keyboard_event_source());
    al_register_event_source(eventqueue, al_get_joystick_event_source());

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


    al_draw_text(myfont, al_map_rgb(0, 255, 0), 32, 32, 0, "Step 15 - Gamepad / joystick controls");
    if (strDebugStick != "") {
        al_draw_text(myfont, al_map_rgb(255, 255, 0), 32, 64, 0, ("Debug stick: " + strDebugStick).c_str());
    }
    al_draw_text(myfont, al_map_rgb(255, 255, 0), 32, 96, 0, ("Debug button pressed: " + to_string(iDebugButtonPressed)).c_str());


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
    bool hasEvent;
    bool firstTime = true;

    if (useJoystickPolling) {
        al_get_joystick_state(al_get_joystick(0), &joystick_state);
        float fTolerance = 0.2;

        if (joystick_state.stick[0].axis[0] > fTolerance) {
            ship->moveRight();
        } else if (joystick_state.stick[0].axis[0] < -fTolerance) {
            ship->moveLeft();
        } else {
            ship->stopHorizontal();
        }

        if (joystick_state.stick[0].axis[1] > fTolerance) {
            ship->moveDown();
        } else if (joystick_state.stick[0].axis[1] < -fTolerance) {
            ship->moveUp();
        } else {
            ship->stopVertical();
        }


        if (joystick_state.button[0]) {
            iDebugButtonPressed = 0;
            ship->shoot();

        }

        int i;
        for (i = 0; i < al_get_joystick_num_buttons(al_get_joystick(0)); i++) {
            if (joystick_state.button[i] > 0) {
                iDebugButtonPressed = i;

            }

        }

    }

    
    
    while (hasEvent = al_get_next_event(eventqueue, &event)) {


        if (useJoystickEvent) {
            //Handle joystick
            if (firstTime) {
                strDebugStick = "";
                firstTime = false;
            }

            if (hasEvent && event.type == ALLEGRO_EVENT_JOYSTICK_AXIS && event.joystick.id == al_get_joystick(0)) {
                float fTolerance = 0.2;
                strDebugStick.append("stick: " + to_string(event.joystick.stick) + " axis: " + to_string(event.joystick.axis) + " pos: " + to_string(event.joystick.pos) + " ");

                //left stick or d-pad
                if (event.joystick.stick == 0) {
                    if (event.joystick.axis == 0 && event.joystick.pos > fTolerance) {
                        ship->moveRight();
                    } else if (event.joystick.axis == 0 && event.joystick.pos < -fTolerance) {
                        ship->moveLeft();
                    } else {
                        ship->stopHorizontal();
                    }

                    if (event.joystick.axis == 1 && event.joystick.pos > fTolerance) {
                        ship->moveDown();
                    } else if (event.joystick.axis == 1 && event.joystick.pos < -fTolerance) {
                        ship->moveUp();
                    } else {
                        ship->stopVertical();
                    }


                }
            }

            if (hasEvent && event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN && event.joystick.id == al_get_joystick(0)) {
                iDebugButtonPressed = event.joystick.button;


                if (event.joystick.button == 0) {
                    ship->shoot();
                }

            }
        }



        //Handle keyboard
        if (hasEvent && event.type == ALLEGRO_EVENT_KEY_DOWN) {
            int iKey = event.keyboard.keycode;

            switch (iKey) {
                case ALLEGRO_KEY_ESCAPE:
                case ALLEGRO_KEY_Q:
                    keepLooping = false;
                    break;

                case ALLEGRO_KEY_LEFT:
                case ALLEGRO_KEY_A:
                    ship->moveLeft();

                    break;
                case ALLEGRO_KEY_RIGHT:
                case ALLEGRO_KEY_D:
                    ship->moveRight();
                    break;
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_W:
                    ship->moveUp();
                    break;
                case ALLEGRO_KEY_DOWN:
                case ALLEGRO_KEY_S:
                    ship->moveDown();
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
                        ship->stopHorizontal();
                    }
                    break;
                case ALLEGRO_KEY_RIGHT:
                case ALLEGRO_KEY_D:
                    if (ship->vel_x > 0) {
                        ship->stopHorizontal();
                    }
                    break;
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_W:
                    if (ship->vel_y < 0) {
                        ship->stopVertical();
                    }
                    break;
                case ALLEGRO_KEY_DOWN:
                case ALLEGRO_KEY_S:
                    if (ship->vel_y > 0) {
                        ship->stopVertical();
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