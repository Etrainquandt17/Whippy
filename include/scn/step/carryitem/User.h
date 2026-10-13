#ifndef SCN_STEP_CARRYITEM_USER_H
#define SCN_STEP_CARRYITEM_USER_H

#include "hel/math/Vector2.h"

namespace scn {
namespace step {
namespace carryitem {

class User {
public:
    bool chkCollide(const hel::math::Vector2& pos);
    void clearTargetItem();
    bool isItemExist() const;
    int targetItemKind() const;
    int targetItemUseCount() const;
    void setIsValid(bool isValid);
    // TODO: names; the u32 at 0x48 is what a throw state counts while the button is held.
    void set_48(u32 value) { reinterpret_cast<u32*>(this)[0x48 / 4] = value; }
    void set_4C(u32 value) { reinterpret_cast<u32*>(this)[0x4C / 4] = value; }
    void setIsWalk(bool isWalk) { reinterpret_cast<bool*>(this)[0x42] = isWalk; }
    void setIsRun(bool isRun) { reinterpret_cast<bool*>(this)[0x43] = isRun; }
};

}}}  // namespace scn::step::carryitem

#endif
