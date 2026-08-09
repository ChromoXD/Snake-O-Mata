#include "Game_Class.hpp"
#include <raylib.h>

void Game::snakeMovement(Game::Snake *snake, Game * game)
{
    for (size_t i = snake->snakeBody.size() / 2 - 1; i > 0; i--)
    {
        snake->snakeBody[i * 2] = snake->snakeBody[i * 2 - 2];
        snake->snakeBody[i * 2 + 1] = snake->snakeBody[i * 2 - 1];
    }

    
    switch (snake->snake_direction_state)
    {   
        case 'w': snake->snakeBody[1] += 1.0f;
            break;
        case 'a': snake->snakeBody[0] -= 1.0f;
            break;
        case 's': snake->snakeBody[1] -= 1.0f;
            break;
        case 'd': snake->snakeBody[0] += 1.0f;
            break;

        default:
            break;
    }

    // if ((int)snake->snakeBody[0] > 31) snake->snakeBody[0] = 0;
    // if ((int)snake->snakeBody[0] < 0)  snake->snakeBody[0] = 31;
    // if ((int)snake->snakeBody[1] < 0)  snake->snakeBody[1] = 23;
    // if ((int)snake->snakeBody[1] > 23) snake->snakeBody[1] = 0;

    if ((int)snake->snakeBody[0] > 31) game->Reset(snake, game);
    if ((int)snake->snakeBody[0] < 0)  game->Reset(snake, game);
    if ((int)snake->snakeBody[1] < 0)  game->Reset(snake, game);
    if ((int)snake->snakeBody[1] > 23) game->Reset(snake, game);

    
    for (size_t i = 1; i < snake->snakeBody.size()/2; i++)
    {
        if (snake->snakeBody[0] == snake->snakeBody[i*2] && snake->snakeBody[1] == snake->snakeBody[i*2 + 1])
        {
            game->Reset(snake, game);
        }
    }
    
}

void Game::Snake::InitSnake(Game::Snake * snake){

    snake->snakeBody.insert(snake->snakeBody.end(), {0.0, 0.0});
}

void Game::SnakeBodyUpdate(Game::Snake * snake, Game * game){
    if (snake->Food[0] == snake->snakeBody[0] && snake->Food[1] == snake->snakeBody[1])
    {
        std::array<int, 2> rn = {GetRandomValue(0,31), GetRandomValue(0,23)};
        snake->snakeBody.insert(snake->snakeBody.end(), {(float)snake->snakeBody[(float)snake->snakeBody.size() - 2], (float)snake->snakeBody[(float)snake->snakeBody.size() - 1]});
        game->score +=1;
        snake->Food = {rn[0], rn[1]};
        
        // std::cout << "(" << rn[0] << ", " << rn[1] << ")" << std::endl;
        // std::cout << "(" << snake->Food[0] << ", " << snake->Food[1] << ")" << std::endl << std::endl;
    }
}

void Game::Reset(Game::Snake * snake, Game * game){
    game->score = 0;
    snake->Food = {10, 10};
    snake->snakeBody = {0, 0};
    snake->snake_direction_state = 'd';
}