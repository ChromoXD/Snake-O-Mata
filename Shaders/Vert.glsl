#version 430 core

layout(location = 0) in vec3 postion;
layout(location = 1) in vec2 uv;

out vec4 TexCoords;

void main(){
    gl_Position = vec4(postion, 1.0);
    TexCoords = vec4(uv, 1.0, 1.0);
}