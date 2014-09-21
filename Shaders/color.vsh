
struct Transform {
    mat4 view;
    mat4 projection;
};
uniform Transform transformVar;


in vec4 position;
in vec3 pickingColor;
out vec3 Color;

void main()
{
    Color = pickingColor;
    gl_Position = transformVar.projection * transformVar.view * position;
}