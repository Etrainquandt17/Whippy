#include "msg/Message.h"

#include "app/Locale.h"
#include "libms/msgfile.h"

namespace {

// Indexed by the language app::Locale::GetLanguage returns.
#ifdef VERSION_SUKK01
const char* DIRS_US[8] = {0, "US_English", 0, "US_French", "US_Spanish", 0, 0, 0};
const char* DIRS_EU[8] = {0, "EU_English", "EU_German", "EU_French", "EU_Spanish", "EU_Italian", "EU_Dutch", 0};
const char* DIRS_JP[8] = {"JP_Japanese", 0, 0, 0, 0, 0, 0, 0};
const char* DIRS_KR[8] = {0, 0, 0, 0, 0, 0, 0, "KR_Korean"};
#else
const char* DIRS_US[6] = {0, "US_English", 0, "US_French", "US_Spanish", 0};
const char* DIRS_EU[6] = {0, "EU_English", "EU_German", "EU_French", "EU_Spanish", "EU_Italian"};
const char* DIRS_JP[6] = {"JP_Japanese", 0, 0, 0, 0, 0};
#endif

}

namespace msg {

namespace {

// TODO: most likely an operator+ of hel::common::FixedString; the name is made up.
inline hel::common::FixedString<80> Join(const hel::common::FixedString<80>& path, const hel::common::FixedStringIN<char, 80>& extension) {
    return hel::common::FixedStringIN<char, 80>::FromFormat("%s%s", static_cast<const char*>(path), static_cast<const char*>(extension));
}

}

Message::Message(const char* name)
    : mFileAccessor(Join(FilePath(name), hel::common::FixedStringIN<char, 80>(".msbt")), false)
    , mMessageInfo(0) {
    mMessageInfo = LMS_InitMessage(mFileAccessor.block().startAddress());
}

Message::~Message() {
    LMS_CloseMessage(mMessageInfo);
    mMessageInfo = 0;
}

hel::common::FixedString<80> Message::FilePath(const char* name) {
    int language = app::Locale::GetLanguage();
    const char* dir = 0;
    switch (app::Locale::GetRegion()) {
    case 0:
        dir = DIRS_JP[language];
        break;
    case 1:
        dir = DIRS_US[language];
        break;
    case 2:
        dir = DIRS_EU[language];
        break;
#ifdef VERSION_SUKK01
    case 3:
        dir = DIRS_KR[language];
        break;
#endif
    }
    return hel::common::FixedStringIN<char, 80>::FromFormat("msg/%s/%s", dir, name);
}

const wchar_t* Message::text(const char* label) {
    int index = LMS_GetTextIndexByLabel(mMessageInfo, label);
    if (index < 0 || LMS_GetTextNum(mMessageInfo) <= index) {
        return 0;
    }
    return LMS_GetText(mMessageInfo, index);
}

}
