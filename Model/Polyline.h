
#pragma once

#include <Model/Node.h>
#include <Model/Point.h>

namespace ftr {

class Polyline : Model
{
public:
    typedef std::vector<Point*>  TPoinsVector;
    virtual ~Polyline() {}
    
private:
    TPoinsVector mPointsVector;
};
    
}

