#include "GameManager.h"

float GameManager::TILE_SIZE = 64;
int GameManager::SCREEN_WIDTH = 1280;
int GameManager::SCREEN_HEIGHT = 720;

GameManager::GameManager() {

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    eventqueue = NULL;
    

    myfont = al_load_font("..\\Debug\\Arezzo-Cd-Regular.ttf", 32, 0);
    eventqueue = al_create_event_queue();
    al_register_event_source(eventqueue, al_get_keyboard_event_source());

    keepLooping = true;
    ship = new Ship();


}

void GameManager::Run() {
    while (keepLooping) {
        Update();
        Draw();
        al_rest(0.016);

    }

}


void GameManager::Draw() {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_text(myfont, al_map_rgb(0, 255, 0), 32, 32, 0, "Step 4 - Stop on arrow key release");

    ship->Draw();

    al_flip_display();


}


void GameManager::Update() {

    ship->Update();
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
