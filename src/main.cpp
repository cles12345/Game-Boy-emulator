#include <SDL.h>

constexpr int GB_WIDTH = 160;
constexpr int GB_HEIGHT = 144;

constexpr int SCREEN_MAG = 4;
constexpr int WIN_WIDH = GB_WIDTH * SCREEN_MAG;
constexpr int WIN_HEIGHT = GB_HEIGHT * SCREEN_MAG;

void cleanup(SDL_Window* window);

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("GameBoy", WIN_WIDH, WIN_HEIGHT, 0);
    if (!window)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
        cleanup(window);
        return 1;
    }

    bool running = true;
    while (running)
    {
        SDL_Event event{0};
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            default:
                break;
            }
        }   
    }

    cleanup(window);
    return 0;
}

void cleanup(SDL_Window* window)
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}