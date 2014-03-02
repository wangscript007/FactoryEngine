//
//  PointNodeIterator.h
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 19/01/14.
//  Copyright (c) 2014 Dimention. All rights reserved.
//

#pragma once

#include <Model/Edge.h>

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
    
inline PointNodeIterator& PointNodeIterator::operator ++ ()
{
    if (mEdge == NULL) {
        mEdge = mPointNode.mEdge;
    } else {
        for (int i = 0; i < 2; i++) {
            if ((mEdge->originNode() != &mPointNode) && mEdge->next()) {
                mEdge = mEdge->next();
            } else {
                mEdge = mEdge->twin();
            }
        }
        if (mEdge == mPointNode.mEdge) {
            mEdge = NULL;
        }
    }
    return *this;
}
    
inline PointNodeIterator& PointNodeIterator::operator -- ()
{
    if (mEdge == mPointNode.mEdge) {
        mEdge = NULL;
    } else {
        if (mEdge == NULL) {
            Edge* beginEdge = mPointNode.mEdge->prev();
            if (beginEdge) {
                mEdge = beginEdge->twin();
            }
        } else {
            for (int i = 0; i < 2; i++) {
                if ((mEdge->originNode() == &mPointNode) && mEdge->prev()) {
                    mEdge = mEdge->prev();
                } else {
                    mEdge = mEdge->twin();
                }
            }
        }
    }
    
    return *this;
}

    
}

