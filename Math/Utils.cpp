
#include <Math/Utils.h>


namespace ftr {

    
Vec3 Utils::Viewport(Vec3 sceneVec)
{
    return Vec3();
}

Vec3 Utils::Scene(const Vec3 windowVec)
{
    return Vec3();
}

GLfloat Utils::DepthAtWindowPoint(const Vec2 point)
{
    GLfloat depth[2];
    GLint x = point.mX;
    GLint y = point.mY;
    glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    return depth[0];
}

void Utils::PrintMatrix(int cols, int rows, GLdouble *matrix)
{   
    printf("{\n");
    for (int i = 0; i < rows; i++) {
        printf("{");
        for (int j = 0; j < cols; j++) {
            printf("[%4.4f]     ", matrix[j + i*cols]);
        }
        printf("}\n");
    }
    printf("}\n");
}

// https://sites.google.com/site/vamsikrishnav/gluunproject
//The function that handles the mouse clicks glutMouseFunc( )
/*
void mouse( int button, int state, int x, int y )
{
    double modelview[16], projection[16];
    int viewport[4];
    float z;
	//get the projection matrix		
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
	//get the modelview matrix		
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	//get the viewport		
    glGetIntegerv( GL_VIEWPORT, viewport );
	
    //Read the window z co-ordinate 
    //(the z value on that point in unit cube)		
    glReadPixels( x, viewport[3]-y, 1, 1,
                 GL_DEPTH_COMPONENT, GL_FLOAT, &z );
    
    //Unproject the window co-ordinates to 
    //find the world co-ordinates.
    gluUnProject( x, viewport[3]-y, z, modelview, 
                 projection, viewport, &objx, &objy, &objz );
}
*/

// http://nehe.gamedev.net/tutorial/3d_lens_flare_with_occlusion_testing/16007/
/*
 Now we will ask OGL to project some geometry for us using the gluProject function. Practically we ask OGL to guess where a point in space will be projected in our current viewport, using arbitrary viewport and transform matrices we pass to the function. If we pass to the function the current matrices (retrievede with the glGet funcs) we will have the real position on screen where the dot will be drawn. The interesting part is that we also get a Z value back, this means that reading the REAL buffer for Z values we can discover if the flare is in front or if it's occluded by some objects.
 */

// ########## New Stuff by rIO.Spinning Kids ##########
/*
 bool glCamera::IsOccluded(glPoint p)
 {
 GLint viewport[4];                          // Space For Viewport Data
 GLdouble mvmatrix[16], projmatrix[16];                  // Space For Transform Matrix
 GLdouble winx, winy, winz;                      // Space For Returned Projected Coords
 GLdouble flareZ;                            // Here We Will Store The Transformed Flare Z
 GLfloat bufferZ;                            // Here We Will Store The Read Z From The Buffer
 
 glGetIntegerv (GL_VIEWPORT, viewport);                  // Get Actual Viewport
 glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);               // Get Actual Model View Matrix
 glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);            // Get Actual Projection Matrix
 
 // This Asks OGL To Guess The 2D Position Of A 3D PointNode Inside The Viewport
 gluProject(p.x, p.y, p.z, mvmatrix, projmatrix, viewport, &winx, &winy, &winz);
 flareZ = winz;
 
 // We Read Back One Pixel From The Depth Buffer (Exactly Where Our Flare Should Be Drawn)
 glReadPixels(winx, winy,1,1,GL_DEPTH_COMPONENT, GL_FLOAT, &bufferZ);
 
 // If The Buffer Z Is Lower Than Our Flare Guessed Z Then Don't Draw
 // This Means There Is Something In Front Of Our Flare
 if (bufferZ < flareZ)
 return true;
 else
 return false;
 }
 */

}