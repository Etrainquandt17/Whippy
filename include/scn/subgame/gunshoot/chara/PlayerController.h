#ifndef SCN_SUBGAME_GUNSHOOT_CHARA_PLAYERCONTROLLER_H
#define SCN_SUBGAME_GUNSHOOT_CHARA_PLAYERCONTROLLER_H

#include "hel/common/AutoDeleteArray.h"
#include "nw4r/math/math_types.h"
#include "scn/subgame/common/view/Stage.h"
#include "scn/subgame/gunshoot/chara/Bullet.h"
#include "scn/subgame/gunshoot/chara/ICharaController.h"
#include "scn/subgame/gunshoot/chara/Player.h"
#include "scn/subgame/gunshoot/enemy/EnemyAccessor.h"
#include "scn/subgame/gunshoot/input/Accessor.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace chara {

class StageConstant;

class PlayerController : public ICharaController {
public:
    virtual ~PlayerController();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw() const;

    void shot(bool charged);
    void damage(bool);
    void initSoundLabel();
    void playSound(const char* name);
    void playSound(u32 label);
    bool isBulletFromGun() const;
    void updateAimDirection();
    void updateBullet();

private:
    common::view::Stage& mStage;
    const StageConstant& mStageConstant;
    enemy::EnemyAccessor mEnemy;
    u32 _10[3];
    input::Accessor mInput;
    Player mPlayer;
    int _28C;
    bool _290;
    bool _291;
    u32 _294[0x16];
    hel::common::AutoDeleteArray<Bullet, 8> mBullets;
    Bullet* _310;
    nw4r::math::VEC3 _314;
    nw4r::math::VEC3 _320;
    bool _32C;
    bool _32D;
    u32 mShotSoundLabel[2];
    u32 _338[2];
    u32 _340[2];
};

}
}
}
}

#endif
