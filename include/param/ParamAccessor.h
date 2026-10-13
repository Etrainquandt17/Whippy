#ifndef PARAM_PARAMACCESSOR_H
#define PARAM_PARAMACCESSOR_H

#include "types.h"
#include "xdata/XData.h"

namespace param {

class ParamAccessor {
public:
    ParamAccessor(const char* name);
    ~ParamAccessor();

    // TODO: the result is an xdata label, a u32 length followed by the characters
    const char* str(unsigned int reference) const;

    // TODO: name. Only seen inlined, in param::JITParam::data.
    const xdata::XData& xdata() const { return mXData; }

private:
    u32 _0;
    xdata::XData mXData;
};

}  // namespace param

#endif
