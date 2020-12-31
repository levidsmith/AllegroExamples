#include "Ship.h"
#include "GameManager.h"
#include "GameObject.h"

Ship::Ship() : GameObject((1280-32) / 2, 600, 32, 64) {
    fSpeed = 5 * GameManager::TILE_SIZE;
    vel_x = 0;
    vel_y = 0;

}


void Ship::Update() {
    x += vel_x * 0.0167;
    y += vel_y * 0.0167;

}

void Ship::Draw() {
    al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgb(0, 255, 255));

}
