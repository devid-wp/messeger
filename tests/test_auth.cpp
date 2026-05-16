#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "auth.h"
#include "crypto.h"

TEST_CASE("register_user generates non-empty hash and salt", "[AuthManager]") {
    AuthManager auth;
    UserRecord record = auth.register_user("test_user", "secure_password");

    REQUIRE_FALSE(record.hash.empty());
    REQUIRE_FALSE(record.salt.empty());
}

TEST_CASE("verify_user returns true for correct password", "[AuthManager]") {
    AuthManager auth;
    UserRecord record = auth.register_user("test_user", "secure_password");

    REQUIRE(auth.verify_user("test_user", "secure_password", record.hash, record.salt));
}

TEST_CASE("verify_user returns false for incorrect password", "[AuthManager]") {
    AuthManager auth;
    UserRecord record = auth.register_user("test_user", "secure_password");

    REQUIRE_FALSE(auth.verify_user("test_user", "wrong_password", record.hash, record.salt));
}

TEST_CASE("register_user generates different hashes for same password", "[AuthManager]") {
    AuthManager auth;
    UserRecord record1 = auth.register_user("user1", "secure_password");
    UserRecord record2 = auth.register_user("user2", "secure_password");

    REQUIRE(record1.hash != record2.hash);
    REQUIRE(record1.salt != record2.salt);
}

TEST_CASE("secure_compare works correctly", "[CryptoEngine]") {
    CryptoEngine crypto;

    REQUIRE(crypto.secure_compare("abc", "abc"));
    REQUIRE_FALSE(crypto.secure_compare("abc", "abd"));
    REQUIRE_FALSE(crypto.secure_compare("abc", "abcd"));
}

TEST_CASE("register_user throws exception for invalid input", "[AuthManager]") {
    AuthManager auth;

    REQUIRE_THROWS_AS(auth.register_user("", "secure_password"), std::invalid_argument);
    REQUIRE_THROWS_AS(auth.register_user("test_user", "short"), std::invalid_argument);
}