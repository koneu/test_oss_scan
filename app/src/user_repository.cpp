#include "app/user_repository.hpp"

#include <SQLiteCpp/Statement.h>
#include <spdlog/spdlog.h>

namespace app {

namespace {

User read_user(SQLite::Statement& query) {
    return User{query.getColumn(0).getInt64(), query.getColumn(1).getString(), query.getColumn(2).getString()};
}

}  // namespace

UserRepository::UserRepository(const std::string& db_path)
    : db_(db_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    create_schema();
    spdlog::debug("Opened database '{}'", db_path);
}

void UserRepository::create_schema() {
    db_.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "  id    INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  name  TEXT NOT NULL,"
        "  email TEXT NOT NULL UNIQUE"
        ")");
}

std::int64_t UserRepository::add(const std::string& name, const std::string& email) {
    SQLite::Statement insert(db_, "INSERT INTO users (name, email) VALUES (?, ?)");
    insert.bind(1, name);
    insert.bind(2, email);
    insert.exec();
    const auto id = db_.getLastInsertRowid();
    spdlog::info("Added user {} ({}) with id {}", name, email, id);
    return id;
}

std::optional<User> UserRepository::find_by_id(std::int64_t id) {
    SQLite::Statement query(db_, "SELECT id, name, email FROM users WHERE id = ?");
    query.bind(1, id);
    if (query.executeStep()) {
        return read_user(query);
    }
    return std::nullopt;
}

std::vector<User> UserRepository::all() {
    std::vector<User> users;
    SQLite::Statement query(db_, "SELECT id, name, email FROM users ORDER BY id");
    while (query.executeStep()) {
        users.push_back(read_user(query));
    }
    return users;
}

bool UserRepository::remove(std::int64_t id) {
    SQLite::Statement del(db_, "DELETE FROM users WHERE id = ?");
    del.bind(1, id);
    return del.exec() > 0;
}

std::size_t UserRepository::count() {
    return static_cast<std::size_t>(db_.execAndGet("SELECT COUNT(*) FROM users").getInt64());
}

}  // namespace app
