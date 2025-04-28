#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

const int WIDTH = 800, HEIGHT = 600; 

enum GameState { START, PLAYING, GAME_OVER };
GameState state = START;

struct Pipe {
    float x;
    float gapCenter;
    bool scored;
};

float birdX = 100.0f, birdY = HEIGHT / 2.0f, birdVelocity = 0.0f;
float gravity = -900.0f, flapStrength = 300.0f;
float pipeGap = 200.0f, pipeWidth = 80.0f;
float pipeSpeed = 400.0f, pipeSpacing = 300.0f; 
int score = 0;
std::vector<Pipe> pipes;
bool flapAnimation = false;
float animationTimer = 0.0f;

void drawText(float x, float y, std::string text, float r, float g, float b) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawRect(float x, float y, float w, float h, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void drawBackground() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.5f, 0.9f); 
    glVertex2f(0, HEIGHT);
    glVertex2f(WIDTH, HEIGHT);
    glColor3f(0.6f, 0.8f, 1.0f); 
    glVertex2f(WIDTH, 0);
    glVertex2f(0, 0);
    glEnd();
    drawRect(0, 0, WIDTH, 80, 0.1f, 0.5f, 0.1f); 
    drawRect(0, 70, WIDTH, 10, 0.2f, 0.6f, 0.2f); 
}

void drawPipe(float x, float gapBottom, float gapTop) {
    drawRect(x, 0, pipeWidth, gapBottom, 0.0f, 0.7f, 0.0f);
    drawRect(x - 5, gapBottom - 25, pipeWidth + 10, 25, 0.0f, 0.5f, 0.0f); 
    drawRect(x + 5, 0, pipeWidth - 10, gapBottom, 0.0f, 0.9f, 0.0f); 
    drawRect(x, gapTop, pipeWidth, HEIGHT - gapTop, 0.0f, 0.7f, 0.0f); 
    drawRect(x - 5, gapTop, pipeWidth + 10, 25, 0.0f, 0.5f, 0.0f); 
    drawRect(x + 5, gapTop, pipeWidth - 10, HEIGHT - gapTop, 0.0f, 0.9f, 0.0f); 
}

void drawBird(float x, float y) {
    glColor3f(1.0f, 0.9f, 0.0f); 
    glBegin(GL_QUADS);
    glVertex2f(x + 5, y - 15);
    glVertex2f(x + 35, y - 15);
    glVertex2f(x + 35, y + 10);
    glVertex2f(x + 5, y + 10);
    glEnd();

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_TRIANGLES);
    if (flapAnimation && animationTimer < 0.2f) {
        glVertex2f(x + 10, y - 5);
        glVertex2f(x + 30, y + 20); 
        glVertex2f(x + 30, y - 5);
    } else {
        glVertex2f(x + 10, y - 5);
        glVertex2f(x + 30, y + 5); 
        glVertex2f(x + 30, y - 20);
    }
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f); 
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 35, y);
    glVertex2f(x + 45, y + 3);
    glVertex2f(x + 45, y - 3);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); 
    glBegin(GL_QUADS);
    glVertex2f(x + 25, y + 3);
    glVertex2f(x + 30, y + 3);
    glVertex2f(x + 30, y + 8);
    glVertex2f(x + 25, y + 8);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f); 
    glBegin(GL_QUADS);
    glVertex2f(x + 27, y + 4);
    glVertex2f(x + 29, y + 4);
    glVertex2f(x + 29, y + 7);
    glVertex2f(x + 27, y + 7);
    glEnd();
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if (state == START) {
            state = PLAYING;
            pipes.clear();
            pipes.push_back({WIDTH + pipeSpacing, HEIGHT / 2.0f, false}); 
        } else if (state == PLAYING) {
            birdVelocity = flapStrength;
            flapAnimation = true;
            animationTimer = 0.0f;
        }
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
        flapAnimation = false;
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS && state == GAME_OVER) {
        birdY = HEIGHT / 2.0f;
        birdVelocity = 0.0f;
        pipes.clear();
        score = 0;
        state = START;
    }
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, char** argv) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Flappy Bird - OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glutInit(&argc, argv);

    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    double lastTime = glfwGetTime();
    float lastPipeTime = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        lastPipeTime += deltaTime;

        if (flapAnimation) {
            animationTimer += deltaTime;
            if (animationTimer >= 0.2f) flapAnimation = false;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        drawBackground();

        switch (state) {
            case START:
                drawBird(birdX, birdY);
                drawText(WIDTH / 2 - 100, HEIGHT / 2 + 50, "Press SPACE to Start", 1.0f, 1.0f, 1.0f);
                break;

            case PLAYING:
                birdVelocity += gravity * deltaTime;
                birdY += birdVelocity * deltaTime;
                if (birdY < 80 || birdY > HEIGHT) state = GAME_OVER;

                if (lastPipeTime >= pipeSpacing / pipeSpeed) {
                    float minGapCenter = pipeGap / 2 + 80; 
                    float maxGapCenter = HEIGHT - pipeGap / 2; 
                    float newGapCenter = minGapCenter + static_cast<float>(rand() % static_cast<int>(maxGapCenter - minGapCenter));
                    float newX = pipes.empty() ? WIDTH + pipeSpacing : pipes.back().x + pipeSpacing;
                    pipes.push_back({newX, newGapCenter, false});
                    lastPipeTime = 0.0f;
                }

                for (auto it = pipes.begin(); it != pipes.end();) {
                    it->x -= pipeSpeed * deltaTime;

                    float gapBottom = it->gapCenter - pipeGap / 2;
                    float gapTop = it->gapCenter + pipeGap / 2;

                    if ((birdX + 35 > it->x && birdX < it->x + pipeWidth) &&
                        (birdY - 10 < gapBottom || birdY + 10 > gapTop)) {
                        state = GAME_OVER;
                    }

                    if (it->x + pipeWidth < birdX && !it->scored) {
                        score++;
                        it->scored = true;
                    }

                    if (it->x < -pipeWidth) {
                        it = pipes.erase(it);
                    } else {
                        drawPipe(it->x, gapBottom, gapTop);
                        ++it;
                    }
                }

                drawBird(birdX, birdY);
                drawText(10, HEIGHT - 30, "Score: " + std::to_string(score), 1.0f, 1.0f, 1.0f);
                break;

            case GAME_OVER:
                drawBird(birdX, birdY);
                for (const auto& pipe : pipes) {
                    drawPipe(pipe.x, pipe.gapCenter - pipeGap / 2, pipe.gapCenter + pipeGap / 2);
                }
                drawText(WIDTH / 2 - 100, HEIGHT / 2 + 50, "Game Over! Score: " + std::to_string(score), 1.0f, 0.0f, 0.0f);
                drawText(WIDTH / 2 - 100, HEIGHT / 2, "Press R to Restart or Q to Quit", 1.0f, 1.0f, 1.0f);
                break;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}