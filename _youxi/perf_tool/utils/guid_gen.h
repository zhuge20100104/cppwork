#ifndef _FREDRIC_GUID_GEN_H_
#define _FREDRIC_GUID_GEN_H_

#include <crossguid/guid.hpp>

#include <string>

struct GUIDGen {
    static std::string gen_uuid_str();
    static xg::Guid from_str(const std::string& src_str);
    static xg::Guid gen_guid();
};
#endif