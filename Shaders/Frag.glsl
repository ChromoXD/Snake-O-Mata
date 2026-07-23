#version 430 core

in vec4 FragCord;
uniform vec2 SnakePos;

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

    FragColor = Pixel_color;
}