#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATES_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATES_H

#include "scn/step/boss/fattybuffer/StateStalactiteStart.h"
#include "scn/step/boss/fattybuffer/StateSwellBalloonStart.h"
#include "scn/step/boss/fattybuffer/StateSwellBackJumpStart.h"
#include "scn/step/boss/fattybuffer/StateStampStart.h"
#include "scn/step/boss/fattybuffer/StateMoveForward.h"
#include "scn/step/boss/fattybuffer/StalactiteJumpKind.h"
#include "scn/step/boss/fattybuffer/StateSwellEnd.h"
#include "scn/step/boss/fattybuffer/StateSwellStart.h"
#include "scn/step/boss/fattybuffer/StateStickRoofFall.h"
#include "scn/step/boss/fattybuffer/StateStickRoofJumpStart.h"
#include "scn/step/boss/fattybuffer/StateJumpStart.h"
#include "scn/step/boss/fattybuffer/StateTurn.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace fattybuffer {


// TODO: members of every state; one header per state once their units are written.
class StateCannon : public IState {
public:
    StateCannon(Boss* boss, bool isUpper);
    virtual ~StateCannon();
};

class StateSwellRollingAttack : public IState {
public:
    StateSwellRollingAttack(Boss* boss, unsigned long);
    virtual ~StateSwellRollingAttack();
};

class StateSwellRollingAttackCircuit : public IState {
public:
    StateSwellRollingAttackCircuit(Boss* boss);
    virtual ~StateSwellRollingAttackCircuit();
};

class StateDisgorge : public IState {
public:
    StateDisgorge(Boss* boss);
    virtual ~StateDisgorge();
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
