#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700
#define GRAVITY 0.30f
#define JUMP -5.0f
#define BIRD_X 100
#define PIPE_GAP 180
#define PIPE_WIDTH 60
#define PIPE_COUNT 3
#define PIPE_SPEED 4
#define PIPE_MIN_GAP_Y 150
#define PIPE_MAX_GAP_Y 400

struct Pipe {
    float x;
    int gapY;
};

class FlappyBird {
private:
    float birdY;
    float velocity;
    int score;
    bool gameOver;
    bool gameStarted;
    bool paused;
    bool spacePressed;
    Pipe pipes[PIPE_COUNT];
    
    sf::RectangleShape birdBody;  
    sf::ConvexShape birdWing;    
    sf::ConvexShape birdBeak;     
    sf::CircleShape birdEye;      
    sf::CircleShape birdPupil;    
    int birdFrame;
    float birdAnimationTimer;

    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text welcomeText;
    sf::Text pauseText;

public:
    FlappyBird() : birdY(WINDOW_HEIGHT / 2), velocity(0), score(0),
                  gameOver(false), gameStarted(false), paused(false), spacePressed(false),
                  birdFrame(0), birdAnimationTimer(0.0f) {
        initGame();
    }

    void initGame() {
        srand(static_cast<unsigned>(time(0)));

        birdBody.setSize(sf::Vector2f(30, 20));  
        birdBody.setFillColor(sf::Color(255, 215, 0));  
        birdBody.setOutlineThickness(1);
        birdBody.setOutlineColor(sf::Color::Black);
        birdBody.setOrigin(15, 10);  

        birdWing.setPointCount(5);  
        birdWing.setPoint(0, sf::Vector2f(0, 0));
        birdWing.setPoint(1, sf::Vector2f(-15, -5)); 
        birdWing.setPoint(2, sf::Vector2f(-20, 10));  
        birdWing.setPoint(3, sf::Vector2f(-10, 15));  
        birdWing.setPoint(4, sf::Vector2f(0, 10));    
        birdWing.setFillColor(sf::Color(255, 165, 0));  

        birdBeak.setPointCount(3);  
        birdBeak.setPoint(0, sf::Vector2f(0, 0));
        birdBeak.setPoint(1, sf::Vector2f(12, -2));  
        birdBeak.setPoint(2, sf::Vector2f(12, 2));
        birdBeak.setFillColor(sf::Color(255, 69, 0)); 

        birdEye.setRadius(3); 
        birdEye.setFillColor(sf::Color::Black);
        birdPupil.setRadius(1); 
        birdPupil.setFillColor(sf::Color::White);

        resetPipes();

        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cerr << "Font loading failed!" << std::endl;
            exit(1);
        }

        setupText();
    }

    void setupText() {
        scoreText.setFont(font);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setCharacterSize(30);
        scoreText.setStyle(sf::Text::Bold);
        scoreText.setPosition(WINDOW_WIDTH / 2 - 70, 20);

        gameOverText.setFont(font);
        gameOverText.setFillColor(sf::Color(200, 0, 0));
        gameOverText.setCharacterSize(40);
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setString("GAME OVER!\nPress R to Restart or Q to Quit");
        gameOverText.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 50);

        welcomeText.setFont(font);
        welcomeText.setFillColor(sf::Color::Black);
        welcomeText.setCharacterSize(40);
        welcomeText.setStyle(sf::Text::Bold);
        welcomeText.setString("Flappy Bird\nPress Space to Start");
        welcomeText.setPosition(WINDOW_WIDTH / 2 - 170, WINDOW_HEIGHT / 2 - 50);

        pauseText.setFont(font);
        pauseText.setFillColor(sf::Color::Black);
        pauseText.setCharacterSize(40);
        pauseText.setStyle(sf::Text::Bold);
        pauseText.setString("PAUSED");
        pauseText.setPosition(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2);
    }

    void update(float deltaTime) {
        if (gameOver || paused || !gameStarted) return;

        velocity += GRAVITY * deltaTime * 60.0f;
        birdY += velocity * deltaTime * 60.0f;

        birdAnimationTimer += deltaTime * 12.0f;
        if (birdAnimationTimer >= 1.0f) {
            birdAnimationTimer = 0.0f;
            birdFrame = !birdFrame;
        }

        for (int i = 0; i < PIPE_COUNT; i++) {
            pipes[i].x -= PIPE_SPEED * deltaTime * 60.0f;
            if (pipes[i].x + PIPE_WIDTH < 0) {
                pipes[i].x = WINDOW_WIDTH;
                pipes[i].gapY = rand() % (PIPE_MAX_GAP_Y - PIPE_MIN_GAP_Y + 1) + PIPE_MIN_GAP_Y;
                if (gameStarted) score++;
            }
        }

        checkCollisions();
    }

    void checkCollisions() {
        float groundHeight = WINDOW_HEIGHT - 100;
        if (birdY + 10 >= groundHeight) {  
            birdY = groundHeight - 10;
            velocity = 0;
            gameOver = true;
        }
        if (birdY - 10 < 0) {
            birdY = 10;
            velocity = 0;
        }

        for (int i = 0; i < PIPE_COUNT; i++) {
            if (BIRD_X + 15 >= pipes[i].x && BIRD_X - 15 <= pipes[i].x + PIPE_WIDTH && 
                (birdY - 10 < pipes[i].gapY || birdY + 10 > pipes[i].gapY + PIPE_GAP)) {
                gameOver = true;
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.clear();

        sf::VertexArray gradient(sf::Quads, 4);
        gradient[0].position = sf::Vector2f(0, 0);
        gradient[1].position = sf::Vector2f(WINDOW_WIDTH, 0);
        gradient[2].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
        gradient[3].position = sf::Vector2f(0, WINDOW_HEIGHT);
        gradient[0].color = sf::Color(70, 130, 180);
        gradient[1].color = sf::Color(70, 130, 180);
        gradient[2].color = sf::Color(135, 206, 235);
        gradient[3].color = sf::Color(135, 206, 235);
        window.draw(gradient);

        drawClouds(window);

        sf::RectangleShape ground(sf::Vector2f(WINDOW_WIDTH, 100));
        ground.setPosition(0, WINDOW_HEIGHT - 100);
        ground.setFillColor(sf::Color(50, 205, 50));
        window.draw(ground);
        sf::RectangleShape dirt(sf::Vector2f(WINDOW_WIDTH, 20));
        dirt.setPosition(0, WINDOW_HEIGHT - 100);
        dirt.setFillColor(sf::Color(139, 69, 19));
        window.draw(dirt);

        for (int i = 0; i < PIPE_COUNT; i++) {
            float groundLevel = WINDOW_HEIGHT - 100;
            sf::RectangleShape bottomPipe(sf::Vector2f(PIPE_WIDTH, groundLevel - (pipes[i].gapY + PIPE_GAP)));
            bottomPipe.setPosition(pipes[i].x, pipes[i].gapY + PIPE_GAP);
            bottomPipe.setFillColor(sf::Color(34, 139, 34));
            bottomPipe.setOutlineThickness(3);
            bottomPipe.setOutlineColor(sf::Color(0, 100, 0));
            window.draw(bottomPipe);

            sf::RectangleShape topPipe(sf::Vector2f(PIPE_WIDTH, pipes[i].gapY));
            topPipe.setPosition(pipes[i].x, 0);
            topPipe.setFillColor(sf::Color(34, 139, 34));
            topPipe.setOutlineThickness(3);
            topPipe.setOutlineColor(sf::Color(0, 100, 0));
            window.draw(topPipe);
        }

        float birdAngle = velocity * 2.0f;
        birdBody.setPosition(BIRD_X, birdY);
        birdBody.setRotation(birdAngle);
        birdWing.setPosition(BIRD_X + 10, birdY + (birdFrame ? -5 : 5));  
        birdWing.setRotation(birdAngle);
        birdBeak.setPosition(BIRD_X + 15, birdY); 
        birdBeak.setRotation(birdAngle);
        birdEye.setPosition(BIRD_X + 10, birdY - 5); 
        birdPupil.setPosition(BIRD_X + 11, birdY - 5);  
        window.draw(birdBody);
        window.draw(birdWing);
        window.draw(birdBeak);
        window.draw(birdEye);
        window.draw(birdPupil);

        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
        if (gameOver) window.draw(gameOverText);
        else if (!gameStarted) window.draw(welcomeText);
        else if (paused) window.draw(pauseText);

        window.display();
    }

    void drawClouds(sf::RenderWindow& window) {
        sf::CircleShape cloud1(60);
        cloud1.setScale(1.6, 0.9);
        cloud1.setFillColor(sf::Color(255, 255, 255, 220));
        cloud1.setPosition(250, 120);
        window.draw(cloud1);

        sf::CircleShape cloud2(70);
        cloud2.setScale(1.4, 0.8);
        cloud2.setFillColor(sf::Color(255, 255, 255, 220));
        cloud2.setPosition(600, 170);
        window.draw(cloud2);
    }

    void handleInput(sf::Event& event, sf::RenderWindow& window) {
        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space && !spacePressed) {
                spacePressed = true;
                if (!gameStarted) gameStarted = true;
                velocity = JUMP;
            }
            if (event.key.code == sf::Keyboard::P) paused = !paused;
            if (gameOver) {
                if (event.key.code == sf::Keyboard::R) reset();
                if (event.key.code == sf::Keyboard::Q) window.close();
            }
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
            spacePressed = false;
        }
    }

    void reset() {
        birdY = WINDOW_HEIGHT / 2;
        velocity = 0;
        score = 0;
        gameOver = false;
        birdFrame = 0;
        birdAnimationTimer = 0.0f;
        resetPipes();
        gameStarted = false;
    }

private:
    void resetPipes() {
        for (int i = 0; i < PIPE_COUNT; i++) {
            pipes[i].x = WINDOW_WIDTH + (i * (WINDOW_WIDTH / PIPE_COUNT));
            pipes[i].gapY = rand() % (PIPE_MAX_GAP_Y - PIPE_MIN_GAP_Y + 1) + PIPE_MIN_GAP_Y;
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird", sf::Style::Close);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    FlappyBird game;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            game.handleInput(event, window);
        }

        float deltaTime = clock.restart().asSeconds();
        game.update(deltaTime);
        game.draw(window);
    }
    return 0;
}