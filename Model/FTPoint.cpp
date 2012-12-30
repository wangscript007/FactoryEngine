
#include "FTPoint.h"

const float FTPoint::c_fR = 4.0f;

FTPoint::FTPoint()
{
    
}

#pragma mark - Instance

//
// Renders cicle at point position
//
void FTPoint::Render()
{
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(c_fR);
    
    glBegin(GL_POINTS);
        glColor3f(0.95f, 0.207, 0.031f);
        glVertex3f(m_vOrigin.m_fX, m_vOrigin.m_fY, m_vOrigin.m_fZ);
    glEnd();
}