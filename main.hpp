#pragma once
#include <unordered_map>
#include <vector>
#include <array>
#include <string>

unsigned int CreateShader(const char *ShaderSource, int SHADER_TYPE, std::string type);
char *Error_logger(GLuint Shader, std::string ShaderType);
void UserInput(char *direction, double time);

std::unordered_map<std::string, const char *> Location = {
    {"Fragment_Shader", "Shaders/Frag.glsl"},
    {"Vertex_Shader", "Shaders/Vert.glsl"},
    {"Compute_Shader", "Shaders/Comp.glsl"}};

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
