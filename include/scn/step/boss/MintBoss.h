#ifndef SCN_STEP_BOSS_MINTBOSS_H
#define SCN_STEP_BOSS_MINTBOSS_H

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace MintBoss {

void Register(Boss& obj);
void Unregister(Boss& obj);
Boss& Obj();

}}}}  // namespace scn::step::boss::MintBoss

#endif
