#pragma once

#include "Object.h"

const int INIT_NODES = 3;           // ��ʼ����
const float SNAKE_SPEED = 32.0f;    // �����ٶ�

//
// ��
//

class Snake : public Object
{
public:
    Snake(Scene* scene, int style);
    ~Snake();

    void init();

    Point head() const;         // ��ȡͷ�ڵ�λ��
    int size() const;           // ���س���
    void setDir(Point dir);     // ���÷���
    float speed() const;        // �����ٶ�
    void setSpeed(float value); // �����ٶ�
    void grow(int n);           // ����
    bool hitSelf() const;       // �ж��Ƿ��������Լ�

    void update(float delay);
    void draw();

private:
    SDL_Texture* texHead;
    SDL_Texture* texBody;
    SDL_Texture* texTail;

    Point m_dir;        // ��ǰ�߷���
    float m_speed;      // �ٶ�

    std::vector<Point> m_nodes; // �߽ڵ�
    std::deque<Point> m_path;   // ·��

    // ���ƽڵ�
    void drawNode(int index);
};

