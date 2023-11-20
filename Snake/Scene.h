#pragma once

#include "Object.h"
#include "Fruit.h"
#include "Snake.h"

// Game scene interface
enum SceneType
{
    Menu,       // Menu
    Settings,   // Settings
    Game,       // Game
    End,        // End
};

// Button
struct Button
{
    SceneType scene;
    SDL_Rect bounds;
    std::string text;
    SDL_Texture* texture;
};

//
// Scene
//

class Scene
{
public:
    Scene(SDL_Renderer* renderer);
    ~Scene();

    SDL_Renderer* renderer() const;

    void keyDown(int key);      // Key press
    void click(int x, int y);   // mouse click

    void update(float delay);
    void draw();

private:
    SDL_Renderer* m_renderer;   // Renderer object
    SceneType m_scene;          // Current scene

    // image
    SDL_Texture* texLogo;
    SDL_Texture* texMenu;
    SDL_Texture* texSettings;
    SDL_Texture* texStart;
    SDL_Texture* texExit;
    SDL_Texture* texPause;

    Mix_Music* music;       // music
    Mix_Chunk* chunkEat;    // sound
    Mix_Chunk* chunkDie;

    std::vector<Button> buttons;    // Interface button list

    bool isPause;       // Whether to pause
    int snakeStyle;     // snakeStyle
    bool gridOn;        // Show grid or not
    bool soundOn;       // SoundOn or off
    Snake* snake;       // Snake object
    std::vector<Fruit*> fruits; // Food list
    int score; // score

    // game
    float fruitTime; // Food refresh countdown

    void startGame();
    void endGame();
    void refreshFruit(float delay);
    void checkEat();

    void drawGrid(); // drawGrid
};
