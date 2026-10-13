#ifndef SCN_STEP_INFO_HEROSTATUSICON_H
#define SCN_STEP_INFO_HEROSTATUSICON_H

#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "mem/AutoHeapExp.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/Kind.h"
#include "types.h"
#include "util/PlacementNew.h"

namespace scn {
namespace step {
namespace info {

class HeroStatusIcon {
public:
    HeroStatusIcon(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, hero::Kind kind);
    ~HeroStatusIcon();

    void setParent(const lyt::PaneAccessor& parent);
    void changeIcon(hero::AbilityKind kind);
    void updateFrame();
    void startWaitAnim();
    void startDamageAnim();
    void startCureAnim();
    void startDeadAnim();
    void startPinchAnim();
    void stopPinchAnim();
    void startGetAbilityAnim();
    bool isAnimEnd() const;
    f32 animFrame() const;
    void setAnimFrame(f32 frame);

private:
    void disposeIcon();
    void createIcon(hero::AbilityKind kind);

    mem::AutoHeapExp mHeap;
    lyt::Layout _60;
    util::PlacementNew<lyt::Layout> _1F0;
    util::PlacementNew<lyt::Layout> _384;
    lyt::Layout _518;
    lyt::Layout* _6A8;
    lyt::PaneAccessor _6AC;
    hero::Kind _6C0;
};

}
}
}

#endif
