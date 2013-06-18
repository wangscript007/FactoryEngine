
#include <Math/Transformation.h>

namespace ftr {

Mat4 Transformation::Translate(const Vec3& motion)
{
    return Mat4(Vec4(1.0, 0.0f, 0.0f, 0.0f),
                  Vec4(0.0f, 1.0, 0.0f, 0.0f),
                  Vec4(0.0f, 0.0f, 1.0, 0.0f),
                  Vec4(motion.mX, motion.mY, motion.mZ, 1.0f)
                  );
}
    
Mat4 Transformation::RotateAroundAxis(float angle, const Vec3& axis)
{
    Vec3 normalized = axis;
    normalized.Normalize();
    Mat4 m;
    float a = angle * M_PI / 180.0; // convert to radians
	float s = sin(a);
	float c = cos(a);
	float t = 1.0 - c;
    float x = normalized.mX;
    float y = normalized.mY;
    float z = normalized.mZ;
	float tx = t * x;
	float ty = t * y;
	float tz = t * z;
	
	float sz = s * z;
	float sy = s * y;
	float sx = s * x;
	
	m.mX[0]  = tx * x + c;
	m.mX[1]  = tx * y + sz;
	m.mX[2]  = tx * z - sy;
	m.mX[3]  = 0;
    
	m.mY[0]  = tx * y - sz;
	m.mY[1]  = ty * y + c;
	m.mY[2]  = ty * z + sx;
	m.mY[3]  = 0;
    
	m.mZ[0]  = tx * z + sy;
	m.mZ[1]  = ty * z - sx;
	m.mZ[2] = tz * z + c;
	m.mZ[3] = 0;
    
	m.mW[0] = 0;
	m.mW[1] = 0;
	m.mW[2] = 0;
	m.mW[3] = 1;
    return m;
}

Mat4 Transformation::Rotate(const Vec3& radians)
{
    Mat4 mx, my, mz;
    float cx = cosf(radians.mX);
    float sx = sinf(radians.mX);
    mx[1][1] = cx;
    mx[2][1] = sx;
    mx[1][2] = -sx;
    mx[2][2] = cx;
    
    float cy = cosf(radians.mY);
    float sy = sinf(radians.mY);
    my[0][0] = cy;
    my[2][0] = -sy;
    my[0][2] = sy;
    my[2][2] = cy;
    
    float cz = cosf(radians.mZ);
    float sz = sinf(radians.mZ);
    mz[0][0] = cz;
    mz[1][0] = sz;
    mz[0][1] = -sz;
    mz[1][1] = cz;
    
    return mx*my*mz;
}

Mat4 Transformation::Scale(const Vec3& scale)
{
    return Mat4(Vec4(scale.mX, 0.0f, 0.0f, 0.0f),
                Vec4(0.0f, scale.mY, 0.0f, 0.0f),
                Vec4(0.0f, 0.0f, scale.mZ, 0.0f),
                Vec4(0.0f, 0.0f, 0.0f, 1.0f));
}
    
    
Mat4 Transformation::Frustum(FTDouble left, FTDouble right, FTDouble bottom, FTDouble top,
                             FTDouble near, FTDouble far)
{
    Mat4 m = Mat4::Identity;
    m.mX[0] = 2.0f*near/(right - left);
    m.mY[1] = 2.0f*near/(top - bottom); //
    m.mX[2] = (right + left)/(right - left); // A
    m.mY[2] = (top + bottom)/(top - bottom); // B
    m.mZ[2] = -(far + near)/(far - near); // C
    m.mZ[3] = -(2.0f*far*near)/(far - near); // D
    m.mW[2] = -1.0f;
    m.mW[3] = 0.0f;
    return m;
}
    
Mat4 Transformation::Perspective(float fov, float ratio, float nearP, float farP)
{
    Mat4 m;
    float f = 1.0f / tan (fov * (M_PI / 360.0));
    m.mX[0] = f / ratio;
    m.mY[2] = f;
    m.mZ[2] = (farP + nearP) / (nearP - farP);
    m.mW[2] = (2.0f * farP * nearP) / (nearP - farP);
    m.mZ[3] = -1.0f;
    m.mW[3] = 0.0f;
    return m;
}
    
Mat4 Transformation::Ortho(FTDouble left, FTDouble right, FTDouble bottom, FTDouble top,
                                  FTDouble near, FTDouble far)
{
    Mat4 m;
    m.mX[0] = 2.0f/(right - left);
    m.mY[1] = 2.0f/(top - bottom);
    m.mZ[2] = -2.0/(far-near);
    
    m.mX[3] = -(right + left)/(right - left);
    m.mY[3] = -(top + bottom)/(top - bottom);
    m.mZ[3] = -(far + near)/(far - near);
    m.mW[3] = 1.0f;
    return m;
}
    
 Mat4 Transformation::LookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
{
    Mat4 m;
    Vec3 side, up2;
    Vec3 forward = center + eye;
    forward.Normalize();
    side = forward^up;
    side.Normalize();
    up2 = side^forward;
    up2.Normalize();
    
    m.mX[0] = side[0];
    m.mY[0] = side[1];
    m.mZ[0] = side[2];
    m.mW[0] = 0.0f;
    
    m.mX[1] = up2[0];
    m.mY[1] = up2[1];
    m.mZ[1] = up2[2];
    m.mW[1] = 0.0f;
    
    m.mX[2] = -forward[0];
    m.mY[2] = -forward[1];
    m.mZ[2] = -forward[2];
    m.mW[2] = 0.0f;
    
    m.mX[3] = 0;
    m.mY[3] = 0;
    m.mZ[3] = 0;
    m.mW[3] = 1.0f;
    return m*Translate(-eye);
}
    
Vec3 UnProject(const Vec3& window,
               const Mat4& modelview,
               const Mat4& projection,
               const Frame& viewport)
{
    Mat4 matrix = modelview*projection;
}

    /*
Vec3 UnProject(float winx, float winy, float winz, float *modelview, float *projection, int *viewport)
{
    //Transformation matrices
    float m[16], A[16];
    float in[4], out[4];
    //Calculation for inverting a matrix, compute projection x modelview
    //and store in A[16]
    MultiplyMatrices4by4OpenGL_FLOAT(A, projection, modelview);
    //Now compute the inverse of matrix A
    if(glhInvertMatrixf2(A, m)==0)
        return 0;
    //Transformation of normalized coordinates between -1 and 1
    in[0]=(winx-(float)viewport[0])/(float)viewport[2]*2.0-1.0;
    in[1]=(winy-(float)viewport[1])/(float)viewport[3]*2.0-1.0;
    in[2]=2.0*winz-1.0;
    in[3]=1.0;
    //Objects coordinates
    MultiplyMatrixByVector4by4OpenGL_FLOAT(out, m, in);
    if(out[3]==0.0)
        return 0;
    out[3]=1.0/out[3];
    objectCoordinate[0]=out[0]*out[3];
    objectCoordinate[1]=out[1]*out[3];
    objectCoordinate[2]=out[2]*out[3];
    return 1;
}
*/
    
}

