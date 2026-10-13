#ifndef PAUSE_RESULTSETTER_H
#define PAUSE_RESULTSETTER_H

#include "pause/Result.h"
#include "types.h"

namespace pause {

class ResultSetter {
public:
    bool wasSet() const;
    void set(Result result);
};

}  // namespace pause

#endif
