#include "scn/step/gimmick/cutropestep/CutRopeStep.h"

#include "g3d/CharaModelContext.h"
#include "g3d/ModelBufferOption.h"
#include "g3d/ModelContext.h"
#include "g3d/ResModelContext.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/map/MemManager.h"

namespace scn {
namespace step {
namespace gimmick {
namespace cutropestep {

namespace {

// TODO: define. With `flip` the matrix is also turned 180 degrees around Z.
hel::math::Matrix34 GetPosMtx(const hel::math::Vector3& pos, bool flip);

}

#define MF_FUNCTION __ct__Q63scn4step7gimmick11cutropestep11CutRopeStep8RestRopeFRQ53scn4step7gimmick11cutropestep11CutRopeStepUl
CutRopeStep::RestRope::RestRope(CutRopeStep& owner, u32 index)
    : mOwner(owner)
    , _4(owner.ropeLength() - index)
    , _8(owner.pos().x, owner.pos().y + owner.ropeLength() + 1.0f)
    , _10(g3d::ModelContext(g3d::ResModelContext(owner.resFile(), "TopL2"), g3d::ModelBufferOption(), 0, g3d::CharaModelContext::DefaultNumView(),
                            owner.comp().mapMemManager().allocator(), false))
    , _1BC() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 limit;
    u32 last;

    hel::math::Vector3 pos(_8.x, _8.y - (f32)_4, mOwner.mParam.obj()._0);
    asm {
        bl      after1
        opword  MF_WORD(0x12C)
        opword  0x9928CD13
    after1:
        mflr    r16
        lwz     r23, 0x0(r16)
        stw     r23, expected
    }
    hash = 0xC5;
    asm {
        bl      after2
        opword  0x183F7380
        opword  0xE0F3A880
        opword  MF_WORD(0x150)
        opword  MF_WORD(0x154)
        opword  0x3696C601
    after2:
        mflr    r19
        lwz     r15, 0x8(r19)
        lwz     r21, 0xc(r19)
        add     r21, r15, r21
        stw     r15, start
        stw     r21, end
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    for (; i != limit; i += 2) {
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - 1 - i);
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    _10.setModelRTMtx(GetPosMtx(pos, expected != hash));
    _1BC.reset(mOwner.mParam.obj()._4);
}
#undef MF_FUNCTION

}}}}  // namespace scn::step::gimmick::cutropestep
