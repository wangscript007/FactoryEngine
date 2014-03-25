
#pragma once

#include <Geometry/GeometryPrimitives.h>
#include <External/poly2tri/poly2tri.h>
#include <Geometry/Polyline.h>
#include <Geometry/Triangle.h>


namespace ftr {

class Polygon
{
public:
    void AddPoint(const glm::vec3& point);
    const std::vector<Triangle*>& GetTriangles() const { return mTriangles; }
    
    void Triangulate();
    
    void Rotate(const glm::vec3& oilerAngle);
    void Translate(const  glm::vec3& offset);
    void Scale(const glm::vec3& offset);
    void Reset();
    
    
    
private:
    glm::mat4 RotationToSurfaceNormal(const glm::vec3& targedNormal);
    void Transform(const glm::mat4& tranformation);
    void TransformTriangles(const glm::mat4& tranformation);
    
    std::vector<Triangle*> mTriangles;
    
    glm::vec3 SurfaceNormal() const;
    glm::vec3 XYZClosestNormal() const;
    
    
    glm::mat4 mMatrix;
    glm::vec3 mLocal;
    glm::vec3 mWorld;
    
    Polyline mPolyline;
};

}