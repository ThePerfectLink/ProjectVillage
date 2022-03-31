#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
class StartWindow {
    private:
        SDL_Window* startIntroMenu() {
            SDL_Window* introMenu = SDL_CreateWindow(
                "Startup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 600, SDL_WINDOW_VULKAN
            );
            return introMenu;
        }
        SDL_Window* startGameWindow() {
            SDL_Window* gameWindow = SDL_CreateWindow(
                "ProjectVillage", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 1080, SDL_WINDOW_VULKAN
            );
            return gameWindow;
        }
    public:
        StartWindow::StartWindow();
};
struct Button {
        void (*callback)(void* data);
        void* user_data;
};