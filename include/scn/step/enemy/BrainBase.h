#ifndef SCN_STEP_ENEMY_BRAINBASE_H
#define SCN_STEP_ENEMY_BRAINBASE_H

#include "hel/common/NonCopyable.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

class BrainBase : private hel::common::NonCopyable {
public:
    BrainBase(Enemy& enemy);
    virtual ~BrainBase();

    virtual bool onStart();
    virtual bool onRecover();
    virtual bool onLanding();
    virtual void update();

    Enemy& obj() const;
    // TODO: BrainBase.cpp does not define this one yet; the original link folded it away.
    Enemy& obj();

protected:
    Enemy& mEnemy;
};

}}}  // namespace scn::step::enemy

#endif
