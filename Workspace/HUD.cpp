//
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Workspace/HUD.h>
#include <Main/Log.h>
#include <Main/GLError.h>

namespace ftr {

void HUD::Render(RenderBundle& renderBundle)
{
    const float k = 1;
    rectanglePrimitive[0].mVec[0].set(k,k,k);
    rectanglePrimitive[0].mVec[1].set(-k,k,k);
    rectanglePrimitive[0].mVec[2].set(-k,-k,k);
    rectanglePrimitive[0].mVec[3].set(k,-k,k);
    rectanglePrimitive[0].color.set(1.0f, 0.0f, 0.0f);
    renderBundle.AddPrimitive(rectanglePrimitive[0]);
    
    rectanglePrimitive[1].mVec[0].set(k,k,k);
    rectanglePrimitive[1].mVec[1].set(k,-k,k);
    rectanglePrimitive[1].mVec[2].set(k,-k,-k);
    rectanglePrimitive[1].mVec[3].set(k,k,-k);
    rectanglePrimitive[1].color.set(1.0f, 0.0f, 0.0f);
    renderBundle.AddPrimitive(rectanglePrimitive[1]);
    
    rectanglePrimitive[2].mVec[0].set(k,k,k);
    rectanglePrimitive[2].mVec[1].set(k,k,-k);
    rectanglePrimitive[2].mVec[2].set(-k,k,-k);
    rectanglePrimitive[2].mVec[3].set(-k,k,k);
    rectanglePrimitive[2].color.set(1.0f, 0.0f, 0.0f);
    renderBundle.AddPrimitive(rectanglePrimitive[2]);
    
    rectanglePrimitive[3].mVec[0].set(-k,k,k);
    rectanglePrimitive[3].mVec[1].set(-k,k,-k);
    rectanglePrimitive[3].mVec[2].set(-k,-k,-k);
    rectanglePrimitive[3].mVec[3].set(-k,-k,k);
    rectanglePrimitive[3].color.set(1.0f, 0.0f, 0.0f);
    renderBundle.AddPrimitive(rectanglePrimitive[3]);
    
    rectanglePrimitive[4].mVec[0].set(-k,-k,-k);
    rectanglePrimitive[4].mVec[1].set(k,-k,-k);
    rectanglePrimitive[4].mVec[2].set(k,-k,k);
    rectanglePrimitive[4].mVec[3].set(-k,-k,k);
    rectanglePrimitive[4].color.set(1.0f, 0.0f, 0.0f);
    renderBundle.AddPrimitive(rectanglePrimitive[4]);
    
    rectanglePrimitive[5].mVec[0].set(k,-k,-k);
    rectanglePrimitive[5].mVec[1].set(-k,-k,-k);
    rectanglePrimitive[5].mVec[2].set(-k,k,-k);
    rectanglePrimitive[5].mVec[3].set(k,k,-k);
    rectanglePrimitive[5].color.set(1.0f, 0.0f, 0.0f);
    renderBundle.AddPrimitive(rectanglePrimitive[5]);
    
    RenderDesktop(renderBundle);
}
    
void HUD::RenderDesktop(RenderBundle& renderBundle)
{
    const float k = 20;
    desktopPrimitive.mVec[0].set(k,0.0f,k);
    desktopPrimitive.mVec[1].set(-k,0.0f,k);
    desktopPrimitive.mVec[2].set(-k,0.0f,-k);
    desktopPrimitive.mVec[3].set(k,0.0f,-k);
    desktopPrimitive.color.set(0.3f, 0.3f, 0.3f);
    renderBundle.AddPrimitive(desktopPrimitive);
}

}