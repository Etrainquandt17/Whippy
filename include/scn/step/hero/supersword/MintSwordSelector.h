#ifndef SCN_STEP_HERO_SUPERSWORD_MINTSWORDSELECTOR_H
#define SCN_STEP_HERO_SUPERSWORD_MINTSWORDSELECTOR_H

namespace scn {
namespace step {
namespace hero {
namespace supersword {

class SwordSelector;

namespace MintSwordSelector {

void Register(SwordSelector& obj);
void Unregister(SwordSelector& obj);
void SetKind(int kind);
void SetRareTryCount(int count);

}}}}}  // namespace scn::step::hero::supersword::MintSwordSelector

#endif
