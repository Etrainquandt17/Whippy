#include "msg/Project.h"

#include "hel/common/FixedStringIN.h"
#include "libms/projfile.h"

namespace msg {

Project::Project(mem::IAllocator& allocator, const char* name)
    : mFileLoader()
    , mProjectInfo(0) {
    mFileLoader.load(hel::common::FixedStringIN<char, 80>::FromFormat("msg/%s.msbp", name), allocator, false, 0);
    mProjectInfo = LMS_InitProject(mFileLoader.data().startAddress());
}

Project::~Project() {
    LMS_CloseProject(mProjectInfo);
    mProjectInfo = 0;
    mFileLoader.unload();
}

const wchar_t* Project::tagGroupName(u16 group) const {
    return LMS_GetTagGroupName(mProjectInfo, group);
}

const wchar_t* Project::tagName(u16 group, u16 tag) const {
    return LMS_GetTagName(mProjectInfo, group, tag);
}

const wchar_t* Project::listItemName(u16 group, u16 tag, u16 param, u16 item) const {
    return LMS_GetTagListItemName(mProjectInfo, group, tag, param, item);
}

}  // namespace msg
