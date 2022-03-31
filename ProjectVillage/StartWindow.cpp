#include "StartWindow.h"
#include <iostream>
#include <SDL_mouse.h>
#include <SDL_events.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

StartWindow::StartWindow() {
	int exit = 0;
    int start = 0;
    SDL_Window * currentWindow = NULL;
	SDL_Event e;
	currentWindow = startIntroMenu();
    SDL_Rect button;
    button.x = 400/2 - 384/2;
    button.y = 500;
    button.w = 384;
    button.h = 72;
    SDL_Rect buttonE;
    buttonE.x = 400 / 2 + 384 / 2;
    buttonE.y = 572;
    buttonE.w = 384;
    buttonE.h = 72;

    SDL_Renderer* renderer = SDL_CreateRenderer(currentWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    //Now render to the texture
    SDL_Surface* surface = IMG_Load("./Assets/button.png");

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = NULL;

    //Make a target texture to render too
    SDL_Texture* texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, button.w, button.h);

    //Now render to the texture
    SDL_SetRenderTarget(renderer, texTarget);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    //Detach the texture
    SDL_SetRenderTarget(renderer, NULL);

    while (!exit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int x = e.button.x;
                    int y = e.button.y;
                    if (x > button.x && x < button.w + button.x &&
                        y > button.y && y < button.h + button.y ) {
                        cout << "button" << endl;
                    }
                }
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
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &button);
        SDL_RenderPresent(renderer);
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


