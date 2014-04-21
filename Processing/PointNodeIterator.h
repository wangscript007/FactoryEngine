
#pragma once

#include <Graph/Edge.h>

namespace ftr {

class PointNode;

class PointNodeIterator
{
public:
    PointNodeIterator(const PointNode& pointNode, Edge* start)
    : mPointNode(pointNode), mEdge(start) {};

    virtual ~PointNodeIterator() {}
    
    PointNodeIterator& operator = (const PointNodeIterator& other) {
        mEdge = other.mEdge;
        return *this;
    }
    
    PointNodeIterator& operator ++ ();
    PointNodeIterator& operator -- ();
    
    ftr::Edge* operator * ()
    { return mEdge; };
    bool operator == (const PointNodeIterator& other) const
    { return mEdge == other.mEdge; }
    bool operator != (const PointNodeIterator& other) const
    { return !(*this == other); }
    
private:
    Edge* mEdge;
    const PointNode& mPointNode;
};
    
}

