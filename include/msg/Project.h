#ifndef MSG_PROJECT_H
#define MSG_PROJECT_H

#include "file/FileLoader.h"
#include "types.h"

struct ProjectInfo;

namespace msg {

class Project {
public:
    Project(mem::IAllocator& allocator, const char* name);
    ~Project();

    const wchar_t* tagGroupName(u16 group) const;
    const wchar_t* tagName(u16 group, u16 tag) const;
    const wchar_t* listItemName(u16 group, u16 tag, u16 param, u16 item) const;

private:
    file::FileLoader mFileLoader;
    ProjectInfo* mProjectInfo;
};

}

#endif
