#include <raylib.h>
#include <iostream>
#include <glad.h>
#include "main.hpp"
#include <vector>
#include <chrono>

#define GLSL_Version 430

Game game(30);
Game::Snake snake;

class ShaderFunctions{
    public: 

        void BindBuffers_SSBO(GLuint * Buffer, GLsizeiptr size, const void * data){
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, *Buffer);
            glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_STATIC_DRAW);
        }

        void SSBO_DataPush(GLuint index, GLuint * Buffer, GLsizeiptr size, const void *data){

            glBindBuffer(GL_SHADER_STORAGE_BUFFER, *Buffer);
            glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, *Buffer);
        }
};

ShaderFunctions SF;

int main(int argc, char const *argv[])
{
    const char *Title{"neural cellular SnakeOmata"};
    const char *fragShader{LoadFileText(Location["Fragment_Shader"])};
    const char *vertShader{LoadFileText(Location["Vertex_Shader"])};
    // const char *compShader{LoadFileText(Location["Compute_Shader"])};

    GLuint SnakePos;
    snake.InitSnake();

    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(width, height, Title);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_CULL_FACE);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &Snakebody);
    glGenBuffers(1, &Food);
    glGenBuffers(1, &Score);
    glGenBuffers(1, &SnakeLength);


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    SF.BindBuffers_SSBO(&Snakebody , snake.snakeBody.size() * sizeof(float), snake.snakeBody.data());
    SF.BindBuffers_SSBO(&Food , snake.Food.size() * sizeof(int), snake.Food.data());
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indeces), Indeces, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    
    GraphicsProgram = glCreateProgram();
    
    FragmentShader = CreateShader(fragShader, GL_FRAGMENT_SHADER, "FRAGMENT_SHADER");
    VertexShader = CreateShader(vertShader, GL_VERTEX_SHADER, "VERTEX_SHADER");
    
    glAttachShader(GraphicsProgram, FragmentShader);
    glAttachShader(GraphicsProgram, VertexShader);

    glLinkProgram(GraphicsProgram);

    glUseProgram(GraphicsProgram);
    

    SetTargetFPS(game.getFPS());

float moveTimer = 0.0f;
float moveInterval = 0.01f;

while (!WindowShouldClose())
{
    float dt = GetFrameTime();

    UserInput(&snake.snake_direction_state, moveInterval);

    moveTimer += dt;

    if (moveTimer >= moveInterval)
    {
        game.SnakeBodyUpdate(&snake);
        game.snakeMovement(&snake);
        moveTimer = 0.0f;
    }

        SF.SSBO_DataPush(1, &Snakebody, snake.snakeBody.size() * sizeof(float), snake.snakeBody.data());
        SF.SSBO_DataPush(2, &Food, snake.Food.size() * sizeof(int), snake.Food.data());
        
        BeginDrawing();
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(GraphicsProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        DrawText(("Score: " + std::to_string(game.getScore())).c_str(), 10 ,height - 50 ,30, (Color){202, 191, 171, 255});

        EndDrawing();
    }

    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        // glDeleteProgram(ComputeProgram);
        glDeleteProgram(GraphicsProgram);
        UnloadFileText((char *)fragShader);
        UnloadFileText((char *)vertShader);
        // glDeleteShader(ComputeShader);
        glDeleteShader(FragmentShader);
        glDeleteShader(VertexShader);
        CloseWindow();
    }

    return 0;
}

unsigned int CreateShader(const char *ShaderSource, int SHADER_TYPE, std::string type)
{
    unsigned int Shader = glCreateShader(SHADER_TYPE);
    glShaderSource(Shader, 1, &ShaderSource, NULL);
    glCompileShader(Shader);

    std::cout << Error_logger(Shader, type);

    return Shader;
}

char *Error_logger(GLuint Shader, std::string ShaderType)
{
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(Shader, 512, NULL, log_info);
        std::cout << "ERROR::SHADER::" << ShaderType << "::COMPILATION_FAILED\n";
    }
    return log_info;
}

void UserInput(char *direction, double time)
{
    
    if (IsKeyPressed(KEY_W) && *direction != 's' && *direction != 'w'){ 
        *direction = 'w';
    }
    if (IsKeyPressed(KEY_A) && *direction != 'd' && *direction != 'a'){ 
        *direction = 'a';
    }
    if (IsKeyPressed(KEY_S) && *direction != 'w' && *direction != 's'){ 
        *direction = 's';
    }
    if (IsKeyPressed(KEY_D) && *direction != 'a' && *direction != 'd'){ 
        *direction = 'd';
    }
}

void Game::snakeMovement(Game::Snake *snake)
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

    if ((int)snake->snakeBody[0] > 31) snake->snakeBody[0] = 0;
    if ((int)snake->snakeBody[0] < 0)  snake->snakeBody[0] = 31;
    if ((int)snake->snakeBody[1] < 0)  snake->snakeBody[1] = 23;
    if ((int)snake->snakeBody[1] > 23) snake->snakeBody[1] = 0;

    
    for (size_t i = 1; i < snake->snakeBody.size()/2; i++)
    {
        if (snake->snakeBody[0] == snake->snakeBody[i*2] && snake->snakeBody[1] == snake->snakeBody[i*2 + 1])
        {
            game.Reset();
        }
    }
    
}

void Game::Snake::InitSnake(){

    snake.snakeBody.insert(snake.snakeBody.end(), {0.0, 0.0});
}

void Game::SnakeBodyUpdate(Game::Snake * snake){
    if (snake->Food[0] == snake->snakeBody[0] && snake->Food[1] == snake->snakeBody[1])
    {
        std::array<int, 2> rn = {GetRandomValue(0,31), GetRandomValue(0,23)};
        snake->snakeBody.insert(snake->snakeBody.end(), {(float)snake->snakeBody[(float)snake->snakeBody.size() - 2], (float)snake->snakeBody[(float)snake->snakeBody.size() - 1]});
        game.score +=1;
        snake->Food = {rn[0], rn[1]};
        
        // std::cout << "(" << rn[0] << ", " << rn[1] << ")" << std::endl;
        // std::cout << "(" << snake->Food[0] << ", " << snake->Food[1] << ")" << std::endl << std::endl;
    }

}

void Game::Reset(){
    score = 0;
    snake.Food = {10, 10};
    snake.snakeBody = {0, 0};
    snake.snake_direction_state = 'd';
}