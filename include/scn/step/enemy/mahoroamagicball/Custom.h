#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_CUSTOM_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

}
namespace enemy {
namespace mahoroamagicball {

// TODO: members.
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    util::ObjRefHandle<boss::Boss> owner();
    void clearOwner();
    bool isOwnerAlive() const;
    bool isPhase2nd() const;

private:
    // TODO: members.
    u32 _8[4];
};

}
}
}
}

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::mahoroamagicball::Custom>();

}
}

#endif
