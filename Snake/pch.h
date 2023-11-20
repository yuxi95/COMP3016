#pragma once


#define _CRT_SECURE_NO_WARNINGS

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

// stl
#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#ifdef defined(_M_AMD64) || defined(_M_X64)
    #pragma comment(lib, "lib/x64/SDL2.lib")
    #pragma comment(lib, "lib/x64/SDL2_image.lib")
    #pragma comment(lib, "lib/x64/SDL2_mixer.lib")
    #pragma comment(lib, "lib/x64/SDL2_ttf.lib")
    #pragma comment(lib, "lib/x64/SDL2main.lib")
    #pragma comment(lib, "lib/x64/SDL2test.lib")
#else
    #pragma comment(lib, "lib/x86/SDL2.lib")
    #pragma comment(lib, "lib/x86/SDL2_image.lib")
    #pragma comment(lib, "lib/x86/SDL2_mixer.lib")
    #pragma comment(lib, "lib/x86/SDL2_ttf.lib")
    #pragma comment(lib, "lib/x86/SDL2main.lib")
    #pragma comment(lib, "lib/x86/SDL2test.lib")
#endif

//
// Color
//

class Color : public SDL_Colour
{
public:
    Color()
    {
        this->r = 0;
        this->g = 0;
        this->b = 0;
        this->a = 0;
    }

    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

//
// Point
//

class Point : public SDL_FPoint
{
public:
    Point()
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }

    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    Point& operator=(const Point& p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }
};

// add
inline Point operator+(const Point& p, float n)
{
    return Point(p.x + n, p.y + n);
}

inline Point operator+(float n, const Point& p)
{
    return Point(n + p.x, n + p.y);
}

inline Point operator+(const Point& p1, const Point& p2)
{
    return Point(p1.x + p2.x, p1.y + p2.y);
}

 // sub
inline Point operator-(const Point& p, float n)
{
    return Point(p.x - n, p.y - n);
}

inline Point operator-(float n, const Point& p)
{
    return Point(n - p.x, n - p.y);
}

inline Point operator-(const Point& p1, const Point& p2)
{
    return Point(p1.x - p2.x, p1.y - p2.y);
}

// multiple
inline Point operator*(const Point& p, float n)
{
    return Point(p.x * n, p.y * n);
}

inline Point operator*(float n, const Point& p)
{
    return Point(n * p.x, n * p.y);
}

inline Point operator*(const Point& p1, const Point& p2)
{
    return Point(p1.x * p2.x, p1.y * p2.y);
}

// return length of point
inline float length(const Point& p)
{
    return (float) sqrt(p.x * p.x + p.y * p.y);
}

// get angle
inline float degreeAngle(const Point& p)
{
    return static_cast<float>(atan2(p.y, p.x) * 180.0 / M_PI);
}

//
// Auxiliary
//

// Load texture
SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filename);

// delete texture
void freeTexture(SDL_Texture* &ptr);

// text output
void textout(float x, float y, const char* text, Color color);

// Return text width
int textwidth(const char* text);
