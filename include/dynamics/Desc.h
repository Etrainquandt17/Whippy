#ifndef DYNAMICS_DESC_H
#define DYNAMICS_DESC_H

#include "types.h"

#ifdef DYNAMICS_DESC_MEMBERS
#include "hel/common/FixedString.h"
#endif

namespace dynamics {

// TODO: name the members.
class DescNode {
public:
    // TODO: inline in the original. A unit that expands it defines DYNAMICS_DESCNODE_INIT_IN_CLASS ahead of its
    // includes.
#ifdef DYNAMICS_DESCNODE_INIT_IN_CLASS
    void init(f32 _0_, f32 _4_, f32 _8_, f32 _c_, f32 _10_, f32 _14_, f32 _18_, f32 _1c_, f32 _20_) {
        _0[0] = _0_;
        _0[1] = _4_;
        _0[2] = _8_;
        _0[3] = _c_;
        _0[4] = _10_;
        _0[5] = _14_;
        _0[6] = _18_;
        _0[7] = _1c_;
        _0[8] = _20_;
    }
#else
    void init(f32 _0, f32 _4, f32 _8, f32 _c, f32 _10, f32 _14, f32 _18, f32 _1c, f32 _20);
#endif

    f32 _0[9];
};

// TODO: the constructor is inline in the original: a unit that builds one description expands it
// (scn/step/enemy/bladeknight/ModelDesc.cpp). The units written before the members were known use the opaque
// form, so a unit that needs the members or the body defines DYNAMICS_DESC_MEMBERS ahead of its includes.
class Desc {
public:
#ifdef DYNAMICS_DESC_MEMBERS
    Desc() : _0(0.0f), mNodeNum(0) {}

    f32 _0;
    u32 mNodeNum;
    hel::common::FixedString<40> mName;
    DescNode mNodes[5];
#else
    Desc();

private:
    u32 _0[0xE4 / 4];

public:
#endif
    void setDescNode(int index, const DescNode& node);
};

}  // namespace dynamics

#endif
