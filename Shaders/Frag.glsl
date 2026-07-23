#version 430 core

in vec4 FragCord;

out vec4 FragColor;

void main(){
    vec4 Pixel_color;
    vec2 grid = mod(gl_FragCoord.xy, 10.0);

    if(grid.x == 0.0 || grid.y == 0.0)
    {
        Pixel_color = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else
    {
        Pixel_color  = vec4(0.0, 0.0, 0.0, 1.0);
    }

    FragColor = Pixel_color;
}