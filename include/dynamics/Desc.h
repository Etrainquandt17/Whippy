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
    void init(f32 _0, f32 _4, f32 _8, f32 _c, f32 _10, f32 _14, f32 _18, f32 _1c, f32 _20);

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

}

#endif
