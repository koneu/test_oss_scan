#include <exception>

#include "app/logger.hpp"
#include "app/user_repository.hpp"

int main() {
    auto log = app::init_logger();

    try {
        app::UserRepository repo(":memory:");
        repo.add("Ada Lovelace", "ada@example.com");
        repo.add("Alan Turing", "alan@example.com");

        for (const auto& user : repo.all()) {
            log->info("User #{}: {} <{}>", user.id, user.name, user.email);
        }
        log->info("{} users in database", repo.count());
    } catch (const std::exception& e) {
        log->error("Unhandled error: {}", e.what());
        return 1;
    }
    return 0;
}
