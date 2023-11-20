#pragma once

#include "Object.h"

// 不同水果对应不同分数（对应分数增长蛇身相应的长度） 共有5种
enum class FruitType
{
    Black,      // 黑色 不得分
    Bronw,      // 棕色 不得分
    Red,        // 红色 3分
    Blue,       // 蓝色 2分
    Green,      // 绿色 1分
};

class Fruit : public Object
{
public:
    Fruit(Scene* scene);
    ~Fruit();

    FruitType getType() const;          // 获取类型
    void setType(FruitType type);       // 设置类型    

    Point position() const;             // 获取位置
    void setPosition(Point pos);        // 设置位置
    void setPosition(float x, float y);

    float size() const; // 返回大小
    void setSize(float value); // 设置大小

    void update(float delay);
    void draw();

private:
    FruitType m_type;   // 类型
    Color m_color;      // 绘制颜色
    Point m_pos;        // 位置
    float m_size;       // 大小

    SDL_Texture* m_texture; // 纹理
};

