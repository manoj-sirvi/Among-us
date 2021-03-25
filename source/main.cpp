#include "main.h"
#include "timer.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include "ball.h"
#include <SOIL/SOIL.h>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;
int width = 15, height = 15;
GridBox *grid;
Player *player = NULL;
int previous = 0;

GridBox &getposition(int x, int y)
{
    // if (y * 10 + x >= 99)
    // {
    //     cerr << "gfgh " << x << y << "\n";
    // }
    return grid[(y)*10 + x];
}
// /**************************
// * Customizable functions *
// **************************/

// Ball ball1;

// float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
// float camera_rotation_angle = 0;

// Timer t60(1.0 / 60);

// /* Render the scene with openGL */
// /* Edit this function according to your assignment */
// void draw()
// {
//     // clear the color and depth in the frame buffer
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     // use the loaded shader program
//     // Don't change unless you know what you are doing
//     glUseProgram(programID);

//     // Eye - Location of camera. Don't change unless you are sure!!
//     glm::vec3 eye(5 * cos(camera_rotation_angle * M_PI / 180.0f), 0, 5 * sin(camera_rotation_angle * M_PI / 180.0f));
//     // Target - Where is the camera looking at.  Don't change unless you are sure!!
//     glm::vec3 target(0, 0, 0);
//     // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
//     glm::vec3 up(0, 1, 0);

//     // Compute Camera matrix (view)
//     Matrices.view = glm::lookAt(eye, target, up); // Rotating Camera for 3D
//     // Don't change unless you are sure!!
//     // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

//     // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
//     // Don't change unless you are sure!!
//     glm::mat4 VP = Matrices.projection * Matrices.view;

//     // Send our transformation to the currently bound shader, in the "MVP" uniform
//     // For each model you render, since the MVP will be different (at least the M part)
//     // Don't change unless you are sure!!
//     glm::mat4 MVP; // MVP = Projection * View * Model

//     // Scene render
//     ball1.draw(VP);
// }

// void tick_input(GLFWwindow *window)
// {
//     int left = glfwGetKey(window, GLFW_KEY_LEFT);
//     int right = glfwGetKey(window, GLFW_KEY_RIGHT);
//     if (left)
//     {
//         // Do something
//     }
// }

// void tick_elements()
// {
//     ball1.tick();
//     camera_rotation_angle += 1;
// }

// // /* Initialize the OpenGL rendering properties */
// // /* Add all the models to be created here */
// // void initGL(GLFWwindow *window, int width, int height)
// {
//     /* Objects should be created before any other gl function and shaders */
//     // Create the models

//     ball1 = Ball(0, 0, COLOR_RED);

//     // Create and compile our GLSL program from the shaders
//     programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
//     // Get a handle for our "MVP" uniform
//     Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

//     reshapeWindow(window, width, height);

//     // Background color of the scene
//     glClearColor(COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
//     glClearDepth(1.0f);

//     glEnable(GL_DEPTH_TEST);
//     glDepthFunc(GL_LEQUAL);

//     cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
//     cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
//     cout << "VERSION: " << glGetString(GL_VERSION) << endl;
//     cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
// }
void remove_line(int x, int y, int dest)
{
    glBegin(GL_LINES);
    // cout << "called"
    //      << " " << dest << "\n";
    switch (dest)
    {
    case 0:
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(x * 30 + 150, y * 30 + 150); //left
        glVertex2f(x * 30 + 150, (y + 1) * 30 + 150);
        // cout << x * 30 + 150 << " " << y * 30 + 150 << "\n";

        break;
    case 1:
        glColor3f(0.0, 0, 0.0);
        glVertex2f(x * 30 + 150, y * 30 + 150);
        glVertex2f((x + 1) * 30 + 150, (y)*30 + 150); //down
        // cout << x * 30 + 150 << " " << y * 30 + 150 << "\n";
        break;

    case 2:
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f((x + 1) * 30 + 150, y * 30 + 150);
        glVertex2f((x + 1) * 30 + 150, (y + 1) * 30 + 150); //right
        // cout << x * 30 + 150 << " " << y * 30 + 150 << "\n";
        break;

    case 3:
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f((x)*30 + 150, (y + 1) * 30 + 150);
        glVertex2f((x + 1) * 30 + 150, (y + 1) * 30 + 150); //up
        // cout << x * 30 + 150 << " " << y * 30 + 150 << "\n";
        break;
    }
    glEnd();
    // exit(0);
}

void dfs(int x, int y)
{
    getposition(x, y).isVisited = true;

    // vec1.resize(4);
    // int counter = 0;
    vector<pair<int, int>> vec;
    // vec.resize(4);

    vector<int> vec1;
    // cout << x << " " << y << "\n";
    // cout << "checking"
    //      << "\n";
    // cerr << getposition(x, y - 1).isVisited << "\n";
    if (y != 0 && getposition(x, y - 1).isVisited == false)
    {
        vec.push_back({x, y - 1});
        vec1.push_back(1); //down
        // cerr << "checking1"
        //      << "\n";
    }
    if (x != 0 && getposition(x - 1, y).isVisited == false)
    {
        vec.push_back({x - 1, y});
        vec1.push_back(0); //left
        // cerr << "checking2"
        //      << "\n";
    }
    if (y != 9 && getposition(x, y + 1).isVisited == false)
    {
        vec.push_back({x, y + 1});
        vec1.push_back(3); //up
        // cerr << "checking3"
        //      << "\n";
    }
    if (x != 9 && getposition(x + 1, y).isVisited == false)
    {
        // vec[counter++] = {x + 1, y};
        vec.push_back({x + 1, y});
        vec1.push_back(2); //right
        // cerr << "checking4"
        //  << "\n";
    }
    while (vec.size())
    {
        int a = rand() % vec.size();
        a += 2;
        a %= vec.size();
        // cout << "a " << a << "\n";
        vector<pair<int, int>> vec4;
        // vec.resize(4);

        vector<int> vec3;
        if (getposition(vec[a].first, vec[a].second).isVisited == false)
        {
            if (vec1[a] == previous)
            {
                a += rand();
                a %= vec.size();
            }
            previous = vec1[a];
            switch (vec1[a])
            {
            case 0:
                getposition(x, y).walls.left = 1;
                getposition(x - 1, y).walls.right = 1;
                remove_line(x, y, 0);
                break;
            case 1:
                getposition(x, y).walls.down = 1;
                getposition(x, y - 1).walls.up = 1;
                remove_line(x, y, 1);
                break;
            case 2:
                getposition(x, y).walls.right = 1;
                getposition(x + 1, y).walls.left = 1;
                remove_line(x, y, 2);
                break;
            case 3:
                getposition(x, y).walls.up = 1;
                getposition(x, y + 1).walls.down = 1;
                remove_line(x, y, 3);
                break;
            }
            dfs(vec[a].first, vec[a].second);
        }
        for (int i = 0; i < vec.size(); i++)
        {
            if (i != a)
            {
                vec3.push_back(vec1[i]);
                vec4.push_back({vec[i].first, vec[i].second});
            }
        }
        vec1 = vec3;
        vec = vec4;
        // vec.erase(a);
        // vec1.erase(a);
    }

    // vec.clear();
    // vec1.clear();
    return;
}
void Gener_field()
{
    bool f = 0;
    int x = rand() % 10;
    int y = rand() % 10;
    Player special(x * 30 + 165, y * 30 + 165);
    player = &special;
    if (player != NULL)
    {
        // cout << "fgh"
        //  << "\n";
        player->draw();
    }
    cout << "yes"
         << "\n";
    dfs(x, y);
}
void update_maze()
{
    for (int i = 0; i < 10 * 10; i++)
    {
        int x = i % 10 + 150;
        int y = i / 10 + 150;
        if (grid[i].walls.up == true)
        {
            remove_line(x, y, 0);
        }
    }
}
GLuint loadTexture(char const *filename)
{

    GLuint texture;
    // int width, height;
    unsigned char *data;
    // char filename[] = "source/gZZrBVXJG5yiMxfuAgJqok.png";
    FILE *file;
    // cout << filename << "\n";
    file = fopen(filename, "rb");

    if (file == NULL)
    {
        perror("Error:");
        // cout << "checker"
        //      << "\n";
        return 0;
    }
    data = (unsigned char *)malloc(WIDTH * HEIGHT * 3);
    //int size = fseek(file,);
    fread(data, WIDTH * HEIGHT * 3, 1, file);
    fclose(file);

    for (int i = 0; i < WIDTH * HEIGHT; ++i)
    {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];

        data[index] = R;
        data[index + 2] = B;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);

    return texture;
}

void draw_texture()
{
    char const *name = "../source/1.bmp";
    GLuint id = loadTexture(name);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(150, 150);

    glTexCoord2f(1, 0);
    glVertex2f(450, 150);

    glTexCoord2f(1, 1);
    glVertex2f(450, 450);

    glTexCoord2f(0, 1);
    glVertex2d(150, 450);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}
void display()
{

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    draw_texture();
    double x = 1;
    glLoadIdentity();
    // GLfloat lineWidthRange[2] = {0.0f, 1.0f};
    // glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
    glLineWidth(5);
    glBegin(GL_LINES);
    for (x = 5; x < width + 1; x++)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x * 30, 150);
        glVertex2f(x * 30, 450);
    }
    for (x = 5; x < height + 1; x++)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(150.0, x * 30);
        glVertex2f(450, x * 30);
    }
    glEnd();
    // int x1 = rand() % 10;
    // int y = rand() % 10;
    // Player special(x1 * 30 + 165, y * 30 + 165);
    // player = &special;
    // cout << "gh"
    //      << "\n";
    // player = Player(195, 165);
    if (player != NULL)
    {
        // cout << "fgh"
        //  << "\n";
        player->draw();
    }
    Gener_field();

    // glFlush();

    // update_maze();
    // glBegin(GL_LINES);
    // glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    srand(time(0));
    // int width = 600;
    // int height = 600;

    // window = initGLFW(width, height);
    grid = new GridBox[100];
    glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Among-Us");
    init();
    // initGL(window, width, height);
    // glutInit(&argc, argv);
    glutDisplayFunc(display);
    glutMainLoop();

    /* Draw in loop */
    // while (!glfwWindowShouldClose(window))
    // {
    //     // Process timers

    //     if (t60.processTick())
    //     {
    //         // 60 fps
    //         // OpenGL Draw commands
    //         // draw();
    //         glutDisplayFunc(display);
    //         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //         // use the loaded shader program
    //         // Don't change unless you know what you are doing
    //         glUseProgram(programID);

    //         // Swap Frame Buffer in double buffering
    //         glfwSwapBuffers(window);

    //         tick_elements();
    //         tick_input(window);
    //     }

    //     // Poll for Keyboard and mouse events
    //     glfwPollEvents();
    // }

    // quit(window);
}

// bool detect_collision(bounding_box_t a, bounding_box_t b)
// {
//     return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
//            (abs(a.y - b.y) * 2 < (a.height + b.height));
// }

// void reset_screen()
// {
//     float top = screen_center_y + 4 / screen_zoom;
//     float bottom = screen_center_y - 4 / screen_zoom;
//     float left = screen_center_x - 4 / screen_zoom;
//     float right = screen_center_x + 4 / screen_zoom;
//     Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
// }
