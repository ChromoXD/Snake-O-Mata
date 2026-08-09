#include "Shader_Function.hpp"
#include "glad.h"
#include <iostream>

GLuint ComputeShader,
       ComputeProgram,
       GraphicsProgram,
       FragmentShader,
       VertexShader;

GLuint VBO,
       VAO,
       EBO,
       Snakebody,
       Food,
       Score,
       SnakeLength;

unsigned int CreateShader(const char *ShaderSource, int SHADER_TYPE, std::string type)
{
    int success;
    char log_info[512];

    unsigned int Shader = glCreateShader(SHADER_TYPE);
    glShaderSource(Shader, 1, &ShaderSource, NULL);
    glCompileShader(Shader);

    std::cout << Error_logger(Shader, type, &success, log_info);

    return Shader;
}

char *Error_logger(GLuint Shader, std::string ShaderType, int * success, char * log_info)
{
    glGetShaderiv(Shader, GL_COMPILE_STATUS, success);
    if (!success)
    {
        glGetShaderInfoLog(Shader, 512, NULL, log_info);
        std::cout << "ERROR::SHADER::" << ShaderType << "::COMPILATION_FAILED\n";
    }
    return log_info;
}

void ShaderFunctions::BindBuffers_SSBO(GLuint * Buffer, GLsizeiptr size, const void * data){
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, *Buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_STATIC_DRAW);
}

void ShaderFunctions::SSBO_DataPush(GLuint index, GLuint * Buffer, GLsizeiptr size, const void *data){
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, *Buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, *Buffer);
}