#ifndef G3D_RESFILEACCESSOR_H
#define G3D_RESFILEACCESSOR_H

#include "nw4r/g3d/res/g3d_resfile.h"
#include "nw4r/g3d/res/g3d_resmdl.h"

namespace g3d {

class ResFileAccessor {
public:
    ResFileAccessor();
    ResFileAccessor(const nw4r::g3d::ResFile& resFile);

    bool isValid() const;
    bool bind(const ResFileAccessor& other, bool) const;
    nw4r::g3d::ResMdl model(const char* name) const;

private:
    nw4r::g3d::ResFile mResFile;
};

}  // namespace g3d

#endif
