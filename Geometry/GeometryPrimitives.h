

#pragma once


namespace ftr {

enum Axis { kAxisX, kAxisY, kAxisZ };

class Box
{
public:
    glm::vec3 mCenter;
    glm::vec3 mHalfDimension;
    
    Box() : mCenter(glm::vec3()), mHalfDimension(glm::vec3()) {};
    Box(glm::vec3 center, glm::vec3 halfDimension) : mCenter(center), mHalfDimension(halfDimension) {};
    bool Contains(const glm::vec3& vec) const;
    bool Intersects(const Box& other) const;
    float Diagonal2() const;
    float Diagonal3() const;
};

inline bool Box::Contains(const glm::vec3& vec) const
{
    if (vec.x <= mCenter.x - mHalfDimension.x) return false;
    if (vec.x > mCenter.x + mHalfDimension.x) return false;
    
    if (vec.y <= mCenter.y - mHalfDimension.y) return false;
    if (vec.y > mCenter.y + mHalfDimension.y) return false;
    
    if (vec.z <= mCenter.z - mHalfDimension.z) return false;
    if (vec.z > mCenter.z + mHalfDimension.z) return false;
        
    return true;
}

inline bool Box::Intersects(const Box& other) const
{
    if (mCenter.x + mHalfDimension.x <= other.mCenter.x - other.mHalfDimension.x) return false;
    if (mCenter.x - mHalfDimension.x > other.mCenter.x + other.mHalfDimension.x) return false;
    
    if (mCenter.y + mHalfDimension.y <= other.mCenter.y - other.mHalfDimension.y) return false;
    if (mCenter.y - mHalfDimension.y > other.mCenter.y + other.mHalfDimension.y) return false;
    
    if (mCenter.z + mHalfDimension.z <= other.mCenter.z - other.mHalfDimension.z) return false;
    if (mCenter.z - mHalfDimension.z > other.mCenter.z + other.mHalfDimension.z) return false;

    return true; // boxes overlap
}
    
    
inline float Box::Diagonal2() const
{
    float a = mHalfDimension.x*2;
    return sqrtf(2*(a*a));
}

inline float Box::Diagonal3() const
{
    float a = mHalfDimension.x*2;
    float b = Diagonal2();
    return sqrtf((a*a)+(b*b));
}
    


class Sphere
{
public:
    glm::vec3 mCenter;
    float mRadius;
    Sphere(glm::vec3 center, float radius) : mCenter(center), mRadius(radius) {};
    bool Intersects(const Box& box) const;
    bool Containts(const glm::vec3& vec) const;
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
    return ftr::Box(mCenter, glm::vec3(mRadius, mRadius, mRadius));
}

inline bool Sphere::Containts(const glm::vec3& vec) const
{
    return  glm::length(mCenter - vec) < mRadius;
}


struct Rectangle3
{
    glm::vec3 mOrigin;
    glm::vec3 mA;
    glm::vec3 mB;
};
    
}


