#include "GameObject.h"

GameObject::GameObject(float init_x, float init_y, float init_w, float init_h) {
    x = init_x;
    y = init_y;
    w = init_w;
    h = init_h;

}

bool GameObject::checkCollision(GameObject *gobj) {
    bool hasCollided = true;
    if (x + w < gobj->x || x > gobj->x + gobj->w ||
        y + h < gobj->y || y > gobj->y + gobj->h) {
        hasCollided = false;
    }

    return hasCollided;

}
