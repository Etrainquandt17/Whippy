#ifndef SCN_STEP_DEBUG_OBJINFOREPOS_H
#define SCN_STEP_DEBUG_OBJINFOREPOS_H

#include "hel/common/MutableArray.h"

namespace scn {
namespace step {
namespace debug {

class IObjInfoImpl;

class ObjInfoRepos {
public:
    ObjInfoRepos();
    ~ObjInfoRepos();

    void registerObj(const IObjInfoImpl& obj);
    void unregisterObj(const IObjInfoImpl& obj);

private:
    hel::common::MutableArray<const IObjInfoImpl*, 64> mObjs;
};

}
}
}

#endif
