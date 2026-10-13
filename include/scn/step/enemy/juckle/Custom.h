#ifndef SCN_STEP_ENEMY_JUCKLE_CUSTOM_H
#define SCN_STEP_ENEMY_JUCKLE_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "scn/step/map/BinEnemyDirType.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace juckle {

class Custom;

}}}}  // namespace scn::step::enemy::juckle

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::juckle::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace juckle {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onHitPointIsZero();
    virtual void onCaptured();

    f32 VectorRot(map::BinEnemyDirType dirType);
    bool getFollowFlag();
    void onFollowFlag();
    bool myDir() const;
    f32 myAnger() const;
    void setAnger(f32 anger);
    f32 getViewVectorRot();
    f32 playerAnger();
    bool isPlayerInArea();

private:
    u32 _8;
    bool mFollowFlag;
    f32 mAnger;
    f32 mViewVectorRot;
    bool mDir;
};

}}}}  // namespace scn::step::enemy::juckle

#endif
