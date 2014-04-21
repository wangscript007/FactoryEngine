
#pragma once

#include <Graph/Node.h>

namespace ftr {

class TestRectangle : public Node
{
public:
    virtual ~TestRectangle() {}
    void Render(Layer& layer);
private:
    RectanglePrimitive rectanglePrimitive;
};

}

