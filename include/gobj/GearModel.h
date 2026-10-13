#ifndef GOBJ_GEARMODEL_H
#define GOBJ_GEARMODEL_H

#include "gobj/IG3DModel.h"
#include "gobj/NodeRepos.h"
#include "hel/common/FixedString.h"

namespace gobj {

// TODO: name of the members. The node names a model's NodeRepos is built from.
struct NodeReposDesc {
    u32 mCount;
    const char** mNames;
};

// TODO: members.
class GearModelDesc {
public:
    GearModelDesc();

    hel::common::FixedString<24> _0;
    hel::common::FixedString<40> mName;
    u32 _40[3];
    bool _4C;
    bool _4D;
    NodeReposDesc mNodes;
};

// TODO: size and members. The parent gobj::Model sits at 4, a g3d::CharaModel at 8 and the nodes at 0x16C. This is
// the model of a gear; a character's own (chara::Model::model()) is a gobj::Model.
class GearModel : public IG3DModel {
public:
    virtual ~GearModel();
    virtual g3d::ModelAccessor g3dModel();

    const NodeRepos& nodes() const;
    void setIsParentScaleIgnore(bool isIgnore);
    void changeParentNode(u32 node);
    void removeParentNode();
};

}

#endif
