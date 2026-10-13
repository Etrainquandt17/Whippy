#ifndef SCN_STEP_HERO_VACUUMSOUNDCTRL_H
#define SCN_STEP_HERO_VACUUMSOUNDCTRL_H

#include "hel/common/MutableArray.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace hero {

class Hero;

}}}  // namespace scn::step::hero

namespace hel {
namespace common {

// TODO: in the game Array::operator[] is a function of its own (it calls a range check), and
// hel/common/Array.h defines it inline. Until that header changes, this instantiation declares it.
template <>
class Array<util::ObjRefHandle<scn::step::hero::Hero>, 4> {
public:
    util::ObjRefHandle<scn::step::hero::Hero>& operator[](u32 index);

private:
    util::ObjRefHandle<scn::step::hero::Hero> mArray[4];
};

}}  // namespace hel::common

namespace scn {
namespace step {
namespace hero {

class VacuumSoundCtrl {
public:
    VacuumSoundCtrl();
    ~VacuumSoundCtrl();

    void registerObj(util::ObjRefHandle<Hero> obj);
    void unregisterObj(util::ObjRefHandle<Hero> obj);
    void update();

private:
    void updateVolume();
    void cleanup();

    hel::common::MutableArray<util::ObjRefHandle<Hero>, 4> mObjs;
};

}}}  // namespace scn::step::hero

#endif
