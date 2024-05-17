#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

// Window dimensions
const unsigned WINDOW_WIDTH = 1280;
const unsigned WINDOW_HEIGHT = 720;
const int SPEED = 10;
const unsigned PADDLE_SPEED = 30;
const float BALL_RADIUS = 30.0f;
const unsigned WINNING_SCORE = 5;
std::string winMessage;

// Define the game states
enum class GameState { Menu, Playing, GameOver };

//---------------------------------
// ballsound Buffer
sf::SoundBuffer ballSoundBuffer;
sf::Sound ballSound;



void moveBall(sf::CircleShape& ball, sf::Vector2f& position, sf::Vector2f& velocity)
{
    if (position.x < 0 || position.x > WINDOW_WIDTH - BALL_RADIUS * 2)
    {
        velocity.x *= -1;
        ballSound.play();

    }
    if (position.y < 0 || position.y > WINDOW_HEIGHT - BALL_RADIUS * 2)
    {
        velocity.y *= -1;
        ballSound.play();
    }
        
    position.x += velocity.x;
    position.y += velocity.y;

    ball.setPosition(position);
}


void resetGame(sf::CircleShape& ball, sf::Vector2f& ballPosition, sf::Vector2f& ballVelocity,
    sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle,
    int& leftScore, int& rightScore)
{
    // Reset ball position and velocity
    ballPosition = sf::Vector2f(300, 200);
    ball.setPosition(ballPosition);
    ballVelocity.x = SPEED;
    ballVelocity.y = SPEED;

    // Reset paddle positions
    leftPaddle.setPosition(0, 250);
    rightPaddle.setPosition(1260, 250);

    // Reset scores
    leftScore = 0;
    rightScore = 0;
}

int main()
{
    // Initialisation

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong");
    window.setFramerateLimit(60);


    // Define game state
    GameState gameState = GameState::Menu;

    // Load font
    sf::Font font;
    font.loadFromFile("font/DS-DIGI.ttf");

    // Menu text
    sf::Text menuText;
    menuText.setFont(font);
    menuText.setCharacterSize(50);
    menuText.setFillColor(sf::Color::Green);
    menuText.setString("Press Space to Start");
    menuText.setPosition((WINDOW_WIDTH - menuText.getLocalBounds().width) / 2, WINDOW_HEIGHT / 2);

    // Replay button text
    sf::Text replayText;
    replayText.setFont(font);
    replayText.setCharacterSize(50);
    replayText.setFillColor(sf::Color::Green);
    replayText.setString("Press Space to Replay");
    replayText.setPosition((WINDOW_WIDTH - replayText.getLocalBounds().width) / 2, WINDOW_HEIGHT / 2);


    // Game elements

    // Texture
    sf::Texture ballTexture;
    ballTexture.loadFromFile("image/ball.png");

    //Texture
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("image/background_pong.png");
    //Sprite

    sf::Sprite backgroundSprite(backgroundTexture);

    float backgroundX = (WINDOW_WIDTH - backgroundTexture.getSize().x) / 2.0f;
    float backgroundY = (WINDOW_HEIGHT - backgroundTexture.getSize().y) / 2.0f;
    backgroundSprite.setPosition(backgroundX, backgroundY);

    backgroundSprite.setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    backgroundSprite.setTextureRect(sf::IntRect(0, 0, backgroundTexture.getSize().x, backgroundTexture.getSize().y));
    backgroundSprite.setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    backgroundSprite.setTextureRect(sf::IntRect(0, 0, backgroundTexture.getSize().x, backgroundTexture.getSize().y));


    // Ball
    sf::CircleShape ball(BALL_RADIUS);
    ball.setTexture(&ballTexture);

    sf::Vector2f ballPosition(300, 200);
    ball.setPosition(ballPosition);

    sf::Vector2f ballVelocity;
    ballVelocity.x = SPEED;
    ballVelocity.y = SPEED;

    // Paddles
    sf::RectangleShape leftPaddle(sf::Vector2f(20, 100));
    leftPaddle.setFillColor(sf::Color::Red);
    leftPaddle.setPosition(0, 250);

    sf::RectangleShape rightPaddle(sf::Vector2f(20, 100));
    rightPaddle.setFillColor(sf::Color::Blue);
    rightPaddle.setPosition(1260, 250);

    // Scores
    int leftScore = 0;
    int rightScore = 0;



    // Text for score display
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setString("0 - 0");
    scoreText.setPosition((WINDOW_WIDTH - scoreText.getLocalBounds().width) / 2, 10);

    // Game Over text
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Green);
    gameOverText.setString("Game Over!");
    gameOverText.setPosition(WINDOW_WIDTH / 2 - 250, WINDOW_HEIGHT / 2 - 50);

    // Winning message
    sf::Text winText;
    winText.setFont(font);
    winText.setCharacterSize(50);

    winText.setString("");
    winText.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 + 50);


    // Audio
    //----------------------------------
    // BackgroundAudio Buffer
    sf::SoundBuffer backgroundAudioBuffer;
    backgroundAudioBuffer.loadFromFile("audio/background_audio.wav");
    // Chargement du background audio
    sf::Sound backgroundAudio;
    backgroundAudio.setBuffer(backgroundAudioBuffer);
    //----------------------------------

    // gameOverSound Buffer
    sf::SoundBuffer gameOverSoundBuffer;
    gameOverSoundBuffer.loadFromFile("audio/gameover_sound.wav");
    // Chargement du game over sound
    sf::Sound gameOverSound;
    gameOverSound.setBuffer(gameOverSoundBuffer);
    //----------------------------------
    // Lecture du background audio
    backgroundAudio.setLoop(true);

    //----------------------------------
    // game start sound
    sf::SoundBuffer gameStartSoundBuffer;
    gameStartSoundBuffer.loadFromFile("audio/start_sound.wav");
    // Chargement du game over sound
    sf::Sound gameStartSound;
    gameStartSound.setBuffer(gameStartSoundBuffer);
        
    //----------------------------------
    //Ball sound
    ballSoundBuffer.loadFromFile("audio/ball_sound.wav");

    ballSound.setBuffer(ballSoundBuffer);
    //Window

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Up)
                {
                    rightPaddle.move(0, PADDLE_SPEED * -1.0f);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    rightPaddle.move(0, PADDLE_SPEED);
                }
                if (event.key.code == sf::Keyboard::Z)
                {
                    leftPaddle.move(0, PADDLE_SPEED * -1.0f);
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    leftPaddle.move(0, PADDLE_SPEED);
                }
                if (event.key.code == sf::Keyboard::Space)
                {
                    if (gameState == GameState::Menu)
                    {
                        gameState = GameState::Playing;
                        gameStartSound.play();
                        sf::sleep(sf::seconds(2));
                        backgroundAudio.play();
                    }
                    else if (gameState == GameState::GameOver)
                    {
                        gameState = GameState::Playing;
                        resetGame(ball, ballPosition, ballVelocity, leftPaddle, rightPaddle, leftScore, rightScore);
                        gameOverSound.stop();
                        backgroundAudio.play();
                        

                    }
                }
                break;
            default:
                break;

            }
        }
            

            
            // Clear the window
            window.clear();

           
            if (gameState == GameState::Menu)
                {
                    // Display menu
                    window.draw(menuText);
                    window.display();
                }
            else if (gameState == GameState::Playing)
            {
                // Move 
                moveBall(ball, ballPosition, ballVelocity);
                if (ball.getPosition().x <= 0)
                {
                    rightScore++;
                    ball.setPosition(ballPosition);
                    ballVelocity.x = SPEED;
                    ballVelocity.y = SPEED;
                }
                else if (ball.getPosition().x >= WINDOW_WIDTH - BALL_RADIUS * 2)
                {
                    leftScore++;
                    ball.setPosition(ballPosition);
                    ballVelocity.x = SPEED * -1;
                    ballVelocity.y = SPEED;
                }

                // collision
                if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) || ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds()))
                {
                    ballVelocity.x *= -1;
                }

                // Update score text
                scoreText.setString(std::to_string(leftScore) + " - " + std::to_string(rightScore));
                scoreText.setPosition((WINDOW_WIDTH - scoreText.getLocalBounds().width) / 2, 10);
                window.draw(backgroundSprite);
                window.draw(ball);
                window.draw(leftPaddle);
                window.draw(rightPaddle);
                window.draw(scoreText);
                window.display();
                // Check for game over
                if (leftScore >= WINNING_SCORE || rightScore >= WINNING_SCORE)
                {// Determine the winning player
                    gameState = GameState::GameOver;
                    // Display game over message and winning player message
                    
                    if (leftScore >= WINNING_SCORE)
                    {
                        winMessage = "Red Player Wins!";
                        winText.setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        winMessage = "Blue Player Wins!";
                        winText.setFillColor(sf::Color::Blue);
                    }
                    backgroundAudio.stop();
                    gameOverSound.play();
                    window.clear();


                 // Display winning message
                    window.draw(gameOverText);
                    winText.setString(winMessage);
                    window.draw(winText);
                    window.display();
                    // Wait for a few seconds
                    sf::sleep(sf::seconds(5));


                }

            }
                
            if (gameState == GameState::GameOver)
                {
                    // Display game over message

                    
                    window.clear();
                    // Display replay button
                    window.draw(replayText);

                    window.display();
                }


        
    }  return 0;
}