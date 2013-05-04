
#pragma once

#include <Shading/Shader.h>

namespace ftr {

class ShaderFactory
{
public:
    virtual ~ShaderFactory() {}
    Shader* CreateShader();
};

}

