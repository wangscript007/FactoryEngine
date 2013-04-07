
#pragma once

#include <Model/Node.h>

namespace Factory {

class ModelManager;
class Point;

class LineInteraction : public Node
{
public:
    LineInteraction(ModelManager& rModelManager);
    virtual ~LineInteraction() {}
    void Render();
    void Begin();
    void Step();
    void End();
    void SetStart(O5Vec3 vStart);
    void SetEnd(O5Vec3 vEnd);
    
    
private:
    ModelManager& m_rModelManager;
    O5Vec3 m_vStart;
    O5Vec3 m_vEnd;
    bool m_bActive;
    Point* m_pStartPoint;
    Point* m_pEndPoint;

};

}
