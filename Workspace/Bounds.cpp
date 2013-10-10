//
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Workspace/Bounds.h>

namespace ftr {
    
void Bounds::Render(Layer& layer)
{
    const float k = 50;
    static const glm::vec4 color = glm::vec4(0.5f, 0.5f, 0.5f, 0.9f);
    
    rectanglePrimitive[0].mVec[0] = glm::vec3(k,k,k);
    rectanglePrimitive[0].mVec[1] = glm::vec3(-k,k,k);
    rectanglePrimitive[0].mVec[2] = glm::vec3(-k,-k,k);
    rectanglePrimitive[0].mVec[3] = glm::vec3(k,-k,k);
    rectanglePrimitive[0].color = color;
    rectanglePrimitive[0].setOption(Primitive::kUseBlend, true);
    layer.AddPrimitive(rectanglePrimitive[0]);
    
    rectanglePrimitive[1].mVec[0] = glm::vec3(k,k,k);
    rectanglePrimitive[1].mVec[1] = glm::vec3(k,-k,k);
    rectanglePrimitive[1].mVec[2] = glm::vec3(k,-k,-k);
    rectanglePrimitive[1].mVec[3] = glm::vec3(k,k,-k);
    rectanglePrimitive[1].color = color;
    rectanglePrimitive[1].setOption(Primitive::kUseBlend, true);
    layer.AddPrimitive(rectanglePrimitive[1]);
    
    rectanglePrimitive[2].mVec[0] = glm::vec3(k,k,k);
    rectanglePrimitive[2].mVec[1] = glm::vec3(k,k,-k);
    rectanglePrimitive[2].mVec[2] = glm::vec3(-k,k,-k);
    rectanglePrimitive[2].mVec[3] = glm::vec3(-k,k,k);
    rectanglePrimitive[2].color = color;
    rectanglePrimitive[2].setOption(Primitive::kUseBlend, true);
    layer.AddPrimitive(rectanglePrimitive[2]);
    
    rectanglePrimitive[3].mVec[0] = glm::vec3(-k,k,k);
    rectanglePrimitive[3].mVec[1] = glm::vec3(-k,k,-k);
    rectanglePrimitive[3].mVec[2] = glm::vec3(-k,-k,-k);
    rectanglePrimitive[3].mVec[3] = glm::vec3(-k,-k,k);
    rectanglePrimitive[3].color = color;
    rectanglePrimitive[3].setOption(Primitive::kUseBlend, true);
    layer.AddPrimitive(rectanglePrimitive[3]);
    
    rectanglePrimitive[4].mVec[0] = glm::vec3(-k,-k,-k);
    rectanglePrimitive[4].mVec[1] = glm::vec3(k,-k,-k);
    rectanglePrimitive[4].mVec[2] = glm::vec3(k,-k,k);
    rectanglePrimitive[4].mVec[3] = glm::vec3(-k,-k,k);
    rectanglePrimitive[4].color = color;
    rectanglePrimitive[4].setOption(Primitive::kUseBlend, true);
    layer.AddPrimitive(rectanglePrimitive[4]);
    
    rectanglePrimitive[5].mVec[0] = glm::vec3(k,-k,-k);
    rectanglePrimitive[5].mVec[1] = glm::vec3(-k,-k,-k);
    rectanglePrimitive[5].mVec[2] = glm::vec3(-k,k,-k);
    rectanglePrimitive[5].mVec[3] = glm::vec3(k,k,-k);
    rectanglePrimitive[5].color = color;
    rectanglePrimitive[5].setOption(Primitive::kUseBlend, true);
    layer.AddPrimitive(rectanglePrimitive[5]);
}
    
}