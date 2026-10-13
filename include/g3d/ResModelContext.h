#ifndef G3D_RESMODELCONTEXT_H
#define G3D_RESMODELCONTEXT_H

#include "g3d/ResFileAccessor.h"
#include "hel/common/FixedString.h"
#include "types.h"

namespace g3d {

class ResModelContext {
public:
    static const char* DefaultEntryName();

    ResModelContext(const ResFileAccessor& resFile, const char* name);

    const ResFileAccessor& resFile() const { return mResFile; }
    const char* name() const { return mName; }

private:
    ResFileAccessor mResFile;
    hel::common::FixedString<40> mName;
};

}

#endif
