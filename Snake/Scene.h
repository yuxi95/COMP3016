#pragma once

#include "Object.h"
#include "Fruit.h"
#include "Snake.h"

// ��Ϸ��������
enum SceneType
{
    Menu,       // ���˵�
    Settings,   // ���ý���
    Game,       // ��Ϸ����
    End,        // ��������
};

// ��ť
struct Button
{
    SceneType scene;
    SDL_Rect bounds;
    std::string text;
    SDL_Texture* texture;
};

//
// ������
//

class Scene
{
public:
    Scene(SDL_Renderer* renderer);
    ~Scene();

    SDL_Renderer* renderer() const;

    void keyDown(int key);      // ��������
    void click(int x, int y);   // �����

    void update(float delay);
    void draw();

private:
    SDL_Renderer* m_renderer;   // ��Ⱦ������
    SceneType m_scene;          // ��ǰ����

    // ͼƬ
    SDL_Texture* texLogo;
    SDL_Texture* texMenu;
    SDL_Texture* texSettings;
    SDL_Texture* texStart;
    SDL_Texture* texExit;
    SDL_Texture* texPause;

    Mix_Music* music;       // ����
    Mix_Chunk* chunkEat;    // ��Ч
    Mix_Chunk* chunkDie;

    std::vector<Button> buttons;    // ���水ť�б�

    bool isPause;       // �Ƿ���ͣ
    int snakeStyle;     // �ߵ���ʽ
    bool gridOn;        // �Ƿ���ʾ����
    bool soundOn;       // �Ƿ񲥷���Ч
    Snake* snake;       // �߶���
    std::vector<Fruit*> fruits; // ʳ���б�
    int score; // ����

    // game
    float fruitTime; // ʳ��ˢ�µ���ʱ

    void startGame();
    void endGame();
    void refreshFruit(float delay);
    void checkEat();

    void drawGrid(); // ��������
};
