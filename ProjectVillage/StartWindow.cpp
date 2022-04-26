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
    SDL_Rect button[3];
    button[0].x = 400/2 - 384/2;
    button[0].y = 500;
    button[0].w = 384;
    button[0].h = 72;

    button[1].x = 0;
    button[1].y = 0;
    button[1].w = 384;
    button[1].h = 72;

    button[2].x = 0;
    button[2].y = 72;
    button[2].w = 384;
    button[2].h = 72;

    SDL_Renderer* renderer = SDL_CreateRenderer(currentWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    SDL_Surface* surface = IMG_Load("./Assets/button.png");

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = NULL;

    //Make a target texture to render too

    SDL_Texture* texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, button[0].w, button[0].h);

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
                SDL_RenderCopy(renderer, texture, &button[1], &button[0]);
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int x = e.button.x;
                    int y = e.button.y;
                    if (x > button[0].x && x < button[0].w + button[0].x &&
                        y > button[0].y && y < button[0].h + button[0].y ) {
                        cout << "button" << endl;
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, texture, &button[2], &button[0]);
                        SDL_RenderPresent(renderer);
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
        SDL_RenderCopy(renderer, texture, &button[1], &button[0]);
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


