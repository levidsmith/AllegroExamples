//2020 Levi D. Smith
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>


ALLEGRO_FONT *myfont;

void draw_primitives() {

    ALLEGRO_COLOR c_black = al_map_rgb_f(0, 0, 0);
    ALLEGRO_COLOR c_white = al_map_rgb_f(1, 1, 1);

    int iSpacing = 256;

    al_clear_to_color(c_black);

    int x, y;
    int x_offset, y_offset;
    int iCellsPerRow = 5;
    
    x_offset = 64;
    y_offset = 64;

    int iCell = 0;

    while (iCell < 20) {
        ALLEGRO_COLOR c = al_color_hsv(360.0 * ((float) iCell) / 20.0, 1.0, 1.0);
        x = (iCell % iCellsPerRow) * iSpacing + x_offset;
        y = (iCell / iCellsPerRow) * iSpacing + y_offset;

        switch (iCell) {
            case 0:
                al_draw_filled_rectangle(x, y, x + 50, y + 80, c);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_filled_rectangle");
                break;
            case 1:
                al_draw_rectangle(x, y, x + 50, y + 80, c, 1);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_rectangle");
                break;
            case 2:
                al_draw_rectangle(x, y, x + 50, y + 80, c, 8);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_rectangle (increased thickness)");
                break;
            case 3:
                al_draw_line(x, y, x + 50, y + 80, c, 1);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_line");
                break;
            case 4:
                al_draw_line(x, y, x + 50, y + 80, c, 8);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_line (increased thickness)");
                break;
            case 5:
                al_draw_triangle(x, y, x + 50, y, x + 25, y + 80, c, 1);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_triangle");
                break;
            case 6:
                al_draw_triangle(x, y, x + 50, y, x + 25, y + 80, c, 8);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_triangle (increased thickness)");
                break;
            case 7:
                al_draw_filled_triangle(x, y, x + 50, y, x + 25, y + 80, c);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_filled_triangle");
                break;
            case 8:
                al_draw_rounded_rectangle(x, y, x + 50, y + 80, 4, 4, c, 1);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_rounded_rectangle");
                break;
            case 9:
                al_draw_rounded_rectangle(x, y, x + 50, y + 80, 16, 16, c, 1);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_rounded_rectangle (increased radii)");
                break;
            case 10:
                al_draw_circle(x + 25, y + 25, 50, c, 1);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_circle");
                break;
            case 11:
                al_draw_circle(x + 25, y + 25, 50, c, 8);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_circle (increased thickness)");
                break;
            case 12:
                al_draw_ellipse(x + 15, y + 30, 30, 60, c, 1);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_ellipse");
                break;
            case 13:
                al_draw_ellipse(x + 15, y + 30, 30, 60, c, 8);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_ellipse (increased thickness)");
                break;
            case 14:
                al_draw_arc(x + 25, y + 25, 50, 0, 3.14 / 2.0, c, 1);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_arc");
                break;
            case 15:
                al_draw_arc(x + 25, y + 25, 50, 0, 3.14 / 2.0, c, 8);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_arc (increased thickness)");
                break;
            case 16:
                float points[8];
                points[0] = x + 0;
                points[1] = y + 0;
                points[2] = x + 50;
                points[3] = y + -50;
                points[4] = x + 100;
                points[5] = y + 150;
                points[6] = x + 150;
                points[7] = y + 80;

                al_draw_spline(points, c, 1);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_spline");

                break;
            case 17:
                points[0] = x + 0;
                points[1] = y + 0;
                points[2] = x + 50;
                points[3] = y + -50;
                points[4] = x + 100;
                points[5] = y + 150;
                points[6] = x + 150;
                points[7] = y + 80;

                al_draw_spline(points, c, 8);
                al_draw_text(myfont, c_white, x, y + 100, 0, "al_draw_spline (increased thickness)");

                break;

        }


        iCell++;
    }

}


int main() {
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY *display;
    ALLEGRO_KEYBOARD_STATE kb_state;
    
    al_init();
    al_install_keyboard();

    myfont = al_load_font("..\\Arezzo-Cd-Regular.ttf", 16, 0);

    display = al_create_display(1408, 1080);


    bool keepLooping = true;
    while (keepLooping) {
        al_get_keyboard_state(&kb_state);

        if (al_key_down(&kb_state, ALLEGRO_KEY_ESCAPE) || al_key_down(&kb_state, ALLEGRO_KEY_SPACE)) {
            keepLooping = false;
        }

        draw_primitives();

        al_flip_display();

        al_rest(0.0167);

    }


    std::cout << "Hello World!\n";

    return 0;
}

