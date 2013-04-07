// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//


#include <FactoryEngine.h>

#pragma mark Making

FTVec2f FTMakeVec2f(GLfloat x, GLfloat y)
{
    FTVec2f vec;
    vec.x = x; vec.y = y;
    return vec;
}

FTVec2d FTMakeVec2d(GLdouble x, GLdouble y)
{
    FTVec2d vec;
    vec.x = x; vec.y = y;
    return vec;
}


FTVec3f FTMakeVec3f(GLfloat x, GLfloat y, GLfloat z)
{
    FTVec3f vec;
    vec.x = x; vec.y = y; vec.z = z;
    return vec;
}

FTVec3d FTMakeVec3d(GLdouble x, GLdouble y, GLdouble z)
{
    FTVec3d vec;
    vec.x = x; vec.y = y; vec.z = z;
    return vec;
}

FTRectf FTMakeRectf(const GLfloat originX, const GLfloat originY, const GLfloat sizeX, const GLfloat sizeY)
{
    FTRectf rect;
    rect.origin.x = originX;    rect.origin.y = originY;
    rect.size.x = sizeX;        rect.size.y = sizeY;
    return rect;
}

#pragma mark Operations

FTVec2f FTSumVec2f(const FTVec2f vecA, const FTVec2f vecB)
{
    return FTMakeVec2f(vecA.x + vecB.x, vecA.y + vecB.y);
}






