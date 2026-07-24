#pragma once
#include <unordered_map>
#include <vector>
#include <array>
#include <string>

unsigned int CreateShader(const char *ShaderSource, int SHADER_TYPE, std::string type);
char *Error_logger(GLuint Shader, std::string ShaderType);

GLuint ComputeShader;
GLuint ComputeProgram;
GLuint GraphicsProgram;
GLuint FragmentShader;
GLuint VertexShader;

std::unordered_map<std::string, const char *> Location = {
    {"Fragment_Shader", "X:/aweome/smth/Snake/Shaders/Frag.glsl"},
    {"Vertex_Shader", "X:/aweome/smth/Snake/Shaders/Vert.glsl"},
    {"Compute_Shader", "X:/aweome/smth/Snake/Shaders/Vert.glsl"}};

int width{800}, height{600}; //32x24

float Triangle[] = {
    -1.0f,  1.0f, 0.0f,   0.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,   0.0f, 1.0f,
     1.0f, -1.0f, 0.0f,   1.0f, 1.0f,
     1.0f,  1.0f, 0.0f,   1.0f, 0.0f
};

unsigned int Indeces [] = {
    0, 1, 2,
    0, 2, 3
};

int success;
char log_info[512];

//-------------- Boards --------------

struct Snake
{
    std::vector<float> snakeBody;
    void UpdateSnake();
};


int Table[768]{1};

int food[2]{0,0};
