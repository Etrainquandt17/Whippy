#ifndef SCN_SUBGAME_SETSUNA_INFO_RESULTTARGETNUMBER_H
#define SCN_SUBGAME_SETSUNA_INFO_RESULTTARGETNUMBER_H

#include "hel/common/ScopedPtr.h"
#include "lyt/Layout.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace setsuna {
namespace info {

class ResultTargetNumber {
public:
    ResultTargetNumber();
    ~ResultTargetNumber();

    void setVisibility(bool visible);
    void open(u32 number, u32 last);
    void close();

private:
    void initialize();

    hel::common::ScopedPtr<lyt::Layout> mLayout;
};

}
}
}
}

#endif
