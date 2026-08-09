#pragma once

#include <glad.h>
#include <string>

extern unsigned int CreateShader(const char *ShaderSource, int SHADER_TYPE, std::string type);
extern char *Error_logger(GLuint Shader, std::string ShaderType, int * success, char * log_info);
extern void UserInput(char *direction, double time);

extern GLuint ComputeShader,
       ComputeProgram, 
       GraphicsProgram, 
       FragmentShader, 
       VertexShader;

extern GLuint VBO, 
       VAO, 
       EBO, 
       Snakebody, 
       Food, 
       Score,
       SnakeLength;


class ShaderFunctions{
    public: 
        void BindBuffers_SSBO(GLuint * Buffer, GLsizeiptr size, const void * data);
        void SSBO_DataPush(GLuint index, GLuint * Buffer, GLsizeiptr size, const void *data);
};