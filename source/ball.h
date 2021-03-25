#include "main.h"

#ifndef BALL_H
#define BALL_H

class Ball
{
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;

private:
    VAO *object;
};
class Player
{
public:
    Player() {}
    Player(int x, int y);
    int current_x;
    int current_y;
    void draw();
};
#endif // BALL_H
