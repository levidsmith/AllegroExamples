#include "GameObject.h"

GameObject::GameObject(float init_x, float init_y, float init_w, float init_h) {
    x = init_x;
    y = init_y;
    w = init_w;
    h = init_h;

}

void GameObject::Update() {

}


void GameObject::Draw() {
//    al_draw_rectangle(x, y, x + w, y + h, al_map_rgb(0, 255, 255), 2);
      al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgb(0, 255, 255));
    
        

}