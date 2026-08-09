#pragma once
#include <array>
#include <vector>

class Game{
private:
    int FPS;
    int score{0};
public:
    struct Snake
    {
        std::array<int, 2> Food = {10, 10};
        std::vector<float> snakeBody;
        char snake_direction_state = 'd';
        void InitSnake(Game::Snake * snake);
    };

    Game(int FPS){
        this->FPS = FPS;
    }

    int Table[768];
    void snakeMovement(Game::Snake *snake, Game * game);

    int getFPS(){return this->FPS;}
    int& getScore(){return this-> score;}
    void setFPS(int score){ this->score = score; }
    void SnakeBodyUpdate(Game::Snake * snake, Game * game);
    void Reset(Game::Snake * snake, Game * game);
};