#ifndef G3D_RESFILE_H
#define G3D_RESFILE_H

#include "file/FileAccessor.h"
#include "g3d/ResFileAccessor.h"

namespace g3d {

class ResFile {
public:
    ResFile(const char* name, bool);
    ~ResFile();

    ResFileAccessor accessor() const;

private:
    file::FileAccessor mFileAccessor;
    ResFileAccessor mResAccessor;
};

}

#endif
