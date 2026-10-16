#pragma once

#include <cstdint>
#include <string>

namespace app {

struct User {
    std::int64_t id{0};
    std::string name;
    std::string email;
};

inline bool operator==(const User& lhs, const User& rhs) {
    return lhs.id == rhs.id && lhs.name == rhs.name && lhs.email == rhs.email;
}

}  // namespace app
