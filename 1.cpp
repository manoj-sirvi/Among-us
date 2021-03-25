#include <stdlib.h>
#include <stdio.h>
#include <time.h>

enum
{
    W = 36, // width of maze
    H = 25  // height of maze
};

enum
{
    North,
    East,
    South,
    West,
    NDir
};

char visited[H][W];
char horz[H][W - 1]; // horizontal E-W paths in the maze
char vert[H - 1][W]; // veritcal N-S paths in the maze

/*
 *      Fill dir with directions to unvisited cells, return count
 */
int adjacent(int dir[], int x, int y)
{
    int ndir = 0;

    if (y > 0 && visited[y - 1][x] == 0)
        dir[ndir++] = North;
    if (x < W - 1 && visited[y][x + 1] == 0)
        dir[ndir++] = East;
    if (y < H - 1 && visited[y + 1][x] == 0)
        dir[ndir++] = South;
    if (x > 0 && visited[y][x - 1] == 0)
        dir[ndir++] = West;

    return ndir;
}

/*
 *      Traverse cells depth first and create paths as you go
 */
void dfs(int x, int y)
{
    int dir[NDir];
    int ndir;

    visited[y][x] = 1;

    ndir = adjacent(dir, x, y);

    while (ndir)
    {
        int pick = rand() % ndir;

        switch (dir[pick])
        {
        case North:
            vert[y - 1][x] = 1;
            dfs(x, y - 1);
            break;
        case East:
            horz[y][x] = 1;
            dfs(x + 1, y);
            break;
        case South:
            vert[y][x] = 1;
            dfs(x, y + 1);
            break;
        case West:
            horz[y][x - 1] = 1;
            dfs(x - 1, y);
            break;
        }

        ndir = adjacent(dir, x, y);
    }
}

/*
 *      Print a map of the maze
 */
void map(void)
{
    int i, j;

    for (i = 0; i < W; i++)
    {
        putchar('_');
        putchar('_');
    }

    putchar('\n');

    for (j = 0; j < H; j++)
    {
        putchar('|');

        for (i = 0; i < W; i++)
        {
            putchar(j < H - 1 && vert[j][i] ? ' ' : '_');
            putchar(i < W - 1 && horz[j][i] ? '_' : '|');
        }

        putchar('\n');
    }
}

int main()
{
    srand(time(NULL));

    dfs(0, 0);
    map();

    return 0;
}