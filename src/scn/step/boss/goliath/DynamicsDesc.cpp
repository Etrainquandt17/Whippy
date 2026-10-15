#define DYNAMICS_DESC_MEMBERS

#include "scn/step/boss/goliath/DynamicsDesc.h"

#include "dynamics/Desc.h"
#include "hel/common/Array.h"
#include "hel/common/ArrayUtil.h"

using hel::common::Array;
using hel::common::ArrayUtil;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

namespace DynamicsDesc {

const chara::ModelDesc::DynamicsDesc& Create(bool isAngry) {
    static chara::ModelDesc::DynamicsDesc modelDynaDesc;
    static Array<dynamics::Desc, 1> dynaDesc;

    dynaDesc[0]._0 = isAngry ? -0.005f : 0.005f;
    dynamics::DescNode node0;
    node0.init(1.0f, 0.0f, 0.0f, 0.4f, 0.0034906585f, 0.034906585f, 0.12217305f, isAngry ? 0.27925268f : 0.13962634f, 1.0f);
    dynaDesc[0].setDescNode(0, node0);
    dynamics::DescNode node1;
    node1.init(1.0f, 0.0f, 0.0f, 0.4f, 0.0034906585f, 0.034906585f, 0.12217305f, isAngry ? 0.4537856f : 0.31415927f, 1.0f);
    dynaDesc[0].setDescNode(1, node1);
    dynamics::DescNode node2;
    node2.init(1.0f, 0.0f, 0.0f, 0.4f, 0.0034906585f, 0.034906585f, 0.12217305f, isAngry ? 0.5934119f : 0.41887903f, 1.0f);
    dynaDesc[0].setDescNode(2, node2);
    dynamics::DescNode node3;
    node3.init(1.0f, 0.0f, 0.0f, 0.4f, 0.0034906585f, 0.034906585f, 0.12217305f, isAngry ? 0.80285144f : 0.62831855f, 1.0f);
    dynaDesc[0].setDescNode(3, node3);
    dynamics::DescNode node4;
    node4.init(1.0f, 0.0f, 0.0f, 0.4f, 0.0034906585f, 0.034906585f, 0.12217305f, isAngry ? 1.0471976f : 0.87266463f, 1.0f);
    dynaDesc[0].setDescNode(4, node4);
    dynaDesc[0].mNodeNum = 5;
    dynaDesc[0].mName = "Hair1DJ";
    modelDynaDesc.mNum = 1;
    modelDynaDesc.mDescs = reinterpret_cast<dynamics::Desc*>(&dynaDesc);
    return modelDynaDesc;
}

}

}}}}  // namespace scn::step::boss::goliath

namespace dynamics {

// The link keeps these two inline functions of dynamics/Desc.h in this unit.
// TODO: the header declares them out of line, and the nodes are a hel::common::Array there.
void DescNode::init(f32 _0_, f32 _4_, f32 _8_, f32 _c_, f32 _10_, f32 _14_, f32 _18_, f32 _1c_, f32 _20_) {
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

void Desc::setDescNode(int index, const DescNode& node) {
    ArrayUtil::RangeCheck(index, 5);
    DescNode& dst = mNodes[index];
    dst._0[0] = node._0[0];
    dst._0[1] = node._0[1];
    dst._0[2] = node._0[2];
    dst._0[3] = node._0[3];
    dst._0[4] = node._0[4];
    dst._0[5] = node._0[5];
    dst._0[6] = node._0[6];
    dst._0[7] = node._0[7];
    dst._0[8] = node._0[8];
}

}  // namespace dynamics
