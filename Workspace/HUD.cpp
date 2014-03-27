//
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Workspace/HUD.h>

namespace ftr {

void HUD::Render(Layer& layer)
{
    const float k = 1;
    static const glm::vec4 color = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);
    static const glm::vec4 pickingColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    rectanglePrimitive[0].mVec[0] = glm::vec3(k,k,k);
    rectanglePrimitive[0].mVec[1] = glm::vec3(-k,k,k);
    rectanglePrimitive[0].mVec[2] = glm::vec3(-k,-k,k);
    rectanglePrimitive[0].mVec[3] = glm::vec3(k,-k,k);
    rectanglePrimitive[0].mColor = color;
    rectanglePrimitive[0].mPickingColor = pickingColor;
    layer.AddPrimitive(rectanglePrimitive[0]);
    
    rectanglePrimitive[1].mVec[0] = glm::vec3(k,k,k);
    rectanglePrimitive[1].mVec[1] = glm::vec3(k,-k,k);
    rectanglePrimitive[1].mVec[2] = glm::vec3(k,-k,-k);
    rectanglePrimitive[1].mVec[3] = glm::vec3(k,k,-k);
    rectanglePrimitive[1].mColor = color;
    rectanglePrimitive[1].mPickingColor = pickingColor;
    layer.AddPrimitive(rectanglePrimitive[1]);
    
    rectanglePrimitive[2].mVec[0] = glm::vec3(k,k,k);
    rectanglePrimitive[2].mVec[1] = glm::vec3(k,k,-k);
    rectanglePrimitive[2].mVec[2] = glm::vec3(-k,k,-k);
    rectanglePrimitive[2].mVec[3] = glm::vec3(-k,k,k);
    rectanglePrimitive[2].mColor = color;
    rectanglePrimitive[2].mPickingColor = pickingColor;
    layer.AddPrimitive(rectanglePrimitive[2]);
    
    rectanglePrimitive[3].mVec[0] = glm::vec3(-k,k,k);
    rectanglePrimitive[3].mVec[1] = glm::vec3(-k,k,-k);
    rectanglePrimitive[3].mVec[2] = glm::vec3(-k,-k,-k);
    rectanglePrimitive[3].mVec[3] = glm::vec3(-k,-k,k);
    rectanglePrimitive[3].mColor = color;
    rectanglePrimitive[3].mPickingColor = pickingColor;
    layer.AddPrimitive(rectanglePrimitive[3]);
    
    rectanglePrimitive[4].mVec[0] = glm::vec3(-k,-k,-k);
    rectanglePrimitive[4].mVec[1] = glm::vec3(k,-k,-k);
    rectanglePrimitive[4].mVec[2] = glm::vec3(k,-k,k);
    rectanglePrimitive[4].mVec[3] = glm::vec3(-k,-k,k);
    rectanglePrimitive[4].mColor = color;
    rectanglePrimitive[4].mPickingColor = pickingColor;
    layer.AddPrimitive(rectanglePrimitive[4]);
    
    rectanglePrimitive[5].mVec[0] = glm::vec3(k,-k,-k);
    rectanglePrimitive[5].mVec[1] = glm::vec3(-k,-k,-k);
    rectanglePrimitive[5].mVec[2] = glm::vec3(-k,k,-k);
    rectanglePrimitive[5].mVec[3] = glm::vec3(k,k,-k);
    rectanglePrimitive[5].mColor = color;
    rectanglePrimitive[5].mPickingColor = pickingColor;
    layer.AddPrimitive(rectanglePrimitive[5]);
    
    RenderDesktop(layer);
}
    
void HUD::RenderDesktop(Layer& layer)
{
    return;
    const float k = 20;
    desktopPrimitive.mVec[3] = glm::vec3(k,0.0f,k);
    desktopPrimitive.mVec[2] = glm::vec3(-k,0.0f,k);
    desktopPrimitive.mVec[1] = glm::vec3(-k,0.0f,-k);
    desktopPrimitive.mVec[0] = glm::vec3(k,0.0f,-k);
    desktopPrimitive.mColor = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
    layer.AddPrimitive(desktopPrimitive);
}

}