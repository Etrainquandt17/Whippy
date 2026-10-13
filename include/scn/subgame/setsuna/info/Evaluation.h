#ifndef SCN_SUBGAME_SETSUNA_INFO_EVALUATION_H
#define SCN_SUBGAME_SETSUNA_INFO_EVALUATION_H

#include "hel/common/ScopedPtr.h"
#include "lyt/Layout.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace setsuna {
namespace info {

class Evaluation {
public:
    Evaluation();
    ~Evaluation();

    void showGood();
    void showBad();
    bool isAnimEnd() const;
    void close();
    void updateMain();
    void drawLayout() const;

private:
    hel::common::ScopedPtr<lyt::Layout> mGoodLayout;
    hel::common::ScopedPtr<lyt::Layout> mBadLayout;
};

}}}}  // namespace scn::subgame::setsuna::info

#endif
