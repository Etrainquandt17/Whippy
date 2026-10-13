#ifndef SCN_SUBGAME_IRESULTHOLDER_H
#define SCN_SUBGAME_IRESULTHOLDER_H

#include "scn/subgame/Result.h"

namespace scn {
namespace subgame {

class IResultHolder {
public:
    virtual ~IResultHolder();
    virtual Result result() const = 0;
};

}
}

#endif
