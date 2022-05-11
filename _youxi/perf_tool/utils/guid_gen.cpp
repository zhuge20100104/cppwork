#include "utils/guid_gen.h"

std::string GUIDGen::gen_uuid_str() {
    return xg::newGuid().str();
}

xg::Guid GUIDGen::from_str(const std::string& src_str) {
    xg::Guid g(src_str);
    return std::move(g);
}

xg::Guid GUIDGen::gen_guid() {
    return xg::newGuid();
}