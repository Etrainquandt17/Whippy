#ifndef OCOLL_ATTACK_H
#define OCOLL_ATTACK_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace ocoll {

class AttackResult;
class Manager;
class NodeDesc;
class Owner;

class Attack {
public:
    Attack(Manager& manager, Owner& owner, u32);
    ~Attack();

    void clearNode();
    void setType(u32, u32 type);
    void addNode(u32 id, const NodeDesc& desc);
    bool isCollide() const;
    bool isCollideGimmick() const;
    hel::math::Vector2 getCollidedHitPos() const;
    u32 getCollidedHitResistLv() const;
    u32 getCollidedHitStopFrame() const;
    void setPause(bool isPause);
    void setValid(bool valid);
    // TODO: a member at 0x30.
    const AttackResult& result() const {
        return *reinterpret_cast<const AttackResult*>(reinterpret_cast<const u8*>(this) + 0x30);
    }

private:
    // TODO: the members. The size is from hero::parasol::Custom, which holds one.
    u32 _0[0x270 / 4];
};

}

#endif
