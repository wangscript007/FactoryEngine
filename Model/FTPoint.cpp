
#include <FactoryEngine.h>

FTPoint::FTPoint()
{
    
}

#pragma mark - Instance

//
// Renders cicle at point position
//
void FTPoint::Render()
{
    glBegin( GL_POINTS );
    glColor3f( 0.95f, 0.207, 0.031f );
    glVertex3f(m_vOrigin.m_fX, m_vOrigin.m_fY, m_vOrigin.m_fZ);
    glEnd();
}