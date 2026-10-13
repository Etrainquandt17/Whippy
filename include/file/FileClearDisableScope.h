#ifndef FILE_FILECLEARDISABLESCOPE_H
#define FILE_FILECLEARDISABLESCOPE_H

#include "hel/common/NonCopyable.h"

namespace file {

class FileClearDisableScope : private hel::common::NonCopyable {
public:
    FileClearDisableScope();
    ~FileClearDisableScope();
};

}  // namespace file

#endif
