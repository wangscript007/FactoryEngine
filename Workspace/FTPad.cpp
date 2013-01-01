// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include "FTPad.h"
#include "FTLog.h"

void FTPad::Render()
{
    FTLog(kFTLogWorkspace, "");
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDisable(GL_LIGHTING);
    glLineWidth(1);
    //
    // grind
    //
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    int linesCount = mfA * mfScale;
    int i;
    GLfloat a2 = mfA/2;
    //
    // along x axis
    //
    GLfloat x = -a2;
    for(i = 0; i <= linesCount; i++) {
        if ((i%((int)mfA/2) != 0)  || (i == 0) || (i == mfA)) {
            glBegin(GL_LINES);
            {
                glVertex3d(x, 0, -a2);
                glVertex3d(x, 0, a2);
            }
            glEnd();
        }
		x += mfScale;
    }
    //
    // along z axis
    //
	GLfloat z = -a2;
    for(i = 0; i <= linesCount; i++) {
        if ((i%((int)mfA/2) != 0) || (i == 0) || (i == mfA)) {
            glBegin(GL_LINES);
            {
                glVertex3d(-a2, 0, z);
                glVertex3d(a2, 0, z);
            }
            glEnd();
        }
		z += mfScale;
	}
    //
    // Axes
    //
    float a = mfA;
	// x
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES); 
	{
		glVertex3d(-a/2, 0, 0);
		glVertex3d(a/2+1, 0, 0);
	}
	glEnd();
	
	// y
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
	{
		glVertex3d(0, 0, 0);
		glVertex3d(0, a/2, 0);
	}
	glEnd();
	
	// z
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
	{
		glVertex3d(0, 0, -a/2);
		glVertex3d(0, 0, a/2+1);
	}
	glEnd();
}