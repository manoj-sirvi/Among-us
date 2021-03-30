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
#include <GL/freeglut.h>

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;
int width = 15, height = 15;
GridBox *grid;
Ball ball1;
Coin *button = NULL;
int previous = 0;
int manoj = -1;
Obstacles *obs;
int time1 = 0;
int Score = 0;
bool f[10] = {0};
vector<int> graph[100];
GLuint id;
GLuint texture;
Ball Imposter;

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

Timer t60(1.0 / 30);

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

void tick_elements()
{
    // ball1.tick();
    // camera_rotation_angle += 1;
}

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
    for (int i = 0; i < 70; i++)
    {
        int random = rand() % 100;
        if (random % 10 == 0 || random % 10 == 9 || random / 10 == 0 || random / 10 == 9)
            continue;
        int dest = rand() % 4;
        int x = random % 10;
        int y = random / 10;
        // cout << y << " " << x << "\n";
        switch (dest)
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
        default:
            break;
        }
    }
    int exit[4];
    exit[2] = abs(9 - x) + abs(9 - y);
    exit[1] = abs(9 - x) + abs(0 - y);

    exit[3] = abs(0 - x) + abs(9 - y);

    exit[0] = abs(0 - x) + abs(0 - y);
    int index = distance(exit, max_element(exit, exit + 4));
    cout << index << "\n";
    switch (index)
    {
    case 0:
        getposition(0, 0).walls.left = 1;
        break;
    case 1:
        getposition(9, 0).walls.down = 1;
        break;
    case 2:
        getposition(9, 9).walls.right = 1;
        break;
    case 3:
        getposition(0, 9).walls.up = 1;
        break;

    default:
        break;
    }

    // cout << &(ball1->current_x) << " " << ball1->current_y << "\n";

    // return {ball1->current_x, ball1->current_y};
}
void Get_maze()
{
    // cout << "entering"
    //      << "\n";

    for (int i = 0; i < 100; i++)
    {
        // cout << grid[i].filled << " ";
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
    // cout << "\n";
}
void Generate_Graph()
{
    // cout << grid[0].walls.up << " " << grid[0].walls.right << " " << grid[0].walls.left << " " << grid[0].walls.down << " "
    //      << "\n";
    for (int i = 0; i < 100; i++)
    {

        if ((i % 10) != 0 && grid[i].walls.left == true)
            graph[i].push_back(i - 1);
        if (((i + 1) % 10) != 0 && grid[i].walls.right == true)
            graph[i].push_back(i + 1);
        if (i - 10 >= 0 && grid[i].walls.down == true)
            graph[i].push_back(i - 10);
        if (i + 10 < 100 && grid[i].walls.up == true)
            graph[i].push_back(i + 10);
    }
    // for (int i = 0; i < 100; i++)
    // {
    //     cout << i << " ";
    //     cout << grid[i].walls.up << " " << grid[i].walls.right << " " << grid[i].walls.left << " " << grid[i].walls.down << " ";

    //     for (int j = 0; j < graph[i].size(); j++)
    //         cout << graph[i][j] << " ";
    //     cout << "\n";
    // }
}
int bfs(int start, int destination)
{
    bool vis[101] = {0};
    queue<int> qu;
    // vector<pair<int, int>> checker;
    int dis[100];
    for (int i = 0; i < 100; i++)
        dis[i] = 10000;
    int parent[100];
    // vis[start] = 1;
    for (int i = 0; i < graph[start].size(); i++)
    {
        // cout << "enter"
        //      << "\n";
        qu.push(graph[start][i]);
        vis[graph[start][i]] = 1;
        dis[graph[start][i]] = 1;
        parent[graph[start][i]] = graph[start][i];
        // checker.push_back({graph[start][i], 1});
    }
    // qu.push(start);
    while (!qu.empty())
    {
        int x = qu.front();
        qu.pop();
        // cout << x << " " << parent[x] << "\n";

        // vis[x] = 1;
        for (int i = 0; i < graph[x].size(); i++)
        {
            if (!vis[graph[x][i]])
            {
                qu.push(graph[x][i]);
                vis[graph[x][i]] = 1;
                if (dis[graph[x][i]] > dis[x] + 1)
                {
                    dis[graph[x][i]] = dis[x] + 1;
                    parent[graph[x][i]] = parent[x];
                }
            }
        }
    }
    // cout << parent[destination] << "\n";
    return parent[destination];
}

GLuint loadTexture(char const *filename)
{

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
void render_string(string str, int x, int y)
{
    glColor4f(1.0f, 1.0f, 1.0f, 0.0f); //RGBA values of text color
    glRasterPos2i(x, y);
    // string str = "Score: " + to_string(Score);                                                            //Top left corner of text
    const unsigned char *t = reinterpret_cast<const unsigned char *>((const unsigned char *)str.c_str()); // Since 2nd argument of glutBitmapString must be const unsigned char
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, t);
}

void draw_texture()
{
    char const *name = "../source/1.bmp";
    id = loadTexture(name);
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
    // free(texture)
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}
void render_loop()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(10);
    glLineWidth(2.5);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(10.0, 10.0, 0.0);
    glVertex3f(200.0, 200.0, 0.0);
    glEnd();
}
void HUD()
{
    string str = "Score: " + to_string(Score);
    render_string(str, 150, 540);
}
void display()
{

    //

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // cout << "drawing"
    //      << " "
    //      << "\n";
    // Get_maze();
    // draw_texture();
    double x = 1;
    glBegin(GL_QUADS);
    glColor3f(0, 0.4, 0.2);
    glVertex2f(450, 450);
    glVertex2f(150, 450);
    glVertex2f(150, 150);
    glVertex2f(450, 150);
    glEnd();
    // glLoadIdentity();
    // GLfloat lineWidthRange[2] = {0.0f, 1.0f};
    // glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
    glLineWidth(5);
    glBegin(GL_QUADS);
    glColor3f(0, 0.0, 0.0);
    glVertex2f(150, 550);
    glVertex2f(150, 500);
    glVertex2f(450, 500);
    glVertex2f(450, 550);
    glEnd();
    glBegin(GL_LINES);
    // glColor3f(1, 1, 1);
    for (x = 5; x < width + 1; x++)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(x * 30, 150, 0);
        glVertex3f(x * 30, 450, 0);
    }
    for (x = 5; x < height + 1; x++)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(150.0, x * 30, 0);
        glVertex3f(450, x * 30, 0);
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
    // obs = Obstacles(165, 165, -1);
    // obs.draw();
    // cout << "hello"
    //      << "\n";
    for (int i = 0; i < 4; i++)
    {
        obs[i].draw();
    }
    // ball1 = Ball(165, 165, 1, 1, 0);
    // cout << "hello1"
    //      << "\n";
    ball1.draw();
    // cout << "hello2"
    //      << "\n";
    Imposter.draw();
    // cout << "hello3"
    //      << "\n";
    Get_maze();
    // cout << "hello4"
    //      << "\n";

    if (button != NULL)
    {
        // cout << "enter"
        //      << "\n";
        // cout << button->current_x << " " << button->current_y << "\n";
        button->draw();
    }
    // Get_maze();
    // string str = "Score: " + to_string(Score);
    // render_string(str, 150, 540);
    HUD();

    // Gener_field();

    // glFlush();

    // update_maze();
    // glBegin(GL_LINES);
    // glEnd();

    // glFlush();
    // glutPostRedisplay();
    //     }
    //       counter+=1;
    // counter%=100;
    // }
}

void Imposter_movement()
{
    int destination = 10 * ((ball1.gety() - 165) / 30) + ((ball1.getx() - 165) / 30);
    int start = 10 * ((Imposter.gety() - 165) / 30) + ((Imposter.getx() - 165) / 30);
    cout << "special " << start << " " << destination << "\n";
    cerr << bfs(start, destination) << "\n";
    int move = bfs(start, destination);
    cerr << move << "\n";
    int x = move % 10;
    int y = move / 10;
    Imposter.setx((x * 30 + 165));
    Imposter.sety((y * 30 + 165));
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
void timer()
{
    time1 += 1;
    string str = "manoj: " + to_string(time1);
    render_string(str, 250, 500);
    ball1.draw();
    glFlush();
}
void player_obstaclecollision()
{
    for (int i = 0; i < 4; i++)
    {
        if (ball1.getx() == obs[i].current_x && ball1.gety() == obs[i].current_y)
        {
            Score += obs[i].score;
            obs[i].score = 0;
            obs[i].type = 0;
        }
    }
}
void Player_buttoncollision()
{
    // cout << button->current_x << " " << button->current_y << "\n";

    if (ball1.getx() == button->current_x && ball1.gety() == button->current_y)
    {
        getposition((button->current_x - 165) / 30, (button->current_y - 165) / 30).filled = true;
        int counter = 0;
        for (int i = 0; i < 10; i++)
        {
            if (counter < 2)
            {
                int x = rand() % 10;
                int y = rand() % 10;
                if (getposition(x, y).filled == false)
                {
                    getposition(x, y).filled = true;
                    obs[counter].current_x = x * 30 + 165;
                    obs[counter].current_y = y * 30 + 165;
                    obs[counter].type = 1;
                    obs[counter].score = 10;
                    counter++;
                }
            }
            else
            {
                if (counter < 4)
                {
                    int x = rand() % 10;
                    int y = rand() % 10;
                    if (getposition(x, y).filled == false)
                    {
                        getposition(x, y).filled = true;

                        obs[counter].current_x = x * 30 + 165;
                        obs[counter].current_y = y * 30 + 165;
                        obs[counter].type = -1;
                        obs[counter].score = -8;
                        counter++;
                    }
                }
                else
                    break;
            }
        }
        button = NULL;
        // cout << "fgfjgjh"
        //      << "\n";
    }
    // cout << "out"
    //      << "\n";
}
void input_enter(GLFWwindow *window)
{
    cout << "dewkfhj"
         << "\n";
    // cout << (int)key << "\n";
    int key = glfwGetKey(window, GLFW_KEY_ENTER);
    // if (f[0] == 0)
    // {
    if (f[0] == 0)
    {
        if (key == 1)
        {
            // cout << "pressed enter"
            //      << "\n";
            int x = rand() % 10;
            int y = rand() % 10;
            int x1 = rand() % 10;
            int y1 = rand() % 10;
            cout << "bfs " << bfs(99, 0) << "\n";
            // Ball special(x * 30 + 165, y * 30 + 165);
            // ball1 = &special;
            // ball1->setx(x * 30 + 165);
            // ball1->sety(y * 30 + 165);
            // x = 9, y = 9;
            // cout << "fgh"
            //  << "\n";
            x = 0, y = 0;
            getposition(x, y).filled = true;
            // cout << y * 10 + x << "\n";
            ball1 = Ball(x * 30 + 165, y * 30 + 165, 1, 1, 0);
            if (x1 == x && y1 == y)
            {
                x1 = (x + 1) % 10;
                y1 = (y + 5) % 10;
            }

            getposition(x1, y1).filled = true;
            // // cout << y1 * 10 + x1 << "\n";
            static Coin finder(x1 * 30 + 165, y1 * 30 + 165);
            button = &(finder);

            // ball1.draw();

            // cout << "x " << x << " " << y << "\n";
            // dfs(x, y);
            Gener_field(x, y);
            Generate_Graph();
            // cout << "efr"
            //      << "\n";
            f[0] = 1;
            for (int i = 0; i < 5; i++)
            {
                int x = rand() % 10;
                int y = rand() % 10;
                x = 9, y = 9;
                if (getposition(x, y).filled == false)
                {
                    // cout << "enter"
                    //      << "\n";
                    // cout << x << " " << y << " " << ball1.getx() << " " << ball1.gety() << "\n";
                    Imposter = Ball(x * 30 + 165, y * 30 + 165, 0.6, 0.8, 1);
                    getposition(x, y).filled = true;
                    // Imposter.draw();
                    break;
                }
            }
            // cout << ball1.getx() << " " << ball1.gety() << "\n";
            // cout << bfs(2, 99) << "\n";

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
    }
    // }
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int x1 = ball1.getx();
    int y1 = ball1.gety();
    getposition((x1 - 165) / 30, (y1 - 165) / 30).filled = 0;
    GridBox Current = getposition((x1 - 165) / 30, (y1 - 165) / 30);
    if (left)
    {
        if (Current.walls.left)
            ball1.setx(ball1.getx() - 30);
        // f[1] = 1;
    }
    if (right)
    {
        if (Current.walls.right == 1)
            ball1.setx(ball1.getx() + 30);
        // f[2] = 1;
    }
    if (up)
    {
        if (Current.walls.up == 1)

            ball1.sety(ball1.gety() + 30);
        // f[3] = 1;
    }
    if (down)
    {
        if (Current.walls.down == 1)
            ball1.sety(ball1.gety() - 30);
        // f[4] = 1;
    }

    // else
    // {
    //     // return;
    //     // cerr << ball1->current_x << "\n";
    //     // cerr << ball1->current_y << "\n";

    //     // cout << "enter "
    //     //      << "\n";

    //     int x1 = ball1.getx();
    //     int y1 = ball1.gety();
    //     getposition((x1 - 165) / 30, (y1 - 165) / 30).filled = 0;
    //     // cout << x1 << " " << y1 << "\n";
    //     // // cerr << (x1 - 165) / 30 << (y1 - 165) / 30 << "\n";
    //     GridBox Current = getposition((x1 - 165) / 30, (y1 - 165) / 30);
    //     // Current.filled = false;
    //     switch (key)
    //     {
    //     case 119:
    //         if (Current.walls.up == 1)
    //         {
    //             // ball1->current_y += 30;
    //             ball1.sety(y1 + 30);
    //             // Current.filled = false;
    //         }
    //         break;
    //     case 115:
    //         if (Current.walls.down == 1)
    //         {
    //             // ball1.current_y -= 30;
    //             ball1.sety(y1 - 30);
    //             // Current.filled = false;
    //         }
    //         break;
    //     case 97:
    //         if (Current.walls.left == 1)
    //         {
    //             // ball1.current_x -= 30;
    //             ball1.setx(x1 - 30);
    //             // Current.filled = false;
    //         }
    //         break;
    //     case 100:
    //         if (Current.walls.right == 1)
    //         {
    //             // ball1.current_x += 30;
    //             ball1.setx(x1 + 30);
    //             // Current.filled = false;
    //         }
    //         break;
    //     default:
    //         break;
    //     }
    //     // cout << Current.filled << "\n";
    //     // cout << 10 * ((y1 - 165) / 30) + (x1 - 165) / 30 << "\n";
    // }

    // // int x1 = ball1.getx();
    // // int y1 = ball1.gety();
    // // cout << x1 << " " << y1 << "\n";
    if (button != NULL)
    {
        //     //  getposition((button->current_x - 165) / 30, (button->current_y - 165) / 30).filled = true;

        //     static Coin finder(button->current_x, button->current_y);
        //     button = &(finder);
        //     // getposition((button->current_x - 165) / 30, (button->current_y - 165) / 30).filled = true;
        Player_buttoncollision();
    }
    // ball1 = Ball(ball1.getx(), ball1.gety(), 1, 1, 0);
    getposition((ball1.getx() - 165) / 30, (ball1.gety() - 165) / 30).filled = true;
    player_obstaclecollision();
    // cout << "fer"
    //      << "\n";
    // // cout << ((ball1.gety() - 165) / 30) * 10 + (ball1.getx() - 165) / 30 << "\n";

    // display();
}

int main(int argc, char **argv)
{
    srand(time(0));
    //     // int width = 600;
    //     // int height = 600;

    //     // window = initGLFW(1000, 1000);
    grid = new GridBox[100];
    //     GLFWwindow *window;
    //     if (!glfwInit())
    //     {
    //         fprintf(stderr, "Failed to initialize GLFW\n");
    //         exit(EXIT_FAILURE);
    //     }
    //     window = glfwCreateWindow(1000, 1000, "LearnOpenGL", NULL, NULL);
    obs = new Obstacles[4];
    glutInit(&argc, argv);
    //     // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //     // glutInitWindowSize(1000, 1000);
    //     // glutInitWindowPosition(100, 100);
    //     // glutCreateWindow("Among-Us");
    //     // init();
    //     // initGL(window, width, height);
    //     // glutInit(&argc, argv);
    //     // glutDisplayFunc(display);
    //     // // glutSpecialFunc(input_ticks);
    //     // glutIdleFunc(timer);
    //     // glutKeyboardFunc(input_enter);
    //     // glutMainLoop();

    //     /* Draw in loop */
    //     while (!glfwWindowShouldClose(window))
    //     {
    //         // Process timers

    //         if (t60.processTick())
    //         {
    //             // 60 fps
    //             // OpenGL Draw commands
    //             // draw();
    //             // glutDisplayFunc(display);
    //             display();
    //             // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //             // use the loaded shader program
    //             // Don't change unless you know what you are doing
    //             // glUseProgram(programID);

    //             // Swap Frame Buffer in double buffering
    //             glfwSwapBuffers(window);

    //             tick_elements();
    //             // tick_input(window);
    //             // glutKeyboardFunc(input_enter);
    //         }

    //         // Poll for Keyboard and mouse events
    //         glfwPollEvents();
    //     }

    //     quit(window);
    // }
    GLFWwindow *window;

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(1000, 1000, "Among-Us", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // set up view
    // glViewport(0, 0, 1000, 1000);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, 0.0, 1.0); // this creates a canvas you can do 2D drawing on

    // Main loop
    int counter = 0;
    int counter1 = 0;
    // static(GL_STATIC_DRAW);
    draw_texture();
    while (!glfwWindowShouldClose(window))
    {
        // Draw gears
        // render_loop();
        // draw_texture();
        if (t60.processTick())
        {
            display();

            // Swap buffers

            counter += 1;
            counter %= 6;
            counter1 += 1;
            counter1 %= 15;
            if (counter == 0)
            {
                input_enter(window);
                if (f[0] && counter1 == 0)
                    Imposter_movement();
            }
            glfwSwapBuffers(window);
        }
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    // Exit program
    exit(EXIT_SUCCESS);
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
