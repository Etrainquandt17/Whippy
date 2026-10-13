#ifndef MSG_MESSAGE_H
#define MSG_MESSAGE_H

#include "file/FileAccessor.h"
#include "hel/common/FixedString.h"
#include "types.h"

struct MsbtInfo;

namespace msg {

class Message {
public:
    Message(const char* name);
    ~Message();

    const wchar_t* text(const char* label);

    static hel::common::FixedString<80> FilePath(const char* name);

private:
    file::FileAccessor mFileAccessor;
    MsbtInfo* mMessageInfo;
};

}  // namespace msg

#endif
