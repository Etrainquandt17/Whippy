#ifndef SCN_STEP_OCOLL_HITRESISTLV_H
#define SCN_STEP_OCOLL_HITRESISTLV_H

namespace scn {
namespace step {
namespace ocoll {

// How a body stands up to the attacks that hit it. Each attack decides what a level means for it; so far the readers
// are the thrown weapons and a few of the hero's attacks.
enum HitResistLv {
    HIT_RESIST_LV_NONE,       // leaf cutters fly on through
    HIT_RESIST_LV_1,          // TODO: set by PopFlower and buraburarope; nothing decompiled tells it from NORMAL
    HIT_RESIST_LV_NORMAL,     // every body to begin with
    HIT_RESIST_LV_WALL,       // spears and needles stick in, dash and glide attacks rebound as off a wall
    HIT_RESIST_LV_REPEL,      // needles, kunai and star shots are repelled
    HIT_RESIST_LV_PUSH_BACK,  // also no hit stop for thrown weapons, and the ice breath pushes its user back
    HIT_RESIST_LV_REFLECT,    // spears and star shots bounce off too
};

}}}  // namespace scn::step::ocoll

#endif
