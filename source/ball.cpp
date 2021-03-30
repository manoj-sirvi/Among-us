#include "ball.h"
#include "main.h"
#include <vector>
#include <GL/freeglut.h>
// #include <ft2build.h>
// #include FT_FREETYPE_H

// Ball::Ball(float x, float y, color_t color) {
//     this->position = glm::vec3(x, y, 0);
//     this->rotation = 0;
//     speed = 1;
//     // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
//     // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
//     static const GLfloat vertex_buffer_data[] = {
//         -1.0f,-1.0f,-1.0f, // triangle 1 : begin
//         -1.0f,-1.0f, 1.0f,
//         -1.0f, 1.0f, 1.0f, // triangle 1 : end
//         1.0f, 1.0f,-1.0f, // triangle 2 : begin
//         -1.0f,-1.0f,-1.0f,
//         -1.0f, 1.0f,-1.0f, // triangle 2 : end
//         1.0f,-1.0f, 1.0f,
//         -1.0f,-1.0f,-1.0f,
//         1.0f,-1.0f,-1.0f,
//         1.0f, 1.0f,-1.0f,
//         1.0f,-1.0f,-1.0f,
//         -1.0f,-1.0f,-1.0f,
//         -1.0f,-1.0f,-1.0f,
//         -1.0f, 1.0f, 1.0f,
//         -1.0f, 1.0f,-1.0f,
//         1.0f,-1.0f, 1.0f,
//         -1.0f,-1.0f, 1.0f,
//         -1.0f,-1.0f,-1.0f,
//         -1.0f, 1.0f, 1.0f,
//         -1.0f,-1.0f, 1.0f,
//         1.0f,-1.0f, 1.0f,
//         1.0f, 1.0f, 1.0f,
//         1.0f,-1.0f,-1.0f,
//         1.0f, 1.0f,-1.0f,
//         1.0f,-1.0f,-1.0f,
//         1.0f, 1.0f, 1.0f,
//         1.0f,-1.0f, 1.0f,
//         1.0f, 1.0f, 1.0f,
//         1.0f, 1.0f,-1.0f,
//         -1.0f, 1.0f,-1.0f,
//         1.0f, 1.0f, 1.0f,
//         -1.0f, 1.0f,-1.0f,
//         -1.0f, 1.0f, 1.0f,
//         1.0f, 1.0f, 1.0f,
//         -1.0f, 1.0f, 1.0f,
//         1.0f,-1.0f, 1.0f
//     };

//     this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
// }

// void Ball::draw(glm::mat4 VP) {
//     Matrices.model = glm::mat4(1.0f);
//     glm::mat4 translate = glm::translate (this->position);    // glTranslatef
//     glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
//     // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
//     // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
//     Matrices.model *= (translate * rotate);
//     glm::mat4 MVP = VP * Matrices.model;
//     glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
//     draw3DObject(this->object);
// }

// void Ball::set_position(float x, float y) {
//     this->position = glm::vec3(x, y, 0);
// }

// void Ball::tick() {
//     this->rotation += speed;
//     // this->position.x -= speed;
//     // this->position.y -= speed;
// }

Ball::Ball(int x, int y, float red1, float green, float blue)
{
    // std::cout << "zishan"
    //           << "\n";
    this->current_x = x;
    this->current_y = y;
    this->red = red1;
    this->green = green;
    this->blue = blue;

    this->draw();
}
int Ball::getx()
{
    return this->current_x;
}
int Ball::gety()
{
    return this->current_y;
}
void Ball::setx(int value)
{
    this->current_x = value;
    // return this->current_x;
}
void Ball::sety(int value)
{
    this->current_y = value;
    // return this->current_x;
}

void Ball::draw()
{
    // std::cout << this->current_x << " " << this->current_y << "\n";
    int x = this->current_x;
    int y = this->current_y;
    glBegin(GL_TRIANGLE_FAN);
    // glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 20; i++)
    {
        float theta = 2.0f * M_PI * float(i) / float(40); //get the current angle

        float x1 = 5 * cosf(theta); //calculate the x component
        float y1 = 5 * sinf(theta); //calculate the y component

        glColor3f(this->red, this->green, this->blue);
        glVertex2f(x1 + x, y1 + y); //output vertex
    }
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(this->red / 2, this->green / 2, this->blue);
    glVertex2f(x + 2, y + 2);
    glVertex2f(x + 2, y + 3);
    glVertex2f(x + 3, y + 2);
    glVertex2f(x + 3, y + 3);
    glVertex2f(x + 2, y + 3);
    glVertex2f(x + 3, y + 2);
    glVertex2f(x - 5, y);
    glVertex2f(x + 5, y);
    glVertex2f(x + 5, y - 5);
    glVertex2f(x - 5, y);
    glVertex2f(x + 5, y - 5);
    glVertex2f(x - 5, y - 5);
    glVertex2f(x + 2 - 5, y + 2);
    glVertex2f(x + 2 - 5, y + 3);
    glVertex2f(x + 3 - 5, y + 2);
    glVertex2f(x + 3 - 5, y + 3);
    glVertex2f(x + 2 - 5, y + 3);
    glVertex2f(x + 3 - 5, y + 2);

    glEnd();

    // std::cout << this->current_x << " " << this->current_y << "\n";
}

Coin::Coin(int x, int y)
{
    this->current_x = x;
    this->current_y = y;
}

void Coin::draw()
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 40; i++)
    {
        float theta = 2.0f * M_PI * float(i) / float(40); //get the current angle

        float x1 = 5 * cosf(theta); //calculate the x component
        float y1 = 5 * sinf(theta); //calculate the y component

        glColor3f(1, 0, 1);
        glVertex2f(x1 + this->current_x, y1 + this->current_y); //output vertex
    }
    glEnd();
}

Obstacles::Obstacles(int x, int y, int f)
{
    this->current_x = x;
    this->current_y = y;
    this->type = f;
    if (f > 0)
    {
        this->score = 10;
    }
    else
    {
        this->score = -8;
    }
}
void Obstacles::draw()
{
    if (this->type > 0)
    {
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i <= 40; i++)
        {
            float theta = 2.0f * M_PI * float(i) / float(40); //get the current angle

            float x1 = 5 * cosf(theta); //calculate the x component
            float y1 = 5 * sinf(theta); //calculate the y component

            glColor3f(1, 1, 0);
            glVertex2f(x1 + this->current_x, y1 + this->current_y); //output vertex
        }
        glEnd();
    }
    else
    {
        if (this->type < 0)
        {
            glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i <= 40; i++)
            {
                float theta = 2.0f * M_PI * float(i) / float(40); //get the current angle

                float x1 = 5 * cosf(theta); //calculate the x component
                float y1 = 5 * sinf(theta); //calculate the y component

                glColor3f(0.5, 0.5, 0.5);
                glVertex2f(x1 + this->current_x, y1 + this->current_y); //output vertex
            }
            glEnd();
            // glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_POINTS);
            for (GLfloat x = -2; x <= 2; x += 0.05)
            {
                GLfloat y = x * x;
                glVertex2f(current_x + x, current_y + 5 + y);
            }
            glEnd();
        }
    }
}

void render_text(const char *text, float x, float y, float sx, float sy)
{
    // const char *p;

    // for (p = text; *p; p++)
    // {
    //     if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
    //         continue;

    //     glTexImage2D(
    //         GL_TEXTURE_2D,
    //         0,
    //         GL_RED,
    //         g->bitmap.width,
    //         g->bitmap.rows,
    //         0,
    //         GL_RED,
    //         GL_UNSIGNED_BYTE,
    //         g->bitmap.buffer);

    //     float x2 = x + g->bitmap_left * sx;
    //     float y2 = -y - g->bitmap_top * sy;
    //     float w = g->bitmap.width * sx;
    //     float h = g->bitmap.rows * sy;

    //     GLfloat box[4][4] = {
    //         {x2, -y2, 0, 0},
    //         {x2 + w, -y2, 1, 0},
    //         {x2, -y2 - h, 0, 1},
    //         {x2 + w, -y2 - h, 1, 1},
    //     };

    //     glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
    //     glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    //     x += (g->advance.x / 64) * sx;
    //     y += (g->advance.y / 64) * sy;
    // }
}
