
#include "pch.h"
#include "Scene.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* fontNormal = nullptr;
Scene* scene = nullptr;

// initial
int init(const char* title, int width, int height, bool fullscreen);
void shutdown();            // shutdown
bool poll_events();         // Process messages

// main
int main(int argc, char* argv[])
{
    init("Snake", 800, 600, false);

    scene = new Scene(renderer);

    int t = SDL_GetTicks();
    int d;
    float delay;

    // main loop
    while (poll_events()) {
        d = SDL_GetTicks() - t;
        delay = d * 0.001f;
        t = SDL_GetTicks();

        // Clear
        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //SDL_RenderClear(renderer);

        scene->update(delay);
        scene->draw();

        // update screen
        SDL_RenderPresent(renderer);

        // Frame rate
        if (d < 16) {
            SDL_Delay(16 - d);
        }
    }

    shutdown();

    return 0;
}

// initialization
int init(const char* title, int width, int height, bool fullscreen)
{
    printf("SDL> initialize...\n");

    // initialization SDL
    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
        printf("SDL> initialize failed!\n");
        printf("SDL> %s\n", SDL_GetError());
        return -1;
    }

    // Create window
    int flag = 0;

    // Determine whether to use full screen mode
    if (fullscreen) {
        flag = SDL_WINDOW_FULLSCREEN;
    }

    // Create window
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        flag);
    if (window == nullptr) {
        printf("SDL> window create failed!\n");
        printf("SDL> %s\n", SDL_GetError());
        return -1;
    }
    else {
        printf("SDL> window create success.\n");
    }

    // Initialize renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        printf("SDL> renderer create failed!\n");
        printf("SDL> %s\n", SDL_GetError());
    }
    else {
        // Set rendering effects
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

        // Initialize render color
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        printf("SDL> renderer create success.\n");
    }

    // Initialize audio processing library
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL> SDL_mixer: initialize failed!\n");
        printf("SDL> SDL_mixer: %s\n", Mix_GetError());
    }
    else {
        Mix_Init(MIX_INIT_MP3);
    }

    // Initialize font engine
    if (TTF_Init() < 0) {
        printf("SDL> SDL_ttf: initialize failed!\n");
        printf("SDL> SDL_ttf: %s\n", TTF_GetError());
    }
    else {
        fontNormal =TTF_OpenFont("../comicbd.ttf", 24.0f);
        if (fontNormal == nullptr) {
            printf("SDL> SDL_ttf: %s\n", TTF_GetError());
        }
    }

    // Initialize image loader
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0) {
        printf("SDL> SDL_image: initialize failed!\n");
        printf("SDL> SDL_image: %s\n", IMG_GetError());
    }

    printf("SDL> initialize success.\n");

    return 0;
}

// shutdown
void shutdown()
{
    if (scene) {
        delete scene;
        scene = nullptr;
    }

    if (fontNormal) {
        TTF_CloseFont(fontNormal);
        fontNormal = nullptr;
    }

    // Release SDL object
    TTF_Quit();
    IMG_Quit();
    Mix_CloseAudio();

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

// Process messages
bool poll_events()
{
    // Handling SDL events
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: // SDLQUIT
            printf("SDL> quit.\n");
            //running = false;
            // this->dispose();
            return false;
        case SDL_KEYDOWN:
            // printf("keydown : %d %c\n", event.key.repeat, (char)event.key.keysym.sym);
            if (event.key.repeat) {
            }
            else {
                scene->keyDown(event.key.keysym.sym);
            }
            break;
        case SDL_KEYUP:
            break;

        case SDL_MOUSEMOTION:
            // printf("mouse move : %d %d\n", event.button.x, event.button.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
            case SDL_BUTTON_LEFT:
                // printf("mouse left down : %d %d\n", event.button.x, event.button.y);
                scene->click(event.button.x, event.button.y);
                break;
            case SDL_BUTTON_MIDDLE:
                break;
            case SDL_BUTTON_RIGHT:
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        default:
            break;
        }
    }

    return true;
}

// Load texture
SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr) {
        printf("SDL> load image %s failed!\n", filename.c_str());
        printf("SDL> SDL_image: %s\n", IMG_GetError());
        return nullptr;
    }
    else {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) {
            printf("SDL> create texture from surface failed!\n");
            printf("SDL> SDL_image: %s\n", IMG_GetError());
            return nullptr;
        }
        else {
            // Setup texture blend mode
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        }
        SDL_FreeSurface(surface);
        return texture;
    }
}

// delete texture
void freeTexture(SDL_Texture* &ptr)
{
    if (ptr) {
        SDL_DestroyTexture(ptr);
        ptr = nullptr;
    }
}

// text output
void textout(float x, float y, const char* text, Color color)
{
    //const Color bg = Color();
    //SDL_Surface* surface = TTF_RenderText_Shaded(fontNormal, text, color, bg);
    SDL_Surface* surface = TTF_RenderText_Solid(fontNormal, text, color);
    
    if (surface) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture) {
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

            int w, h;
            SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

            SDL_Rect rect = { x, y, w, h };
            SDL_RenderCopy(renderer, texture, nullptr, &rect);

            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }
}

// Return text width
int textwidth(const char* text)
{
    int n;
    TTF_SizeText(fontNormal, text, &n, nullptr);
    return n;
}
