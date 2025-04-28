#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>

#define WIDTH 50 
#define HEIGHT 25 
#define BIRD_X 5 
#define PIPE_GAP 8   
#define GRAVITY 1     
#define JUMP -3       
#define PIPE_COUNT 3 
#define FRAME_DELAY 75000
#define PIPE_SPACING 20   

typedef struct {
    int x, gapY; 
} Pipe;

int birdY, velocity;
Pipe pipes[PIPE_COUNT];
int score;
int gameOver; 
int paused = 0; 

void initGame() {
    birdY = HEIGHT / 2;
    velocity = 0;
    score = 0;
    gameOver = 0;

    for (int i = 0; i < PIPE_COUNT; i++) {
        pipes[i].x = WIDTH + (i * PIPE_SPACING);
        pipes[i].gapY = rand() % (HEIGHT - 12) + 4;
    }

    initscr();
    noecho();
    curs_set(0);
    timeout(0); 
    srand(time(0));

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_YELLOW, COLOR_BLACK); 
        init_pair(2, COLOR_GREEN, COLOR_BLACK);  
        init_pair(3, COLOR_RED, COLOR_BLACK);    
        init_pair(4, COLOR_CYAN, COLOR_BLACK);   
        init_pair(5, COLOR_BLACK, COLOR_BLACK);  
        init_pair(8, COLOR_BLUE, COLOR_BLACK);   
    }
}

void drawWelcomeScreen() {
    clear();
    attron(COLOR_PAIR(8));
    mvprintw(HEIGHT / 2 - 3, WIDTH / 2 - 10, "FLAPPY BIRD");
    mvprintw(HEIGHT / 2 - 1, WIDTH / 2 - 15, "Press Enter to Start");
    attroff(COLOR_PAIR(8));
    refresh();
}

void draw() {
    clear();

    attron(COLOR_PAIR(5));
    for (int i = 0; i < HEIGHT; i++) {
        mvhline(i, 0, ' ', WIDTH); 
    }
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(1));
    if (velocity < 0) { 
        mvprintw(birdY, BIRD_X, "o");
    } else { 
        mvprintw(birdY, BIRD_X, "*");
    }
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    for (int j = 0; j < PIPE_COUNT; j++) {
        if (pipes[j].x >= -4 && pipes[j].x < WIDTH) { 
            for (int i = 0; i < pipes[j].gapY; i++) {
                mvprintw(i, pipes[j].x, "|||||");
            }
            mvprintw(pipes[j].gapY, pipes[j].x, "=====");
            for (int i = pipes[j].gapY + PIPE_GAP + 1; i < HEIGHT; i++) {
                mvprintw(i, pipes[j].x, "|||||");
            }
            mvprintw(pipes[j].gapY + PIPE_GAP, pipes[j].x, "=====");
        }
    }
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(0, WIDTH / 2 - 5, "Score: %d", score);
    attroff(COLOR_PAIR(1));

    if (paused) {
        attron(COLOR_PAIR(4));
        mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "PAUSED");
        attroff(COLOR_PAIR(4));
    }

    refresh();
}

void update() {
    if (paused) return;

    velocity += GRAVITY;
    birdY += velocity;

    for (int j = 0; j < PIPE_COUNT; j++) {
        pipes[j].x--;
        if (pipes[j].x < -4) { 
            int maxX = -4;
            for (int k = 0; k < PIPE_COUNT; k++) {
                if (pipes[k].x > maxX) maxX = pipes[k].x;
            }
            pipes[j].x = maxX + PIPE_SPACING; 
            pipes[j].gapY = rand() % (HEIGHT - 12) + 4;
            score++;
        }
    }

    for (int j = 0; j < PIPE_COUNT; j++) {
        if (pipes[j].x >= BIRD_X - 4 && pipes[j].x <= BIRD_X) { 
            if (birdY <= pipes[j].gapY || birdY >= pipes[j].gapY + PIPE_GAP) {
                gameOver = 1;
            }
        }
    }

    if (birdY >= HEIGHT || birdY < 0) {
        gameOver = 1;
    }
}

void gameOverScreen() {
    clear();
    attron(COLOR_PAIR(3)); 
    mvprintw(HEIGHT / 2 - 3, WIDTH / 2 - 10, "GAME OVER!");
    mvprintw(HEIGHT / 2 - 1, WIDTH / 2 - 12, "Final Score: %d", score);
    mvprintw(HEIGHT / 2 + 1, WIDTH / 2 - 15, "Press R to Restart or Q to Quit");
    attroff(COLOR_PAIR(3));
    refresh();
}

int main() {
    char ch;

    initGame();
    drawWelcomeScreen();

    while (1) {
        drawWelcomeScreen();
        ch = getch();
        if (ch == '\n') {
            break;
        }
        usleep(100000); 
    }

    while (1) {
        initGame();

        while (!gameOver) {
            ch = getch();
            if (ch == ' ') {
                velocity = JUMP;
            } else if (ch == 'p' || ch == 'P') {
                paused = !paused;
            }

            update();
            draw();
            usleep(FRAME_DELAY);
        }

        gameOverScreen();

        while (1) {
            ch = getch();
            if (ch == 'r' || ch == 'R') {
                break;
            } else if (ch == 'q' || ch == 'Q') {
                endwin();
                return 0;
            }
        }
    }

    return 0;
}