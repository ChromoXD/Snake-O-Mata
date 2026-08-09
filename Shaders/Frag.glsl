#version 430 core

in vec4 FragCord;
layout(std430, binding = 1) buffer SnakeBody
{
    float Body[];
};

layout(std430, binding = 2) buffer SnakeFood
{
    int Food[];
};

out vec4 FragColor;

void main(){
    vec4 Pixel_color;
    vec2 grid = mod(gl_FragCoord.xy, 25.0);

    if((grid.x > 0.0 && grid.x <= 1.0) || (grid.y > 0.0 && grid.y <= 1.0))
    {
        Pixel_color = vec4(0.322, 0.341, 0.365, 1.0);
    }
    else
    {
        Pixel_color  = vec4(0.255, 0.267, 0.294, 1.0);
    }

    if((floor(gl_FragCoord.x/25)) == Food[0] && (floor(gl_FragCoord.y/25)) == Food[1]){
            Pixel_color  = vec4(0.918, 0.482, 0.482, 1.0);
    }

    for(int x = 0; x < Body.length()/2; x++){
        if((floor(gl_FragCoord.x/25)) == Body[2*x] && (floor(gl_FragCoord.y/25)) == Body[2*x+1]){
            Pixel_color  = vec4(0.875, 0.847, 0.784, 1.0);
        }
    }


    FragColor = Pixel_color;
}