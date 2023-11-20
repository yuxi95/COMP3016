#pragma once

#include "Object.h"

// ��ͬˮ����Ӧ��ͬ��������Ӧ��������������Ӧ�ĳ��ȣ� ����5��
enum class FruitType
{
    Black,      // ��ɫ ���÷�
    Bronw,      // ��ɫ ���÷�
    Red,        // ��ɫ 3��
    Blue,       // ��ɫ 2��
    Green,      // ��ɫ 1��
};

class Fruit : public Object
{
public:
    Fruit(Scene* scene);
    ~Fruit();

    FruitType getType() const;          // ��ȡ����
    void setType(FruitType type);       // ��������    

    Point position() const;             // ��ȡλ��
    void setPosition(Point pos);        // ����λ��
    void setPosition(float x, float y);

    float size() const; // ���ش�С
    void setSize(float value); // ���ô�С

    void update(float delay);
    void draw();

private:
    FruitType m_type;   // ����
    Color m_color;      // ������ɫ
    Point m_pos;        // λ��
    float m_size;       // ��С

    SDL_Texture* m_texture; // ����
};

