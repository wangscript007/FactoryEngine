// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Workspace/HUD.h>
#include <Main/Log.h>
#include <Main/GLError.h>

namespace ftr {

void HUD::Render(RenderBundle& renderBundle)
{
    Log(kLogWorkspace, "");
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
    
    //glutSolidTeapot(1);
    //glutWireTeapot(1);
    RenderCube();
    //RenderIcosahedron();
    RenderDesktop();
}

void HUD::RenderCube()
{
    // vertex coords array
    const float k = 1;
    static GLfloat vertices[] =
    {k,k,k,  -k,k,k,  -k,-k,k,  k,-k,k,        // v0-v1-v2-v3
        k,k,k,  k,-k,k,  k,-k,-k,  k,k,-k,        // v0-v3-v4-v5
        k,k,k,  k,k,-k,  -k,k,-k,  -k,k,k,        // v0-v5-v6-vk TOP
        -k,k,k,  -k,k,-k,  -k,-k,-k,  -k,-k,k,    // vk-v6-v7-v2
        -k,-k,-k,  k,-k,-k,  k,-k,k,  -k,-k,k,    // v7-v4-v3-v2
        k,-k,-k,  -k,-k,-k,  -k,k,-k,  k,k,-k};   // v4-v7-v6-v5
    
    // normal array4
    static GLfloat normals[] =
        {0,0,1,  0,0,1,  0,0,1,  0,0,1,             // v0-v1-v2-v3
        1,0,0,  1,0,0,  1,0,0, 1,0,0,              // v0-v3-v4-v5
        0,1,0,  0,1,0,  0,1,0, 0,1,0,              // v0-v5-v6-v1 TOP
        -1,0,0,  -1,0,0, -1,0,0,  -1,0,0,          // v1-v6-v7-v2
        0,-1,0,  0,-1,0,  0,-1,0,  0,-1,0,         // v7-v4-v3-v2
        0,0,-1,  0,0,-1,  0,0,-1,  0,0,-1};        // v4-v7-v6-v5
    
    // color array
    static GLfloat colors[] =
        {1,1,1,  1,1,0,  1,0,0,  1,0,1,              // v0-v1-v2-v3
        1,1,1,  1,0,1,  0,0,1,  0,1,1,              // v0-v3-v4-v5
        0,1,0,  1,1,1,  1,1,1,  1,1,1,              // v0-v5-v6-v1 TOP
        1,1,0,  0,1,0,  0,0,0,  1,0,0,              // v1-v6-v7-v2
        0,0,0,  0,0,1,  1,0,1,  1,0,0,              // v7-v4-v3-v2
        0,0,1,  0,0,0,  0,1,0,  0,1,1};             // v4-v7-v6-v5
    
    // index array of vertex array for glDrawElements()
    // Notice the indices are listed straight from beginning to end as exactly
    // same order of vertex array without hopping, because of different normals at
    // a shared vertex. For this case, glDrawArrays() and glDrawElements() have no
    // difference.s
    static GLubyte indices[] = {0,1,2,3,
        4,5,6,7,
        8,9,10,11,
        12,13,14,15,
        16,17,18,19,
        20,21,22,23};

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
    GetError();
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY); 
}

void HUD::RenderIcosahedron()
{
    // This is the same result as using Vertex3D, just faster to type and
    // can be made const this way
    static const Vec3 vertices[]= {
        {0, -0.525731, 0.850651},             // vertices[0]
        {0.850651, 0, 0.525731},              // vertices[1]
        {0.850651, 0, -0.525731},             // vertices[2]
        {-0.850651, 0, -0.525731},            // vertices[3]
        {-0.850651, 0, 0.525731},             // vertices[4]
        {-0.525731, 0.850651, 0},             // vertices[5]
        {0.525731, 0.850651, 0},              // vertices[6]
        {0.525731, -0.850651, 0},             // vertices[7]
        {-0.525731, -0.850651, 0},            // vertices[8]
        {0, -0.525731, -0.850651},            // vertices[9]
        {0, 0.525731, -0.850651},             // vertices[10]
        {0, 0.525731, 0.850651}               // vertices[11]
    };
    
    static const Vec4 colors2[] = {
        {1.0, 0.0, 0.0, 1.0},
        {1.0, 0.5, 0.0, 1.0},
        {1.0, 1.0, 0.0, 1.0},
        {0.5, 1.0, 0.0, 1.0},
        {0.0, 1.0, 0.0, 1.0},
        {0.0, 1.0, 0.5, 1.0},
        {0.0, 1.0, 1.0, 1.0},
        {0.0, 0.5, 1.0, 1.0},
        {0.0, 0.0, 1.0, 1.0},
        {0.5, 0.0, 1.0, 1.0},
        {1.0, 0.0, 1.0, 1.0},
        {1.0, 0.0, 0.5, 1.0}
    };
    
    static const GLubyte icosahedronFaces[] = {
        1, 2, 6,
        1, 7, 2,
        3, 4, 5,
        4, 3, 8,
        6, 5, 11,
        5, 6, 10,
        9, 10, 2,
        10, 9, 3,
        7, 8, 9,
        8, 7, 0,
        11, 0, 1,
        0, 11, 4,
        6, 2, 10,
        1, 6, 11,
        3, 5, 10,
        5, 4, 11,
        2, 7, 9,
        7, 1, 0,
        3, 9, 8,
        4, 8, 0,
    };
    
    static const Vec3 normals[] = {
        {0.000000, -0.417775, 0.675974},
        {0.675973, 0.000000, 0.417775},
        {0.675973, -0.000000, -0.417775},
        {-0.675973, 0.000000, -0.417775},
        {-0.675973, -0.000000, 0.417775},
        {-0.417775, 0.675974, 0.000000},
        {0.417775, 0.675973, -0.000000},
        {0.417775, -0.675974, 0.000000},
        {-0.417775, -0.675974, 0.000000},
        {0.000000, -0.417775, -0.675973},
        {0.000000, 0.417775, -0.675974},
        {0.000000, 0.417775, 0.675973},
    };
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(4, GL_FLOAT, 0, colors2);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_BYTE, icosahedronFaces);
    GetError();
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void HUD::RenderDesktop()
{
    GLfloat a = 10;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
        glColor4f(0.0, 1.0, 0.0, 0.0);
        glVertex3f(-a,  0.0,    a);
        glVertex3f(a,   0.0,    a);
        glVertex3f(a,   0.0,    -a);
        glVertex3f(-a,  0.0,    -a);
    glEnd();
    glDisable(GL_BLEND);
}

}