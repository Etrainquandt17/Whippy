#define NW4R_G3D_RESFILE_CONSTRUCTOR_INLINE
#include "g3d/ResFile.h"

#include "hel/common/FixedStringIN.h"

namespace g3d {

ResFile::ResFile(const char* name, bool arg)
    : mFileAccessor(hel::common::FixedStringIN<char, 80>::FromFormat("g3d/%s.brres.cmp", name), true)
    , mResAccessor() {
    if (mFileAccessor.isLoaded()) {
        nw4r::g3d::ResFile file(mFileAccessor.block().startAddress());
        file.CheckRevision();
        file.Init();
        mResAccessor = ResFileAccessor(file);
        if (!mResAccessor.bind(ResFileAccessor(), arg) && !arg) {
            mResAccessor = ResFileAccessor();
            return;
        }
    }
}

ResFile::~ResFile() {
    if (mResAccessor.isValid()) {
        nw4r::g3d::ResFile file(mFileAccessor.block().startAddress());
        file.Release();
        file.Terminate();
    }
}

ResFileAccessor ResFile::accessor() const {
    return mResAccessor;
}

}
