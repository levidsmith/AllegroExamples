//2020 Levi D. Smith
using namespace std;
#include <iostream>
#include <string>
#include <random>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

int main() {
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();

    ALLEGRO_DISPLAY *display = al_create_display(800, 600);
    ALLEGRO_KEYBOARD_STATE kb_state;
    ALLEGRO_EVENT_QUEUE *eventqueue = NULL;
    ALLEGRO_EVENT event;

    ALLEGRO_FONT *myfont = al_load_font("..\\Debug\\Arezzo-Cd-Regular.ttf", 80, 0);
    eventqueue = al_create_event_queue();
    al_register_event_source(eventqueue, al_get_keyboard_event_source());

    random_device rd;
    uniform_int_distribution<int> dist(1, 100);

    int iSecretNumber = dist(rd);
    int iNumGuess = -1;
    int iGuessCount = 0;

    string strInput = "";
    string strResult = "";

    while (true) {
        string strMessage = "Guess the number 1 to 100";

        al_get_keyboard_state(&kb_state);
        if (al_key_down(&kb_state, ALLEGRO_KEY_ESCAPE)) {
            break;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(myfont, al_map_rgb(255, 255, 0), 0, 0, 0, strMessage.c_str());
        al_draw_text(myfont, al_map_rgb(0, 255, 255), 0, 128, 0, strInput.c_str());
        al_draw_text(myfont, al_map_rgb(0, 255, 0), 0, 256, 0, strResult.c_str());
        al_flip_display();

        al_wait_for_event(eventqueue, &event);
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            int iKey = event.keyboard.keycode;
            if (iKey >= ALLEGRO_KEY_0 && iKey <= ALLEGRO_KEY_9) {
                if (strInput.size() < 3) {
                    strInput.append(to_string(iKey - ALLEGRO_KEY_0));
                }
            }

            if (iKey == ALLEGRO_KEY_BACKSPACE) {
                if (strInput.size() > 0) {
                    strInput = strInput.substr(0, strInput.size() - 1);

                }
            }

            if (iKey == ALLEGRO_KEY_ENTER) {
                try {
                    iNumGuess = stoi(strInput);
                } catch (invalid_argument &ia) {
                    cout << "invalid number" << endl;
                    continue; //skips over the rest of the loop
                }
                strResult = to_string(iNumGuess) + ": ";

                iGuessCount++;

                if (iNumGuess < iSecretNumber) {
                    strResult.append("Higher");
                } else if (iNumGuess > iSecretNumber) {
                    strResult.append("Lower");
                } else if (iNumGuess == iSecretNumber) {
                    strResult.append("Correct!  " + to_string(iGuessCount) + " total guesses");
                }

                strInput = "";
            }
        }
    }
}
