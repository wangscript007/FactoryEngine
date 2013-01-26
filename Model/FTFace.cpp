
#include <Model/FTFace.h>
#include <Main/FTLog.h>
#include <Model/FTPolygon.h>
#include "FTLine.h"

FTFace::FTFace()
{
    
}


void FTFace::Render()
{
    
    FTNode::Render();
    glEnable(GL_DEPTH_TEST);
    FTLog(kFTLogModel, "render");
    //
    // vertices
    
    glBegin(GL_POLYGON);
    for(auto i = m_vPointsVector.begin(); i != m_vPointsVector.end(); ++i) {
        glColor3f(0.5f,0.5f,0.5f);
        glNormal3f(0,-1,0);
        glVertex3f((*i)->m_vOrigin.m_fX, (*i)->m_vOrigin.m_fY, (*i)->m_vOrigin.m_fZ);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i = m_vPointsVector.size() - 1; i >= 0; i--) {
        glColor3f(0.5f,0.5f,0.5f);
        glNormal3f(0,1,0);
        glVertex3f(m_vPointsVector[i]->m_vOrigin.m_fX,
                   m_vPointsVector[i]->m_vOrigin.m_fY,
                   m_vPointsVector[i]->m_vOrigin.m_fZ);
    }
    glEnd();

    
}

#pragma mark - Instance

void FTFace::SetSize(const O5Vec3 vSize)
{
    m_vSize = vSize;
}

void FTFace::SetOrigin(const O5Vec3 vOrigin)
{
    m_vOrigin = vOrigin;
}


void FTFace::AddPoint(FTPoint* pPoint)
{
    m_vPointsVector.push_back(pPoint);
}

void FTFace::AddLine(FTLine* pLine)
{
    m_vLinesVector.push_back(pLine);
    AddNode(pLine);
}
//
// Checks if point is int the same plane with face.
// Point is in same plane if any three points coordinate in same axes is the same.
//
bool FTFace::IsInFacePlane(O5Vec3 vec)
{
    return true;
}
//
// Checks point in the same plane intersection with face
//
bool FTFace::Contains(O5Vec3 vec)
{
    return false;
}
//
// Adds cut region to face, should divide into convex polygons
//
void FTFace::Cut(FTFace *cutFace)
{
    
}

