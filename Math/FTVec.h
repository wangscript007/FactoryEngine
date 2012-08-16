// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

typedef struct {
    GLfloat x;
    GLfloat y;
} FTVec2f;

typedef struct {
    GLdouble x;
    GLdouble y;
} FTVec2d;

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} FTVec3f;

typedef struct {
    GLdouble x;
    GLdouble y;
    GLdouble z;
} FTVec3d;

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat a;
} FTVecf4;

typedef struct {
    GLdouble x;
    GLdouble y;
    GLdouble z;
    GLdouble a;
} FTVecd4;

typedef struct
{
    FTVec2f origin;
    FTVec2f size;
} FTRectf;


extern FTVec2f FTMakeVec2f(GLfloat x, GLfloat y);
extern FTVec2d FTMakeVec2d(GLdouble x, GLdouble y);
extern FTVec3f FTMakeVec3f(GLfloat x, GLfloat y, GLfloat z);
extern FTVec3d FTMakeVec3d(GLdouble x, GLdouble y, GLdouble z);
extern FTRectf FTMakeRectf(const GLfloat originX, const GLfloat originY, const GLfloat sizeX, const GLfloat sizeY);

extern FTVec2f FTSumVec2f(const FTVec2f vecA, const FTVec2f vecB);

