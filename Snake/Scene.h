#pragma once

#include "Object.h"
#include "Fruit.h"
#include "Snake.h"

// 游戏场景界面
enum SceneType
{
    Menu,       // 主菜单
    Settings,   // 设置界面
    Game,       // 游戏界面
    End,        // 结束界面
};

// 按钮
struct Button
{
    SceneType scene;
    SDL_Rect bounds;
    std::string text;
    SDL_Texture* texture;
};

//
// 场景类
//

class Scene
{
public:
    Scene(SDL_Renderer* renderer);
    ~Scene();

    SDL_Renderer* renderer() const;

    void keyDown(int key);      // 按键按下
    void click(int x, int y);   // 鼠标点击

    void update(float delay);
    void draw();

private:
    SDL_Renderer* m_renderer;   // 渲染器对象
    SceneType m_scene;          // 当前场景

    // 图片
    SDL_Texture* texLogo;
    SDL_Texture* texMenu;
    SDL_Texture* texSettings;
    SDL_Texture* texStart;
    SDL_Texture* texExit;
    SDL_Texture* texPause;

    Mix_Music* music;       // 音乐
    Mix_Chunk* chunkEat;    // 音效
    Mix_Chunk* chunkDie;

    std::vector<Button> buttons;    // 界面按钮列表

    bool isPause;       // 是否暂停
    int snakeStyle;     // 蛇的样式
    bool gridOn;        // 是否显示网络
    bool soundOn;       // 是否播放音效
    Snake* snake;       // 蛇对象
    std::vector<Fruit*> fruits; // 食物列表
    int score; // 分数

    // game
    float fruitTime; // 食物刷新倒计时

    void startGame();
    void endGame();
    void refreshFruit(float delay);
    void checkEat();

    void drawGrid(); // 绘制网格
};
