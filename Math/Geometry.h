

#pragma once

namespace ftr {

enum Axis { kAxisX, kAxisY, kAxisZ };

struct Box
{
    Vec3 mCenter;
    Vec3 mHalfDimention;
    
    Box() : mCenter(Vec3()), mHalfDimention(Vec3()) {};
    Box(Vec3 center, Vec3 halfDimension) : mCenter(center), mHalfDimention(halfDimension) {};
    bool Contains(const Vec3& vec) const;
    bool Intersects(const Box& other) const;
};

inline bool Box::Contains(const Vec3& vec) const
{
    if (vec.mX <= mCenter.mX - mHalfDimention.mX) return false;
    if (vec.mX > mCenter.mX + mHalfDimention.mX) return false;
    
    if (vec.mY <= mCenter.mY - mHalfDimention.mY) return false;
    if (vec.mY > mCenter.mY + mHalfDimention.mY) return false;
    
    if (vec.mZ <= mCenter.mZ - mHalfDimention.mZ) return false;
    if (vec.mZ > mCenter.mZ + mHalfDimention.mZ) return false;
        
    return true;
}

inline bool Box::Intersects(const Box& other) const
{
    if (mCenter.mX + mHalfDimention.mX <= other.mCenter.mX - other.mHalfDimention.mX) return false;
    if (mCenter.mX - mHalfDimention.mX > other.mCenter.mX + other.mHalfDimention.mX) return false;
    
    if (mCenter.mY + mHalfDimention.mY <= other.mCenter.mY - other.mHalfDimention.mY) return false;
    if (mCenter.mY - mHalfDimention.mY > other.mCenter.mY + other.mHalfDimention.mY) return false;
    
    if (mCenter.mZ + mHalfDimention.mZ <= other.mCenter.mZ - other.mHalfDimention.mZ) return false;
    if (mCenter.mZ - mHalfDimention.mZ > other.mCenter.mZ + other.mHalfDimention.mZ) return false;

    return true; // boxes overlap

}

struct Sphere
{
    Vec3 mCenter;
    float mRadius;
    Sphere(Vec3 center, float radius) : mCenter(center), mRadius(radius) {};
    bool Intersects(const Box& box) const;
    bool Containts(const Vec3& vec) const;
    Box Box() const;
};

inline bool Sphere::Intersects(const struct Box& box) const
{
    /*
    closest.x = box.leftx;
    elseif(sphere.center.x > box.rightx)
    closest.x = box.rightx;
    else
        closest.x = sphere.center.x;
    */
    return false;
}

inline Box Sphere::Box() const
{
    return ftr::Box(mCenter, Vec3(mRadius, mRadius, mRadius));
}

inline bool Sphere::Containts(const Vec3& vec) const
{
    return (mCenter - vec).Length() < mRadius;
}


struct Rectangle3
{
    Vec3 mOrigin;
    Vec3 mA;
    Vec3 mB;
};
    
}


