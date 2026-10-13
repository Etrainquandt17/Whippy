#ifndef SCN_STEP_ENEMY_FLAMER_CUSTOM_H
#define SCN_STEP_ENEMY_FLAMER_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::flamer::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    void attack();
    bool isAttackEnd() const;
    void dead();
    bool isMove() const;
    void setIsMove(bool isMove);

private:
    s32 mAttackCount;
    bool mIsMove;
};

}
}
}
}

#endif
