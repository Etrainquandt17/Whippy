#ifndef SCN_STEP_ENEMY_ELEC_STATEMOVE_H
#define SCN_STEP_ENEMY_ELEC_STATEMOVE_H

#include "hel/math/Vector2.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace elec {

class StateMove : public StateBase {
public:
    StateMove(Enemy* enemy);
    virtual ~StateMove();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool isInitCWR() const = 0;

    void setRot(bool isCWR);

private:
    bool isWall(hel::math::Vector2 pos);
    f32 xy2roundDist(int x, int y, hel::math::Vector2 pos) const;
    hel::math::Vector2 roundDist2xy(int x, int y, f32 dist) const;
    f32 roundDistNormalize(f32 dist) const;
    f32 dir() const;

    bool mIsCWR;
    int mGridX;
    int mGridY;
    int mFrame;
    f32 mSpeed;
};

class StateMoveCWR : public StateMove {
public:
    StateMoveCWR(Enemy* enemy) : StateMove(enemy) { setRot(true); }
    virtual bool isInitCWR() const { return true; }
};

class StateMoveCCW : public StateMove {
public:
    StateMoveCCW(Enemy* enemy) : StateMove(enemy) { setRot(false); }
    virtual bool isInitCWR() const { return false; }
};

}
}
}
}

#endif
