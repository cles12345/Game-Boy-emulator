#include <SDL.h>

constexpr int GB_WIDTH = 160;
constexpr int GB_HEIGHT = 144;

constexpr int SCREEN_SCALE = 4;
constexpr int WIN_WIDH = GB_WIDTH * SCREEN_SCALE;
constexpr int WIN_HEIGHT = GB_HEIGHT * SCREEN_SCALE;

void cleanup(SDL_Window* window, SDL_Renderer* renderer);

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
        cleanup(window, nullptr);
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", nullptr);
        cleanup(window, renderer);
        return 1;
    }

    SDL_Texture* frame_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        GB_WIDTH,
        GB_HEIGHT
    );

    uint32_t framebuffer[GB_WIDTH * GB_HEIGHT];
    
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

        for (int y = 0; y < GB_HEIGHT; y++) {
            for (int x = 0; x < GB_WIDTH; x++) {
                uint32_t color = 0xFF000000 | (0xFF << 16) | (0xFF << 8) | 0xFF;
                framebuffer[y * GB_WIDTH + x] = color;
            }
        }

        SDL_UpdateTexture(
            frame_texture,
            NULL,
            framebuffer,
            GB_WIDTH * sizeof(uint32_t)
        );

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, frame_texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    cleanup(window, renderer);
    return 0;
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}