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
Ball ball1;
Coin task;
int previous = 0;
int manoj = -1;

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

//     ball1 = ball1(0, 0, COLOR_RED);

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
void Gener_field(int x, int y)
{
    // bool f = 0;

    // cout << "wfhregfre"
    //      << "\n";
    // cout << &ball1 << "\n";
    // // cout << "yes"
    // cout << ball1->current_x << " " << ball1->current_y << "\n";
    //      << "\n";
    dfs(x, y);

    // cout << &(ball1->current_x) << " " << ball1->current_y << "\n";

    // return {ball1->current_x, ball1->current_y};
}
void Get_maze()
{
    // cout << "entering"
    //      << "\n";
    for (int i = 0; i < 100; i++)
    {
        if (grid[i].walls.up)
        {
            remove_line(i % 10, i / 10, 3);
        }
        if (grid[i].walls.down)
        {
            remove_line(i % 10, i / 10, 1);
        }
        if (grid[i].walls.left)
        {
            remove_line(i % 10, i / 10, 0);
        }
        if (grid[i].walls.right)
        {
            remove_line(i % 10, i / 10, 2);
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
    // cout << id << "\n";
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
    // cout << "drawing"
    //      << " "
    //      << "\n";
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
    // ball1 special(x1 * 30 + 165, y * 30 + 165);
    // ball1 = &special;
    // cout << "gh"
    //      << "\n";
    // ball1 = ball1(195, 165);
    // cout << ball1->current_x << " " << ball1->current_y << "\n";
    // cout << &ball1 << "\n";

    // cout << "fgh"
    //  << "\n";
    // cout << "in " << ball1->current_x << " " << ball1->current_y << "\n";
    // cout << ball1->getx() << " " << ball1->gety() << "\n";
    // cout << manoj << "\n";
    // ball1 = Ball(165, 165);
    ball1.draw();
    task.draw();
    Get_maze();

    // Gener_field();

    // glFlush();

    // update_maze();
    // glBegin(GL_LINES);
    // glEnd();

    glFlush();
}
void input_ticks(int key, int x, int y)
{
    // cout << ball1->getx() << " " << ball1->gety() << "\n";
    // cout << x << " " << y << "\n";
    // cout << manoj << "\n";
    // if (ball1 != NULL)
    // {
    //     // cout << "enter "
    //     //      << "\n";
    //     // cout << ball1->current_x << " " << ball1->current_y << "\n";
    //     // int x = ball1->current_x;
    //     // int y = ball1->current_y;
    //     // // cout << x1 << " " << y1 << "\n";
    //     // // cout << (x1 - 165) / 30 << (y1 - 165) / 30 << "\n";
    //     // GridBox Current = getposition((x - 165) / 30, (y - 165) / 30);
    //     // switch (key)
    //     // {
    //     // case GLUT_KEY_UP:
    //     //     if (Current.walls.up == 1)
    //     //     {
    //     //         ball1->current_y += 30;
    //     //     }
    //     //     break;
    //     // case GLUT_KEY_DOWN:
    //     //     if (Current.walls.down == 1)
    //     //     {
    //     //         ball1->current_y -= 30;
    //     //     }
    //     //     break;
    //     // case GLUT_KEY_LEFT:
    //     //     if (Current.walls.left == 1)
    //     //     {
    //     //         ball1->current_x -= 30;
    //     //     }
    //     //     break;
    //     // case GLUT_KEY_RIGHT:
    //     //     if (Current.walls.right == 1)
    //     //     {
    //     //         ball1->current_x += 30;
    //     //     }
    //     //     break;
    //     // default:
    //     //     break;
    //     // }
    // }
    // else
    //     return;
    // display();
}
void input_enter(unsigned char key, int x, int y)
{
    // cout << "dewkfhj"
    //      << "\n";
    // cout << (int)key << "\n";
    if (key == 13)
    {
        // cout << "pressed enter"
        //      << "\n";
        int x = rand() % 10;
        int y = rand() % 10;
        // Ball special(x * 30 + 165, y * 30 + 165);
        // ball1 = &special;
        // ball1->setx(x * 30 + 165);
        // ball1->sety(y * 30 + 165);

        // cout << "fgh"
        //  << "\n";
        ball1 = Ball(x * 30 + 165, y * 30 + 165);
        task = Coin(165, 165);

        // ball1.draw();

        // cout << "x " << x << " " << y << "\n";
        dfs(x, y);
        // manoj = 100;

        // cout << "x " << x << " " << y << "\n";

        // ball1->current_y = re.second;
        // cout << ball1->current_y << " " << 1 << "\n";

        // ball1->current_x = re.first;
        // // cout << "hgghf" << re.first << " " << re.second << "\n";
        // cerr << "x " << ball1->current_x << " " << 1 << "\n";
        // cerr << ball1->current_x << " " << 1 << "\n";
        // cerr << ball1->current_x << " " << 1 << "\n";
        // cerr << ball1->current_x << " " << 1 << "\n";
        // cerr << ball1->current_x << " " << 1 << "\n";
        // cerr << ball1->current_x << " " << 1 << "\n";

        // cerr << "gen " << *(&(ball1->current_y)) << " " << ball1->current_x << "\n";

        // cerr << ball1->current_y << " " << 1 << "\n";
        // // cerr << "gen " << &ball1 << "\n";
        // cerr << "gen " << (ball1->current_x) << " " << ball1->current_y << "\n";
        // cerr << ball1->current_x << " " << ball1->current_y << "\n";
    }
    else
    {
        // return;
        // cerr << ball1->current_x << "\n";
        // cerr << ball1->current_y << "\n";

        // cout << "enter "
        //      << "\n";

        int x1 = ball1.getx();
        int y1 = ball1.gety();
        // cout << x1 << " " << y1 << "\n";
        // // cerr << (x1 - 165) / 30 << (y1 - 165) / 30 << "\n";
        GridBox Current = getposition((x1 - 165) / 30, (y1 - 165) / 30);
        switch (key)
        {
        case 119:
            if (Current.walls.up == 1)
            {
                // ball1->current_y += 30;
                ball1.sety(y1 + 30);
            }
            break;
        case 115:
            if (Current.walls.down == 1)
            {
                // ball1.current_y -= 30;
                ball1.sety(y1 - 30);
            }
            break;
        case 97:
            if (Current.walls.left == 1)
            {
                // ball1.current_x -= 30;
                ball1.setx(x1 - 30);
            }
            break;
        case 100:
            if (Current.walls.right == 1)
            {
                // ball1.current_x += 30;
                ball1.setx(x1 + 30);
            }
            break;
        default:
            break;
        }
    }

    // int x1 = ball1.getx();
    // int y1 = ball1.gety();
    // cout << x1 << " " << y1 << "\n";
    ball1 = Ball(ball1.getx(), ball1.gety());
    task = Coin(task.current_x, task.current_y);

    display();
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
    // glutSpecialFunc(input_ticks);
    glutKeyboardFunc(input_enter);
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
