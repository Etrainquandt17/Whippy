#ifndef OCOLL_SEARCHATTACK_H
#define OCOLL_SEARCHATTACK_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace ocoll {

class Manager;
class NodeDesc;
class Owner;

class SearchAttack {
public:
    SearchAttack(Manager& manager, Owner& owner);
    ~SearchAttack();

    void setValid(bool valid);
    void update();
    void addNode(const NodeDesc& desc);
    void clearNode();
    bool isCollide() const;
    u32 getCollidedNum() const;
    bool getCollidedAttackTargetGimmick(u32 index) const;
    u32 getCollidedAttackType(u32 index) const;
    u32 getCollidedAttackElement(u32 index) const;
    u64 getCollidedAttackOwnerRootUid(u32 index) const;
    hel::math::Vector2 getCollidedAttackPos(u32 index) const;

private:
    u32 _0[0x180 / 4];
};

}

#endif
