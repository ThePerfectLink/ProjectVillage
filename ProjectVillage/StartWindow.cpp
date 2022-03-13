#include "StartWindow.h"
#include <iostream>
#include <SDL_mouse.h>
#include <SDL_events.h>
#include <SDL.h>

using namespace std;



StartWindow::StartWindow() {
	int exit = 0;
    int start = 0;
    SDL_Window * currentWindow = NULL;
	SDL_Event e;
	currentWindow = startIntroMenu();
    while (!exit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT)
                    cout << "left" << endl;
                else
                    cout << "right" << endl;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                    exit = 1;
                    start = 1;
                    cout << "boof" << endl;
                }
            }
        }
    }
    SDL_DestroyWindow(currentWindow);
    if (start) {
        currentWindow = startGameWindow();
    }
    while (start) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT)
                    cout << "left" << endl;
                else
                    cout << "right" << endl;
                break;
            case SDL_KEYDOWN:
                start = 0;
            }
        }
    }
    SDL_DestroyWindow(currentWindow);
}
