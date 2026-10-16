#include "app/user_repository.hpp"

#include <algorithm>
#include <stdexcept>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

namespace app {

void to_json(nlohmann::json& j, const User& user) {
    j = nlohmann::json{{"id", user.id}, {"name", user.name}, {"email", user.email}};
}

void from_json(const nlohmann::json& j, User& user) {
    j.at("id").get_to(user.id);
    j.at("name").get_to(user.name);
    j.at("email").get_to(user.email);
}

std::int64_t UserRepository::add(const std::string& name, const std::string& email) {
    const bool taken = std::any_of(users_.begin(), users_.end(), [&](const User& u) { return u.email == email; });
    if (taken) {
        throw std::invalid_argument("email already in use: " + email);
    }
    const auto id = next_id_++;
    users_.push_back(User{id, name, email});
    spdlog::info("Added user {} ({}) with id {}", name, email, id);
    return id;
}

std::optional<User> UserRepository::find_by_id(std::int64_t id) const {
    const auto it = std::find_if(users_.begin(), users_.end(), [id](const User& u) { return u.id == id; });
    if (it == users_.end()) {
        return std::nullopt;
    }
    return *it;
}

std::vector<User> UserRepository::all() const {
    return users_;
}

bool UserRepository::remove(std::int64_t id) {
    const auto it = std::remove_if(users_.begin(), users_.end(), [id](const User& u) { return u.id == id; });
    const bool removed = it != users_.end();
    users_.erase(it, users_.end());
    return removed;
}

std::size_t UserRepository::count() const {
    return users_.size();
}

std::string UserRepository::to_json() const {
    return nlohmann::json(users_).dump(2);
}

void UserRepository::load_json(const std::string& json) {
    auto users = nlohmann::json::parse(json).get<std::vector<User>>();
    std::int64_t max_id = 0;
    for (const auto& user : users) {
        max_id = std::max(max_id, user.id);
    }
    users_ = std::move(users);
    next_id_ = max_id + 1;
    spdlog::debug("Loaded {} users from JSON", users_.size());
}

}  // namespace app
