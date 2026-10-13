#ifndef FILE_FDGMANAGER_H
#define FILE_FDGMANAGER_H

#include "types.h"

namespace file {

class DNOption;

class FDGManager {
public:
    void load(const char* name, const DNOption& option);
    void keep(const char* name, const DNOption& option);
    void preLoad(const char* name, const DNOption& option);
};

}  // namespace file

#endif
