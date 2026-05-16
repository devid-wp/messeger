#include "auth.h"
#include "crypto.h"
#include <stdexcept>

UserRecord AuthManager::register_user(const std::string& login, const std::string& password) {
    if (login.empty()) {
        throw std::invalid_argument("login must not be empty");
    }
    if (password.size() < 8) {
        throw std::invalid_argument("password must be at least 8 characters long");
    }

    CryptoEngine crypto;
    std::string salt = crypto.generate_salt();
    std::string hash = crypto.hash_password(password, salt);

    MemoryGuard guard_hash(&hash[0], hash.size());
    MemoryGuard guard_salt(&salt[0], salt.size());

    UserRecord record{login, hash, salt};
    return record;
}

bool AuthManager::verify_user(const std::string& login, const std::string& password,
                               const std::string& stored_hash, const std::string& stored_salt) {
    CryptoEngine crypto;
    std::string computed_hash = crypto.hash_password(password, stored_salt);

    MemoryGuard guard_computed_hash(&computed_hash[0], computed_hash.size());

    return crypto.secure_compare(computed_hash, stored_hash);
}
