#pragma once

#include "Object.h"

const int INIT_NODES = 3;           // 初始长度
const float SNAKE_SPEED = 32.0f;    // 基础速度

//
// 蛇
//

class Snake : public Object
{
public:
    Snake(Scene* scene, int style);
    ~Snake();

    void init();

    Point head() const;         // 获取头节点位置
    int size() const;           // 返回长度
    void setDir(Point dir);     // 设置方向
    float speed() const;        // 返回速度
    void setSpeed(float value); // 设置速度
    void grow(int n);           // 增长
    bool hitSelf() const;       // 判断是否碰到了自己

    void update(float delay);
    void draw();

private:
    SDL_Texture* texHead;
    SDL_Texture* texBody;
    SDL_Texture* texTail;

    Point m_dir;        // 当前蛇方向
    float m_speed;      // 速度

    std::vector<Point> m_nodes; // 蛇节点
    std::deque<Point> m_path;   // 路径

    // 绘制节点
    void drawNode(int index);
};

