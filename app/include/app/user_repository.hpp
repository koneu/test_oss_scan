#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <SQLiteCpp/Database.h>

#include "app/user.hpp"

namespace app {

// Minimal SQLite backed repository for users.
class UserRepository {
public:
    // Use ":memory:" for an in-memory database.
    explicit UserRepository(const std::string& db_path);

    std::int64_t add(const std::string& name, const std::string& email);
    std::optional<User> find_by_id(std::int64_t id);
    std::vector<User> all();
    bool remove(std::int64_t id);
    std::size_t count();

private:
    void create_schema();

    SQLite::Database db_;
};

}  // namespace app
