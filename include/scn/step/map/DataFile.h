#ifndef SCN_STEP_MAP_DATAFILE_H
#define SCN_STEP_MAP_DATAFILE_H

#include "scn/step/map/DataAccessor.h"

namespace scn {
namespace step {
namespace map {

class DataFile {
public:
    DataAccessor accessor() const;
};

}}}  // namespace scn::step::map

#endif
