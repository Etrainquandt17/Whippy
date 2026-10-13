#ifndef SCN_STEP_ENEMY_LANDIASINGLE_HEADANGLECTRL_H
#define SCN_STEP_ENEMY_LANDIASINGLE_HEADANGLECTRL_H

#include "scn/step/enemy/landiasingle/NodeKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

class HeadAngleCtrl {
public:
    HeadAngleCtrl(Enemy& enemy);

    void update();
    void toValid();
    void toInvalid();

private:
    void setMtx(NodeKind kind, f32 angle);

    Enemy& mObj;
    f32 mAngleX;
    f32 mAngleY;
    bool mIsValid;
};

}}}}  // namespace scn::step::enemy::landiasingle

#endif
