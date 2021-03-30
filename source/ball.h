#include "main.h"

#ifndef BALL_H
#define BALL_H

// class Ball
// {
// public:
//     Ball() {}
//     Ball(float x, float y, color_t color);
//     glm::vec3 position;
//     float rotation;
//     void draw(glm::mat4 VP);
//     void set_position(float x, float y);
//     void tick();
//     double speed;

// private:
//     VAO *object;
// };
class Ball
{
public:
    Ball() {}
    Ball(int x, int y, float red1, float green, float blue);
    void draw();
    int getx();
    int gety();
    void setx(int value);
    void sety(int value);
    float red;
    float blue;
    float green;

private:
    int current_x;
    int current_y;
};

class Coin
{
public:
    Coin() {}
    Coin(int x, int y);
    int current_x;
    int current_y;
    void draw();
};
class Obstacles
{
public:
    Obstacles() {}
    Obstacles(int x, int y, int f);
    int current_x;
    int current_y;
    int score;
    int type;
    void draw();
};

#endif // BALL_H
