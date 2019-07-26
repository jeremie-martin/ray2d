R""(
#version 430
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 col;

void main()
{
    col = vec4(color, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
}
)""