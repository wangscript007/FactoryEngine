//
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Workspace/HUD.h>

namespace ftr {

void HUD::Render(Layer& layer)
{
    const float k = 1;
    static const Color4f color = Color4f(0.0f, 0.5f, 0.0f, 1.0f);
    static const Color4f pickingColor = Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    rectanglePrimitive[0].mVec[0].set(k,k,k);
    rectanglePrimitive[0].mVec[1].set(-k,k,k);
    rectanglePrimitive[0].mVec[2].set(-k,-k,k);
    rectanglePrimitive[0].mVec[3].set(k,-k,k);
    rectanglePrimitive[0].color = color;
    rectanglePrimitive[0].mPickingColor = pickingColor;
    layer.AddPrimitive(rectanglePrimitive[0]);
    
    rectanglePrimitive[1].mVec[0].set(k,k,k);
    rectanglePrimitive[1].mVec[1].set(k,-k,k);
    rectanglePrimitive[1].mVec[2].set(k,-k,-k);
    rectanglePrimitive[1].mVec[3].set(k,k,-k);
    rectanglePrimitive[1].color = color;
    rectanglePrimitive[1].mPickingColor = pickingColor;
    layer.AddPrimitive(rectanglePrimitive[1]);
    
    rectanglePrimitive[2].mVec[0].set(k,k,k);
    rectanglePrimitive[2].mVec[1].set(k,k,-k);
    rectanglePrimitive[2].mVec[2].set(-k,k,-k);
    rectanglePrimitive[2].mVec[3].set(-k,k,k);
    rectanglePrimitive[2].color = color;
    rectanglePrimitive[2].mPickingColor = pickingColor;
    layer.AddPrimitive(rectanglePrimitive[2]);
    
    rectanglePrimitive[3].mVec[0].set(-k,k,k);
    rectanglePrimitive[3].mVec[1].set(-k,k,-k);
    rectanglePrimitive[3].mVec[2].set(-k,-k,-k);
    rectanglePrimitive[3].mVec[3].set(-k,-k,k);
    rectanglePrimitive[3].color = color;
    rectanglePrimitive[3].mPickingColor = pickingColor;
    layer.AddPrimitive(rectanglePrimitive[3]);
    
    rectanglePrimitive[4].mVec[0].set(-k,-k,-k);
    rectanglePrimitive[4].mVec[1].set(k,-k,-k);
    rectanglePrimitive[4].mVec[2].set(k,-k,k);
    rectanglePrimitive[4].mVec[3].set(-k,-k,k);
    rectanglePrimitive[4].color = color;
    rectanglePrimitive[4].mPickingColor = pickingColor;
    layer.AddPrimitive(rectanglePrimitive[4]);
    
    rectanglePrimitive[5].mVec[0].set(k,-k,-k);
    rectanglePrimitive[5].mVec[1].set(-k,-k,-k);
    rectanglePrimitive[5].mVec[2].set(-k,k,-k);
    rectanglePrimitive[5].mVec[3].set(k,k,-k);
    rectanglePrimitive[5].color = color;
    rectanglePrimitive[5].mPickingColor = pickingColor;
    layer.AddPrimitive(rectanglePrimitive[5]);
    
    RenderDesktop(layer);
}
    
void HUD::RenderDesktop(Layer& layer)
{
    return;
    const float k = 20;
    desktopPrimitive.mVec[3].set(k,0.0f,k);
    desktopPrimitive.mVec[2].set(-k,0.0f,k);
    desktopPrimitive.mVec[1].set(-k,0.0f,-k);
    desktopPrimitive.mVec[0].set(k,0.0f,-k);
    desktopPrimitive.color.set(0.3f, 0.3f, 0.3f);
    layer.AddPrimitive(desktopPrimitive);
}

}