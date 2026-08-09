#pragma once
#include <unordered_map>
#include <vector>
#include <array>
#include <string>

unsigned int CreateShader(const char *ShaderSource, int SHADER_TYPE, std::string type);
char *Error_logger(GLuint Shader, std::string ShaderType);
void UserInput(char *direction, double time);

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

std::unordered_map<std::string, const char *> Location = {
    {"Fragment_Shader", "X:/aweome/smth/Snake/Shaders/Frag.glsl"},
    {"Vertex_Shader", "X:/aweome/smth/Snake/Shaders/Vert.glsl"},
    {"Compute_Shader", "X:/aweome/smth/Snake/Shaders/Comp.glsl"}};

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
        void InitSnake();
    };

    Game(int FPS){
        this->FPS = FPS;
    }

    int Table[768];
    void snakeMovement (Snake * snake);

    int getFPS(){return this->FPS;}
    int& getScore(){return this-> score;}
    void setFPS(int score){ this->score = score; }
    void SnakeBodyUpdate(Snake * snake);
    void Reset();
};