// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//


#include <FactoryEngine.h>

FTFace::FTFace()
{
    m_eType = FTFace::Rectangle;
}

void FTFace::Render()
{
    // 
    // Setup gl state
    //
    
    // 
    // Render rectangle
    //
    glBegin(GL_QUADS);
    {
        glColor4f(0.0, 1.0, 1.0, 0.0);
        //
        // If face is parallel to XZ
        //
        glVertex3f(m_vOrigin.m_fX,                  m_vOrigin.m_fY,             m_vOrigin.m_fZ);
        glVertex3f(m_vOrigin.m_fX + m_vSize.m_fX,   m_vOrigin.m_fY,             m_vOrigin.m_fZ + m_vSize.m_fZ);
        glVertex3f(m_vOrigin.m_fX + m_vSize.m_fX,   m_vOrigin.m_fY,             m_vOrigin.m_fZ+m_vSize.m_fZ);
        glVertex3f(m_vOrigin.m_fX,                  m_vOrigin.m_fY,             m_vOrigin.m_fZ+m_vSize.m_fZ);
    }
    glEnd();
}

#pragma mark - Instance
//
// Checks if point is int the same plane with face.
// Point is in same plane if any three points coordinate in same axes is the same.
//
bool FTFace::IsInFacePlane(FTVec3f vec)
{
    return true;
}
//
// Checks point in the same plane intersection with face
//
bool FTFace::Contains(FTVec3f vec)
{
    
}
//
// Adds cut region to face, should divide into convex polygons
//
void FTFace::Cut(FTFace *cutFace)
{
    
}

