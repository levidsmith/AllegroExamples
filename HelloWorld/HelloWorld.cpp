//2020 Levi D. Smith
using namespace std;
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

int main() {
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();

    char *strDir = al_get_current_directory();
    cout << strDir << endl;

    ALLEGRO_DISPLAY *display = al_create_display(800, 600);
    ALLEGRO_FONT *myfont = al_load_font("..\\Debug\\Arezzo-Cd-Regular.ttf", 128, 0);
    al_clear_to_color(al_map_rgb(255, 255, 0));
    al_draw_text(myfont, al_map_rgb(0, 0, 0), 0, 0, 0, "Hello Allegro");

    al_flip_display();
    al_rest(5);  //keep the window from immediately closing

    //std::cout << "Hello World!\n";
}