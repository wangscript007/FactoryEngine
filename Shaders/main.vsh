#version 150

struct Transform {
    mat4 view;
    mat4 projection;
};
uniform Transform transformVar;


in vec4 position;
in vec4 color;
in vec4 normal;

out vec4 localNormal;
out vec3 localNormal3;
out vec4 localPosition;
out vec3 localPosition3;
out vec4 Color;
out vec3 Eye;

//--------------------------------------------------------------------------------------------------
vec4 Local(in vec4 coords)
{
    return transformVar.view * coords;
}

//--------------------------------------------------------------------------------------------------
void main()
{
    localNormal = Local(normal);
    localNormal3 = vec3(localNormal);
    localPosition = Local(position);

    localPosition3 = (vec3(localPosition)) / localPosition.w;
    Eye = -normalize(vec3(0.0, 0.0, 1.0));

    Color = color;
    gl_Position = transformVar.projection * localPosition;
}