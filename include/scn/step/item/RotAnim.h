#ifndef SCN_STEP_ITEM_ROTANIM_H
#define SCN_STEP_ITEM_ROTANIM_H

#include "types.h"

namespace scn {
namespace step {
namespace item {

class Item;

class RotAnim {
public:
    enum SpeedKind {
        SPEED_KIND_SLOW,
        SPEED_KIND_MIDDLE,
        SPEED_KIND_FAST,
    };

    RotAnim(Item& item);

    void update();
    void setSpeed(SpeedKind kind);
    bool isEnable() const;
    void setIsEnable(bool isEnable);
    f32 currentSpeed() const;

private:
    Item& mObj;
    SpeedKind mSpeedKind;
    f32 mRot;
    bool mIsEnable;
};

}}}  // namespace scn::step::item

#endif
