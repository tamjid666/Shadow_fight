#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1366, 760), "Shadow ", sf::Style::None, settings);

    // Background
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    if (bgTexture.loadFromFile("asset/bgm/bg.jpg")) {
        std::cout << "BG Found\n";
        bgSprite.setTexture(bgTexture);
    }
    else {
        std::cout << "BG Not Found\n";
    }

    // Idle Animation
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    if (playerTexture.loadFromFile("asset/player/idle-RGBA.png")) {
        std::cout << "Player Found\n";
        playerSprite.setTexture(playerTexture);
        playerSprite.setTextureRect(sf::IntRect(0, 0, 413, 487));
        playerSprite.setScale(sf::Vector2f(0.75, 0.75));
        playerSprite.setPosition(sf::Vector2f(10, 310));
    }
    else {
        std::cout << "Player Not Found\n";
    }

    int idleMove = 0;
    const int totalFrames = 4;         // Total frames for idle animation
    const float frameDuration = 0.2f; // Duration per frame
    sf::Clock animationClock;

    // Running Animation
    sf::Texture runTexture;
    sf::Sprite runSprite;
    if (runTexture.loadFromFile("asset/player/run-Alpha.png")) {
        std::cout << "Run Animation Found\n";
        runSprite.setTexture(runTexture);
        runSprite.setTextureRect(sf::IntRect(0, 0, 408, 491.125)); // Set first frame
        runSprite.setScale(sf::Vector2f(0.75, 0.75));
        runSprite.setPosition(sf::Vector2f(10, 310));
    }
    else {
        std::cout << "Run Animation Not Found\n";
    }
    
    sf::Texture runRightTexture;
    sf::Sprite runRightSprite;
    if (runRightTexture.loadFromFile("asset/player/right-run-Alpha.png")) {
        std::cout << "Run Animation Found\n";
        runRightSprite.setTexture(runRightTexture);
        runRightSprite.setTextureRect(sf::IntRect(0, 0, 408, 491.125)); // Set first frame
        runRightSprite.setScale(sf::Vector2f(0.75, 0.75));
        runRightSprite.setPosition(sf::Vector2f(10, 310));
    }
    else {
        std::cout << "Run Animation Not Found\n";
    }

    int runMove = 0;
    const int totalRunFrame = 8;     
    const float runFrameDuration = .1f;
    sf::Clock animationRunClock;

    // Track player state
    bool isRunning = false;
    bool rightRunnig = false; 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
        }

        // Update sprite positions
        sf::Vector2f position = playerSprite.getPosition();
        isRunning = false; // Reset running state

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (position.x >= 1372)
                position.x = -308; 
            else
                position.x += 2; // Move right
            rightRunnig = true; 
            isRunning = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (position.x <= -308)
                position.x = 1372;
            else
                position.x -= 2; // Move left
            rightRunnig = false;
            isRunning = true;
        }

        playerSprite.setPosition(position);
        runSprite.setPosition(position);
        runRightSprite.setPosition(position);

        // Animate running
        if (isRunning) {
            if (rightRunnig) {
                if (animationRunClock.getElapsedTime().asSeconds() >= runFrameDuration) {
                    runMove = (runMove + 1) % totalRunFrame;
                    runRightSprite.setTextureRect(sf::IntRect(runMove * 491.125, 0, 408, 491.125)); // Update running frame
                    animationRunClock.restart();
                }
            }
            else{
                if (animationRunClock.getElapsedTime().asSeconds() >= runFrameDuration) {
                    runMove = (runMove + 1) % totalRunFrame;
                    runSprite.setTextureRect(sf::IntRect(runMove * 491.125, 0, 408, 491.125)); // Update running frame
                    animationRunClock.restart();
                }
            }
        }
        else {
            // Animate idle
            if (animationClock.getElapsedTime().asSeconds() >= frameDuration) {
                idleMove = (idleMove + 1) % totalFrames;
                playerSprite.setTextureRect(sf::IntRect(idleMove * 413, 0, 413, 487)); // Update idle frame
                animationClock.restart();
            }
        }

        // Draw appropriate sprite
        window.clear(sf::Color::White);
        window.draw(bgSprite);
        if (isRunning) {
            if (rightRunnig)
                window.draw(runRightSprite);
            else
                window.draw(runSprite);
        }
             // Draw running animation
        else
            window.draw(playerSprite); // Draw idle animation
        window.display();
    }

    return 0;
}
