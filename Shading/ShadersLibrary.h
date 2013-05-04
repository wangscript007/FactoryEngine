
#pragma once

namespace ftr {
    
class ShadersLibrary
{
public:
    typedef std::map<std::string, std::string> SourceMap;
    
    void Load();
    void Add(const std::string& name, const std::string& source);
    virtual ~ShadersLibrary() {}
    
private:
    SourceMap mSourceMap;
};

}

