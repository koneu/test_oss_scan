#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "app/user.hpp"

namespace app {

// Minimal in-memory repository for users with JSON import/export.
class UserRepository {
public:
    // Throws std::invalid_argument if the email is already taken.
    std::int64_t add(const std::string& name, const std::string& email);
    std::optional<User> find_by_id(std::int64_t id) const;
    std::vector<User> all() const;
    bool remove(std::int64_t id);
    std::size_t count() const;

    std::string to_json() const;
    // Replaces the current content. Throws nlohmann::json::exception on malformed input.
    void load_json(const std::string& json);

private:
    std::vector<User> users_;
    std::int64_t next_id_{1};
};

}  // namespace app
