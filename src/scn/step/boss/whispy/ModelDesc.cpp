#include "scn/step/boss/whispy/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "EyeJ",
    "MouthJ",
    "MasterJ",
    "CB1LegSJ",
    "CA1SJ",
    "CA2SJ",
    "CA3SJ",
    "CA4HeadSJ",
    "FaceRotJ",
    "MouthRotJ",
    "LA1ShoulderJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "WaitBig", 0 },
    { "WaitNoFace", 0 },
    { "Appear", 0 },
    { "Menace", 0 },
    { "Grow", 0 },
    { "ShootStart", 0 },
    { "BigShootStart", 0 },
    { "ShootStartWait", 0 },
    { "BigShootStartWait", 0 },
    { "ShootLoop", 0 },
    { "BigShootLoop", 0 },
    { "ShootEnd", 0 },
    { "BigShootEnd", 0 },
    { "FallApple", 0 },
    { "FallEnemyStart", 0 },
    { "BigFallEnemyStart", 0 },
    { "FallEnemyWait", 0 },
    { "BigFallEnemyWait", 0 },
    { "FallEnemy", 0 },
    { "BigFallEnemy", 0 },
    { "Damage", 0 },
    { "DamageL", 0 },
    { "VacuumBigStart", 0 },
    { "VacuumBig", 0 },
    { "VacuumBigEnd", 0 },
    { "Anemic", 0 },
    { "AnemicEnd", 0 },
    { "Death", 0 },
    { "DeathWait", 0 },
    { "Catch", 0 },
    { "Chewing", 0 },
    { "Vomit", 0 },
    { "ShakeNoFace", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "Whispy.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 12, 0, 0 },
    { "Whispy.AnimScript.ShootStart.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.ShootStartWait.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.ShootLoop.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.ShootEnd.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.FallApple.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.FallEnemy.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.FallEnemy2.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 22, 0, 0, 0 },
    { "Whispy.AnimScript.Grow.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.VacuumStart.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.Vacuum.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.VacuumEnd.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.Capture.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.Chewing.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.Vomit.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.AppearLong.Exec", 0, 0, 0, 0 },
    { "Whispy.AnimScript.RootAttack.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    return boss::ModelDesc::CreateTmpl<1, 0, 0>(isExtra ? "step/chara/enemy/whispy/ModelEx" : "step/chara/enemy/whispy/Model",
        "step/chara/enemy/whispy/Motion", "Whispy", 12, T_NODE_NAMES, 34, T_ANIM_ENTRIES, 24,
        T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::boss::whispy
