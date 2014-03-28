
#pragma once

namespace ftr {

class Rect
{
public:
    //glm::mat2
    
    glm::vec2 mOrigin;
    glm::vec2 mSize;
    
    Rect() : mOrigin(glm::vec2()), mSize(glm::vec2()) {}
    Rect(const glm::vec2 origin, const glm::vec2 size) : mOrigin(origin), mSize(size) {}
    Rect(const float x, const float y, const float width, const float fHeight)
    : mOrigin(glm::vec2(x, y)), mSize(glm::vec2(width, fHeight)) {}
};

}