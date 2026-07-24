#include <raylib.h>
#include <iostream>
#include <glad.h>
#include "main.hpp"
#include <vector>

#define GLSL_Version 430

int main(int argc, char const *argv[])
{
    const char *Title{"neural cellular SnakeOmata"};
    const char *fragShader{LoadFileText(Location["Fragment_Shader"])};
    const char *vertShader{LoadFileText(Location["Vertex_Shader"])};
    const char *compShader{LoadFileText(Location["Compute_Shader"])};

    GLuint SnakePos;

    Snake snake;
    snake.snakeBody.insert(snake.snakeBody.end(), {0.0, 0.0});

    InitWindow(width, height, Title);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_CULL_FACE);

    GLuint VBO, VAO, EBO, SSBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &SSBO);

    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_SHADER_STORAGE_BUFFER, snake.snakeBody.size() * sizeof(float), snake.snakeBody.data(), GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, SSBO);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indeces), Indeces, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    {
        ComputeShader = CreateShader(compShader, GL_COMPUTE_SHADER, "COMPUTE_SHADER");
        ComputeProgram = glCreateProgram();
        glAttachShader(ComputeProgram, ComputeShader);

        GraphicsProgram = glCreateProgram();

        FragmentShader = CreateShader(fragShader, GL_FRAGMENT_SHADER, "FRAGMENT_SHADER");
        VertexShader = CreateShader(vertShader, GL_VERTEX_SHADER, "VERTEX_SHADER");

        glAttachShader(GraphicsProgram, FragmentShader);
        glAttachShader(GraphicsProgram, VertexShader);

        glLinkProgram(GraphicsProgram);
        glLinkProgram(ComputeProgram);

        glUseProgram(GraphicsProgram);

        glUseProgram(ComputeProgram);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(GraphicsProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        EndDrawing();
    }

    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteProgram(ComputeProgram);
        glDeleteProgram(GraphicsProgram);
        UnloadFileText((char *)compShader);
        UnloadFileText((char *)fragShader);
        UnloadFileText((char *)vertShader);
        glDeleteShader(ComputeShader);
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