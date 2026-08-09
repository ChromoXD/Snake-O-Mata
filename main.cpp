#include <raylib.h>
#include <iostream>
#include <glad.h>
#include "main.hpp"
#include <vector>
#include <chrono>
#include "classes_and_functions/Shader_Function.hpp"
#include "classes_and_functions/Game_Class.hpp"

#define GLSL_Version 430

Game game(15);
Game::Snake snake;
ShaderFunctions SF;

int main(int argc, char const *argv[])
{
    const char *Title{"neural cellular SnakeOmata"};
    const char *fragShader{LoadFileText(Location["Fragment_Shader"])};
    const char *vertShader{LoadFileText(Location["Vertex_Shader"])};

    GLuint SnakePos;
    snake.InitSnake(&snake);

    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(width, height, Title);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_CULL_FACE);

    glGenVertexArrays(1, &VAO);
    for (GLuint *i : {&VBO, &EBO, &Snakebody, &Food, &Score, &SnakeLength})
    {
        glGenBuffers(1, i);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    SF.BindBuffers_SSBO(&Snakebody, snake.snakeBody.size() * sizeof(float), snake.snakeBody.data());
    SF.BindBuffers_SSBO(&Food, snake.Food.size() * sizeof(int), snake.Food.data());

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
            game.SnakeBodyUpdate(&snake, &game);
            game.snakeMovement(&snake, &game);
            moveTimer = 0.0f;
        }

        SF.SSBO_DataPush(1, &Snakebody, snake.snakeBody.size() * sizeof(float), snake.snakeBody.data());
        SF.SSBO_DataPush(2, &Food, snake.Food.size() * sizeof(int), snake.Food.data());

        BeginDrawing();
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(GraphicsProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        DrawText(("Score: " + std::to_string(game.getScore())).c_str(), 10, height - 50, 30, (Color){202, 191, 171, 255});

        EndDrawing();
    }

    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteProgram(GraphicsProgram);
        UnloadFileText((char *)fragShader);
        UnloadFileText((char *)vertShader);
        glDeleteShader(FragmentShader);
        glDeleteShader(VertexShader);
        CloseWindow();
    }

    return 0;
}

void UserInput(char *direction, double time)
{

    if (IsKeyPressed(KEY_W) && *direction != 's' && *direction != 'w')
    {
        *direction = 'w';
    }
    if (IsKeyPressed(KEY_A) && *direction != 'd' && *direction != 'a')
    {
        *direction = 'a';
    }
    if (IsKeyPressed(KEY_S) && *direction != 'w' && *direction != 's')
    {
        *direction = 's';
    }
    if (IsKeyPressed(KEY_D) && *direction != 'a' && *direction != 'd')
    {
        *direction = 'd';
    }
}