
in vec3 position;
in vec4 color;
in vec4 normal;

out vec4 Color;
out vec4 Normal;

void main()
{
    gl_Position.xyz = position;
    gl_Position.w = 1.0;
    Color = color;
    Normal = normal;
}
