
#include <Geometry/Polygon.h>
#include <Geometry/Vector.h>
#include <Utils/Description.h>

namespace ftr {
        
void Polygon::Triangulate()
{
    glm::vec3 closestNormal = XYZClosestNormal();
    
    bool shouldRotate = !Vector::IsParallel(SurfaceNormal(), closestNormal);
    
    Polygon rotatedPolygon = *this;
    glm::mat4 rotationMatrix;
    if (shouldRotate) {
        rotationMatrix = RotationToSurfaceNormal(closestNormal);
        rotatedPolygon.Transform(rotationMatrix);
    }
    
    int dimensionsToUse[2];
    int dim = 0;
    for (int i = 0; i < 3; i++) {
        if (closestNormal[i] == 0) {
            dimensionsToUse[dim] = i;
            dim++;
        }
    }
    
    std::vector<p2t::Point*> polyline;
    for (int i = 0; i < rotatedPolygon.mPoints.size(); i++) {
        glm::vec3 polygonPoint = rotatedPolygon[i];
        int x = polygonPoint[dimensionsToUse[0]];
        int y = polygonPoint[dimensionsToUse[1]];
        std::cout << "x: " << x << " y: " << y << std::endl;
        polyline.push_back(new p2t::Point(x, y));
    }
    
    p2t::CDT *cdt = new p2t::CDT(polyline);
    cdt->Triangulate();
    std::vector<p2t::Triangle*> triangles = cdt->GetTriangles();
    
    for (int ti = 0; ti < triangles.size(); ++ti)
    {
        p2t::Triangle* p2Triangle = triangles[ti];
        glm::vec3 points[3];
        
        for(int pi = 0; pi < 3; pi++)
        {
            int dim = 0;
            for (int di = 0; di < 3; ++di)
            {
                if (closestNormal[di] == 0) {
                    if (dim == 0) {
                        points[pi][di] = p2Triangle->GetPoint(pi)->x;
                    } else {
                        points[pi][di] = p2Triangle->GetPoint(pi)->y;
                    }
                    dim++;
                }
            }
        }
        mTriangles.push_back(new Triangle(points[0], points[1], points[2]));
    }
    
    if (shouldRotate) {
        TransformTriangles(glm::inverse(rotationMatrix));
    }
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
    glm::vec3 rotationAxis = glm::normalize(glm::cross(targedNormal, surfaceNormal));
    float rotationAngle = glm::angle(targedNormal, surfaceNormal);
    
    std::cout << "Rotatation angle: " << rotationAngle << " around: " << Description::Described(rotationAxis) << std::endl;
    
    return glm::rotate(rotationAngle, rotationAxis);
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
    
void Polygon::DebugPrint() const
{
    std::cout << "Polygon \n";
    for (int i = 0; i < mPoints.size(); ++i) {
        std::cout << Description::Described(mPoints[i]) << " ";
    }
}
    
void Polygon::DebugPrintTriangles() const
{
    std::cout << "Triangles of polygon \n";
    std::vector<Triangle*> triangles = GetTriangles();
    for (int i = 0; i < triangles.size(); ++i) {
        std::cout << triangles[i]->Description();
    }
}
    
}
