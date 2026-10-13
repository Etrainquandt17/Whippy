#ifndef NW4R_DB_ASSERT_H
#define NW4R_DB_ASSERT_H

namespace nw4r {
namespace db {

void Panic(const char* file, int line, const char* format, ...);
void Warning(const char* file, int line, const char* format, ...);

}
}

// The library's inline functions keep their assertions in this game, under the file names and lines of its own headers.
#define NW4R_ASSERTMSG_AT(file, line, exp, ...) ((void)((exp) || (nw4r::db::Panic(file, line, __VA_ARGS__), 0)))
#define NW4R_ASSERT_AT(file, line, exp) NW4R_ASSERTMSG_AT(file, line, exp, "NW4R:Failed assertion " #exp)
#define NW4R_ASSERT_PTR_AT(file, line, ptr) NW4R_ASSERTMSG_AT(file, line, (ptr) != 0, "NW4R:Pointer must not be NULL (" #ptr ")")

#endif
