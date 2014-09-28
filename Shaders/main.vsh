
struct Transform {
    MAT4 view;
    MAT4 projection;
};
uniform Transform transformVar;


in VEC4 position;
in VEC4 color;
in VEC4 normal;

out VEC4 localNormal;
out VEC3 localNormal3;
out VEC4 localPosition;
out VEC3 localPosition3;
out VEC4 Color;
out VEC3 Eye;

//--------------------------------------------------------------------------------------------------
VEC4 Local(in VEC4 coords)
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