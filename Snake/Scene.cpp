#include "Scene.h"

using namespace std;

Scene::Scene(SDL_Renderer* renderer) : m_renderer(renderer)
{
    texLogo = loadTexture(renderer, "../logo.png");
    texMenu = loadTexture(renderer, "../menu.png");
    texSettings = loadTexture(renderer, "../settings.png");
    texStart = loadTexture(renderer, "../start.png");
    texExit = loadTexture(renderer, "../exit.png");
    texPause = loadTexture(renderer, "../pause.png");

    // sounds
    music = Mix_LoadMUS("../bg_music.mp3");
    Mix_PlayMusic(music, -1);

    chunkEat = Mix_LoadWAV("../eating.wav");
    chunkDie = Mix_LoadWAV("../die.wav");

    // scene and buttons
    m_scene = SceneType::Menu;

    // menu buttons
    buttons.push_back({ SceneType::Menu, {800 / 2 - 150, 400, 58, 58}, "settings", texSettings });
    buttons.push_back({ SceneType::Menu, {800 / 2 - 29, 400, 58, 58}, "start", texStart });
    buttons.push_back({ SceneType::Menu, {800 / 2 + 92, 400, 58, 58}, "exit", texExit });

    // setting buttons
    buttons.push_back({ SceneType::Settings, {800 / 2 - 280, 280, 160, 40}, "yellow Snake", nullptr });
    buttons.push_back({ SceneType::Settings, {800 / 2 - 280, 330, 160, 40}, "purple Snake", nullptr });

    buttons.push_back({ SceneType::Settings, {800 / 2 - 80, 280, 160, 40}, "grid off", nullptr });
    //buttons.push_back({ SceneType::Settings, {800 / 2 - 80, 330, 160, 40}, "grid off", nullptr });

    buttons.push_back({ SceneType::Settings, {800 / 2 + 120, 280, 160, 40}, "sound on", nullptr });
    buttons.push_back({ SceneType::Settings, {800 / 2 + 120, 330, 160, 40}, "music on", nullptr });

    buttons.push_back({ SceneType::Settings, {800 / 2 - 29, 450, 58, 58}, "menu", texMenu });

    // game
    buttons.push_back({ SceneType::Game, {800 - 100, 4, 40, 40 }, "pause", texPause });
    buttons.push_back({ SceneType::Game, {800 - 50, 4, 40, 40 }, "menu", texMenu });

    // game end
    buttons.push_back({ SceneType::End, {800 / 2 - 150, 400, 58, 58}, "menu", texMenu });
    buttons.push_back({ SceneType::End, {800 / 2 - 29, 400, 58, 58}, "start", texStart });
    buttons.push_back({ SceneType::End, {800 / 2 + 92, 400, 58, 58}, "exit", texExit });

    snake = nullptr;
    snakeStyle = 0;
    gridOn = false;
    soundOn = true;

}

Scene::~Scene()
{
    freeTexture(texLogo);
    freeTexture(texMenu);
    freeTexture(texSettings);
    freeTexture(texStart);
    freeTexture(texExit);
    freeTexture(texPause);

    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    if (chunkEat) {
        Mix_FreeChunk(chunkEat);
        chunkEat = nullptr;
    }

    if (chunkDie) {
        Mix_FreeChunk(chunkDie);
        chunkDie = nullptr;
    }

    endGame();
}

SDL_Renderer* Scene::renderer() const
{
    return m_renderer;
}

// keyDown
void Scene::keyDown(int key)
{
    // move snake
    if (m_scene == SceneType::Game) {

    }
}

// click 
void Scene::click(int x, int y)
{
    SDL_Point pos = { x, y };
    Button* button = nullptr;
    for (size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i].scene == m_scene) {
            if (SDL_PointInRect(&pos, &buttons[i].bounds)) {// Mouse click button range
                button = &buttons[i];
            }
        }
    }

    // Process the command according to the name of the button returned by clicking
    if (button) {
        if (button->text == "start") {
            this->startGame();
        }
        else if (button->text == "menu") {
            endGame();
            m_scene = SceneType::Menu;
        }
        else if (button->text == "settings") {
            m_scene = SceneType::Settings;
        }
        else if (button->text == "exit") {
            SDL_Event event;
            event.quit = { SDL_QUIT, SDL_GetTicks() };
            SDL_PushEvent(&event);
        }
        else if (button->text == "pause") {
            isPause = !isPause;
        }
        else if (button->text == "yellow Snake") {
            snakeStyle = 0;
        }
        else if (button->text == "purple Snake") {
            snakeStyle = 1;
        }
        else if (button->text == "grid on") {
            gridOn = false;
            button->text = "grid off";
        }
        else if (button->text == "grid off") {
            gridOn = true;
            button->text = "grid on";
        }
        else if (button->text == "sound on") {
            soundOn = false;
            button->text = "sound off";
        }
        else if (button->text == "sound off") {
            soundOn = true;
            button->text = "sound on";
        }
        else if (button->text == "music on") {
            button->text = "music off";
            Mix_HaltMusic();
        }
        else if (button->text == "music off") {
            button->text = "music on";
            Mix_PlayMusic(music, -1);
        }
    }
    else {
        // move snake
        if (m_scene == SceneType::Game) {
            Point dir = Point(x, y) - snake->head();
            snake->setDir(dir);
        }
    }
}

void Scene::update(float delay)
{
    // Draw according to the current interface
    switch (m_scene) {
    case SceneType::Menu:
        break;
    case SceneType::Settings:
        break;
    case SceneType::Game:
        if (!isPause) {
            // refreshFruit
            refreshFruit(delay);

            // keyboard control
            const uint8_t* keyboard = SDL_GetKeyboardState(nullptr);
            Point dir;
            if (keyboard[SDL_SCANCODE_W] || keyboard[SDL_SCANCODE_UP]) {
                dir.y = -1.0f;
            }
            else if (keyboard[SDL_SCANCODE_S] || keyboard[SDL_SCANCODE_DOWN]) {
                dir.y = 1.0f;
            }

            if (keyboard[SDL_SCANCODE_A] || keyboard[SDL_SCANCODE_LEFT]) {
                dir.x = -1.0f;
            }
            else if (keyboard[SDL_SCANCODE_D] || keyboard[SDL_SCANCODE_RIGHT]) {
                dir.x = 1.0f;
            }
            if (length(dir) > 0.0f) {
                snake->setDir(dir);
            }

            // space
            if (keyboard[SDL_SCANCODE_SPACE]) {
                for (int i = 0; i < 2; ++i) { // Double speed
                    // eat and move
                    checkEat();
                    snake->update(delay);
                }
            }
            else {
                // eat and move
                checkEat();
                snake->update(delay);
            }

            // Determine whether you have touched yourself
            if (snake->hitSelf()) {
                endGame();
                m_scene = SceneType::End;
                if (soundOn) {
                    Mix_PlayChannel(-1, chunkDie, 0);
                }
                cout << "game end" << endl;
            }
        }
        break;
    case SceneType::End:
        break;
    default:
        break;
    }
}

void Scene::draw()
{
    // clean
    SDL_SetRenderDrawColor(m_renderer, 224, 224, 224, 255);
    SDL_RenderClear(m_renderer);

    SDL_Rect rect;
    char buf[256] = { 0 };

    // Draw based on current scene
    switch (m_scene) {
    case SceneType::Menu:
        // logo
        rect = { (800 - 200) / 2, 180, 200, 75 };
        SDL_RenderCopy(m_renderer, texLogo, nullptr, &rect);
        break;
    case SceneType::Settings:
        textout(350, 150, "Settings", Color(0, 0, 0));
        break;
    case SceneType::Game:
        if (gridOn) {
            drawGrid();
        }

        // draw fruits
        for (auto f : fruits) {
            f->draw();
        }
        snake->draw();

        // Top-left fraction
        snprintf(buf, 256, "score: %d", score);
        textout(6, 6, buf, Color(0, 0, 0));
        textout(4, 4, buf, Color(255, 255, 255));

        // Pause prompt
        if (isPause) {
            textout(800 / 2 - 40, 600 / 2, "PAUSE", Color(255, 255, 255));
        }
        break;
    case SceneType::End:
        textout(350, 150, "Game End", Color(0, 0, 0));

        // Points
        snprintf(buf, 256, "total score: %d", score);
        textout(302, 302, buf, Color(0, 0, 0));
        textout(300, 300, buf, Color(255, 255, 255));
        break;
    default:
        break;
    }

    // draw button
    int id = 0;
    for (size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i].scene == m_scene) {
            if (buttons[i].texture) {
                SDL_RenderCopy(m_renderer, buttons[i].texture, nullptr, &buttons[i].bounds);
            }
            else {
                Color color;
                SDL_Point m;
                SDL_GetMouseState(&m.x, &m.y);
                if (SDL_PointInRect(&m, &buttons[i].bounds)) {
                    color = Color(0, 0, 255);
                }
                else {
                    color = Color(0, 0, 0);
                }

                SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 255);
                SDL_RenderDrawRect(m_renderer, &buttons[i].bounds);
                int w = textwidth(buttons[i].text.c_str());

                textout(buttons[i].bounds.x + (buttons[i].bounds.w - w) / 2,
                    buttons[i].bounds.y, buttons[i].text.c_str(), color);
            }
        }
    }

    // state
    snprintf(buf, 256, "snake: %s", snakeStyle == 0 ? "yellow" : "purple");
    textout(4, 500, buf, Color(0, 0, 0));

    snprintf(buf, 256, "grid: %s", gridOn ? "on" : "off");
    textout(4, 525, buf, Color(0, 0, 0));

    snprintf(buf, 256, "sound: %s", soundOn ? "on" : "off");
    textout(4, 550, buf, Color(0, 0, 0));
}

void Scene::startGame()
{
    srand(SDL_GetTicks());

    m_scene = SceneType::Game;

    snake = new Snake(this, snakeStyle);
    snake->init();

    fruitTime = 0.0f;
    score = 0;
    isPause = false;
}

void Scene::endGame()
{
    if (snake) {
        delete snake;
        snake = nullptr;
    }

    for (auto f : fruits) {
        delete f;
    }
    fruits.clear();
}

void Scene::refreshFruit(float delay)
{
    fruitTime -= delay;
    if (fruitTime < 0.0f) {

        // add fruit
        fruits.push_back(new Fruit(this));

        cout << "add fruit" << endl;

        //fruitTime = 5 + (rand() % 5);// 5 ~ 10 second
        fruitTime = 2;
    }
}

void Scene::checkEat()
{
    Point dir;

    if (!fruits.empty()) {
        for (int i = (int) fruits.size() - 1; i >= 0; --i) {
            dir = fruits[i]->position() - snake->head();
            if (length(dir) < 10.0f) {
                Fruit* fruit = fruits[i];
                fruits.erase(fruits.begin() + i);

                switch (fruit->getType()) {
                case FruitType::Black:
                    score += 1;
                    break;
                case FruitType::Bronw:
                    score += 2;
                    break;
                case FruitType::Red:
                    snake->grow(3);
                    score += 30;
                    break;
                case FruitType::Blue:
                    snake->grow(2);
                    score += 20;
                    break;
                case FruitType::Green:
                    snake->grow(1);
                    score += 10;
                    break;
                default:
                    break;
                }

                if (soundOn) {
                    Mix_PlayChannel(-1, chunkEat, 0);
                }
            }
        }
    }
}

void Scene::drawGrid()
{
    const int size = 32;

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 128);
    for (int i = size; i < 800; i += size) {
        SDL_RenderDrawLine(m_renderer, i, 0, i, 600);
    }
    for (int i = size; i < 600; i += size) {
        SDL_RenderDrawLine(m_renderer, 0, i, 800, i);
    }
}
