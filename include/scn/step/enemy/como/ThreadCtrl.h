#ifndef SCN_STEP_ENEMY_COMO_THREADCTRL_H
#define SCN_STEP_ENEMY_COMO_THREADCTRL_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/Weapon.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace como {

// TODO: ThreadCtrl.cpp is not written; the members past the first two are named after their offsets.
class ThreadCtrl {
public:
    ThreadCtrl(Enemy& enemy);

    void update();
    void setLength(f32 length);
    void cut(const hel::math::Vector3& pos);
    void cut();
    void setModelThreadLength(f32 length);
    bool checkCut();
    bool isCut() const;
    f32 getLength() const;
    f32 getMaxLength() const;

private:
    Enemy& mObj;
    f32 mLength;
    hel::math::Vector3 _8;
    bool _14;
    util::ObjRefHandle<weapon::Weapon> mThread;
};

}}}}  // namespace scn::step::enemy::como

#endif
