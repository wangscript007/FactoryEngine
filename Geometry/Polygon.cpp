
#include <Geometry/Polygon.h>
#include <Geometry/Vector.h>
#include <Utils/Description.h>
#include <Geometry/Constants.h>
#include <External/poly2tri/poly2tri.h>
#include <Geometry/GeometryPrimitives.h>

namespace ftr {
    
Polygon::~Polygon()
{
    FT_DELETE_VECTOR(mTriangles);
}
    
void Polygon::Triangulate()
{
    FT_DELETE_VECTOR(mTriangles);
    
    if (mPoints.size() == 3) {
        mTriangles.reserve(1);
        mTriangles.push_back(new Triangle(mPoints));
        return;
    }
    
    glm::vec3 closestNormal = XYZClosestNormal();
    bool isXYZAlligned = Vector::IsParallel(SurfaceNormal(), closestNormal);
    
    Polygon rotatedPolygon = *this;
    glm::mat4 rotationMatrix;
    
    if (!isXYZAlligned) {
        rotationMatrix = RotationToSurfaceNormal(closestNormal);
        rotatedPolygon.Transform(rotationMatrix);
    }
    
    int componentIndex = 0;
    for (int i = 0; i < 3; ++i) {
        if (closestNormal[i] != 0) {
            componentIndex = i;
            break;
        }
    }
    float offset = rotatedPolygon[0][componentIndex];
    
//    for (auto &point : rotatedPolygon.mPoints) {
//        assert(offset - point[componentIndex] < 0.1f);
//    }

    
    std::vector<p2t::Point*> polyline;
    for (auto &polygonPoint : rotatedPolygon.mPoints) {
        glm::vec2 vec = Vec3WithoutComponent(polygonPoint, componentIndex);
        polyline.push_back(new p2t::Point(vec.x, vec.y));
    }
    
    p2t::CDT cdt(polyline);
    cdt.Triangulate();
    std::vector<p2t::Triangle*> triangles = cdt.GetTriangles();
    mTriangles.reserve(triangles.size());
    for (auto &triangle : triangles)
    {
        glm::vec3 points[3];
        for(int pi = 0; pi < 3; pi++)
        {
            p2t::Point* point = triangle->GetPoint(pi);
            glm::vec2 vec = glm::vec2(point->x, point->y);
            points[pi] = Vec2ByAppendingComponent(vec, offset, componentIndex);
        }
        mTriangles.push_back(new Triangle(points[0], points[1], points[2]));
    }
    
    if (!isXYZAlligned) {
        TransformTriangles(glm::inverse(rotationMatrix));
    }
    
    FT_DELETE_VECTOR(polyline);
}
    
glm::vec2 Polygon::Vec3WithoutComponent(const glm::vec3& vec, const int index)
{
    glm::vec2 result;
    for (int i = 0; i < kDimensionsCount; i++) {
        if (i < index) {
            result[i] = vec[i];
        } else if (i > index) {
            result[i-1] = vec[i];
        }
    }
    return result;
}
    
glm::vec3 Polygon::Vec2ByAppendingComponent(const glm::vec2& vec, float component, int index)
{
    glm::vec3 result;
    for (int i = 0; i < kDimensionsCount; i++) {
        if (i < index) {
            result[i] = vec[i];
        }
        else if (i == index) {
            result[i] = component;
        }
        else if (i > index) {
            result[i] = vec[i-1];
        }
    }
    return result;
}
    
void Polygon::TransformTriangles(const glm::mat4& tranformation)
{
    for (int i = 0; i < mTriangles.size(); ++i) {
        mTriangles[i]->Transform(tranformation);
    }
}
    
    
void Polygon::RotateToSurfaceNormal(const glm::vec3& targedNormal)
{
    Transform(RotationToSurfaceNormal(targedNormal));
}
    
glm::mat4 Polygon::RotationToSurfaceNormal(const glm::vec3& targedNormal)
{
    glm::vec3 surfaceNormal = SurfaceNormal();
    glm::vec3 rotationAxis  = glm::normalize(glm::cross(targedNormal, surfaceNormal));
    float rotationAngle     = glm::angle(targedNormal, surfaceNormal);
    
    return glm::rotate(-rotationAngle, rotationAxis);
}
    
    
glm::vec3 Polygon::XYZClosestNormal() const
{
    return Vector::XYZClosestAxis(SurfaceNormal());
}
    
    
glm::vec3 Polygon::SurfaceNormal() const
{
    assert(mPoints.size() > 2);
    Triangle triangle(mPoints[0],
                      mPoints[1],
                      mPoints[2]);
    glm::vec3 normal = triangle.SurfaceNormal();
    return normal;
}
    
glm::vec3 Polygon::IntersectionPoint(const Segment& segment) const
{
    assert(mTriangles.size() > 0);
    glm::vec3 point;
    for (const Triangle* triangle : mTriangles) {
        
        Segment::IntersectionSituation situation = segment.IntersectionWithTriangle(*triangle, point);
        assert(situation != Segment::kIntersectionSituationInvalid);
        if (situation == Segment::kIntersectionSituationInside) {
            break;
        }
    }
    return point;
}
    
int Polygon::DebugTrianglesMatchingPointsCount() const
{
    int matchingPointsCount = 0;
    for (auto &triangle : mTriangles) {
        for (int i = 0; i < 3; ++i) {
            for (const glm::vec3 &polygonPoint : mPoints) {
                const glm::vec3& trianglePoint = triangle->GetPoints()[i];
                if (glm::isNull(polygonPoint - trianglePoint, 0.01f)) {
                    matchingPointsCount++;
                }
            }
        }
    }
    return matchingPointsCount;
}
    
    
void Polygon::DebugPrint() const
{
    //std::cout << "Polygon \n";
    for (int i = 0; i < mPoints.size(); ++i) {
        //std::cout << Description::Described(mPoints[i]) << " ";
    }
}
    
void Polygon::DebugPrintTriangles() const
{
    //std::cout << "Triangles of polygon \n";
    std::vector<Triangle*> triangles = GetTriangles();
    for (int i = 0; i < triangles.size(); ++i) {
        //std::cout << triangles[i]->Description();
    }
}
    
}
