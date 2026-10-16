#include <gtest/gtest.h>

#include <stdexcept>

#include <nlohmann/json.hpp>

#include "app/user_repository.hpp"

namespace {

class UserRepositoryTest : public ::testing::Test {
protected:
    app::UserRepository repo;
};

TEST_F(UserRepositoryTest, StartsEmpty) {
    EXPECT_EQ(repo.count(), 0u);
    EXPECT_TRUE(repo.all().empty());
}

TEST_F(UserRepositoryTest, AddAndFind) {
    const auto id = repo.add("Ada", "ada@example.com");

    const auto user = repo.find_by_id(id);
    ASSERT_TRUE(user.has_value());
    EXPECT_EQ(*user, (app::User{id, "Ada", "ada@example.com"}));
}

TEST_F(UserRepositoryTest, FindUnknownReturnsNullopt) {
    EXPECT_FALSE(repo.find_by_id(42).has_value());
}

TEST_F(UserRepositoryTest, DuplicateEmailThrows) {
    repo.add("Ada", "ada@example.com");
    EXPECT_THROW(repo.add("Other Ada", "ada@example.com"), std::invalid_argument);
}

TEST_F(UserRepositoryTest, Remove) {
    const auto id = repo.add("Alan", "alan@example.com");
    EXPECT_TRUE(repo.remove(id));
    EXPECT_FALSE(repo.remove(id));
    EXPECT_EQ(repo.count(), 0u);
}

TEST_F(UserRepositoryTest, AllIsOrderedById) {
    repo.add("A", "a@example.com");
    repo.add("B", "b@example.com");
    const auto users = repo.all();
    ASSERT_EQ(users.size(), 2u);
    EXPECT_LT(users[0].id, users[1].id);
}

TEST_F(UserRepositoryTest, JsonRoundTrip) {
    repo.add("Ada", "ada@example.com");
    repo.add("Alan", "alan@example.com");

    app::UserRepository copy;
    copy.load_json(repo.to_json());
    EXPECT_EQ(copy.all(), repo.all());

    // Ids continue after the highest loaded id.
    EXPECT_EQ(copy.add("Grace", "grace@example.com"), 3);
}

TEST_F(UserRepositoryTest, LoadMalformedJsonThrows) {
    EXPECT_THROW(repo.load_json("{not json"), nlohmann::json::exception);
}

}  // namespace
