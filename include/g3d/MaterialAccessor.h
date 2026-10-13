#ifndef G3D_MATERIALACCESSOR_H
#define G3D_MATERIALACCESSOR_H

#include "types.h"

namespace hel {
namespace math {
class Matrix34;
}
}

namespace g3d {

class MaterialAccessor {
public:
    void texSRTSetEffectMtx(u32 index, const hel::math::Matrix34& mtx) const;
    void texSRTEndEdit() const;

private:
    // TODO: the size is a guess from the one stack frame that holds one.
    u32 _0[0x38 / 4];
};

}

#endif
