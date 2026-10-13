#ifndef SCN_STEP_ENEMY_AQUAROCK_STATEMOVE_H
#define SCN_STEP_ENEMY_AQUAROCK_STATEMOVE_H

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "scn/step/map/BinEnemyDirType.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace aquarock {

// TODO: names for the members that still carry their offset.
class StateMove : public StateBase {
public:
    struct RayCheckData {
        RayCheckData() {}

        hel::math::Vector2 _0;
        hel::math::Vector2 _8;
    };

    struct MapHitResult {
        MapHitResult() {}

        bool mIsHit;
        hel::math::Vector2 _4;
    };

    StateMove(Enemy* enemy);
    virtual ~StateMove();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    void mfReqBubbleEffect();
    void mfSetModelRotate();
    void mfShake();
    void mfSetModelVisible();
    f32 mfCheckRotate(f32 rot);
    f32 mfCheckRotate360(f32 rot);
    f32 mfGetRotByDirType(map::BinEnemyDirType dirType);
    map::BinEnemyDirType mfNormalToDirType(hel::math::Vector2 normal);
    map::BinEnemyDirType mfNormalToDirTypeNururi(hel::math::Vector2 normal);
    map::BinEnemyDirType mfNewDirType(map::BinEnemyDirType from, map::BinEnemyDirType to);
    f32 mfNewRotDir(map::BinEnemyDirType from, map::BinEnemyDirType to);
    RayCheckData mfGetRayCheckData(f32, hel::math::Vector2, f32);
    RayCheckData mfGetRayCheckData2(f32, f32, hel::math::Vector2, f32);
    MapHitResult mfMapCheckPoint(hel::math::Vector2, hel::math::Vector2);
    MapHitResult mfNururiHitCheck();
    void mfMapCheck();

private:
    u32 _8;
    bool _c;
    hel::math::Vector3 mPos;
    hel::math::Vector3 mPrevPos;
    f32 mSpeed;
    f32 mRot;
    f32 mRotSpeed;
    f32 _34;
    map::BinEnemyDirType mDirType;
    bool _3c;
    u32 _40;
    hel::math::Vector2 _44;
    u32 mShakeFrame;
    bool mIsShake;
};

}
}
}
}

#endif
