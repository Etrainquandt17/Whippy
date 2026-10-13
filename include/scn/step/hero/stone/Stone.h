#ifndef SCN_STEP_HERO_STONE_STONE_H
#define SCN_STEP_HERO_STONE_STONE_H

#include "g3d/ResFileAccessor.h"
#include "mem/AutoHeapExp.h"
#include "mem/MemBlock.h"
#include "scn/step/hero/AbilityBase.h"
#include "scn/step/hero/stone/Context.h"
#include "scn/step/hero/stone/GearNodeRandomChanger.h"
#include "types.h"
#include "util/PlacementNew.h"

namespace scn {
namespace step {
namespace hero {

class Gear;

namespace stone {

class Stone : public AbilityBase {
public:
    Stone(Component& component, Hero& hero);
    virtual ~Stone();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onStateEndCleanUp();

private:
    void stoneChangePrepare();
    void stoneBodyClear();
    Gear& gearHat();
    Gear& gearBody();
    Gear& gearHand();

    bool _C;
    u32 _10;
    GearNodeRandomChanger mNodeChanger;
    Context mContext;
    mem::AutoHeapExp mHeap;
    mem::MemBlock mBlock;
    util::PlacementNew<g3d::ResFileAccessor> mResFile;
};

}}}}  // namespace scn::step::hero::stone

#endif
