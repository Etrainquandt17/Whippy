#ifndef SCN_STEP_WEAPON_MAHOROALASER_CUSTOM_H
#define SCN_STEP_WEAPON_MAHOROALASER_CUSTOM_H

#include "hel/common/Array.h"
#include "hel/geo/Rect.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/hero/CaptureHeroAttacker.h"
#include "scn/step/weapon/CustomBase.h"
#include "types.h"
#include "util/ObjRefHandle.h"
#include "util/PlacementNew.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroalaser {

class Custom;

}}}}  // namespace scn::step::weapon::mahoroalaser

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::mahoroalaser::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace mahoroalaser {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();
    virtual void onDead();

    void start(u32 readyFrame, u32 mainFrame);
    const hel::math::Vector3& startPos() const;
    const hel::math::Vector3& endPos() const;
    void setStartPos(const hel::math::Vector3& pos);
    void setEndPos(const hel::math::Vector3& pos);
    f32 scale() const;
    void setScale(f32 scale);
    bool isStartEdge() const;
    void setIsStartEdge(bool isStartEdge);
    bool isEndEdge() const;
    void setIsEndEdge(bool isEndEdge);
    void setMoveLimitRect(const hel::geo::Rect& rect);
    bool isMoveLimitRectValid() const;
    hel::geo::Rect getMoveLimitRect() const;
    bool isStartRequested() const;
    u32 getReadyFrame() const;
    u32 getMainFrame() const;
    void chkCapture();
    void startCapture();
    void endCapture();
    void clearCapture();
    void generateWarpHoleStartPos();
    void generateWarpHoleEndPos();
    void releaseWarpHole();
    void reqFlashWarpHoleStartPos();
    void reqFlashWarpHoleEndPos();
    util::ObjRefHandle<Weapon> generateWarpHole(const hel::math::Vector2& pos, const hel::math::Vector2& targetPos);
    void setupLocation();

private:
    hel::common::Array<util::PlacementNew<hero::CaptureHeroAttacker>, 4> mAttackers;
    util::ObjRefHandle<Weapon> mWarpHoleStart;
    util::ObjRefHandle<Weapon> mWarpHoleEnd;
    bool mIsStartRequested;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mEndPos;
    u32 mReadyFrame;
    u32 mMainFrame;
    f32 mScale;
    bool mIsStartEdge;
    bool mIsEndEdge;
    bool mIsMoveLimitRectValid;
    hel::geo::Rect mMoveLimitRect;
};

}}}}  // namespace scn::step::weapon::mahoroalaser

#endif
