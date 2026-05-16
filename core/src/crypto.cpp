#include <algorithm>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdexcept>
#include <string>
#include <vector>

// Generate a 16-byte cryptographically secure random salt.
std::string CryptoEngine::generate_salt() {
    constexpr int kSaltSize = 16; // required salt length in bytes
    std::string salt;
    salt.resize(kSaltSize); // allocate exact buffer size for raw bytes

    int rc = RAND_bytes(reinterpret_cast<unsigned char*>(&salt[0]), kSaltSize); // fill buffer with secure random bytes
    if (rc != 1) {
        throw std::runtime_error("RAND_bytes failed to generate secure salt"); // handle OpenSSL failure explicitly
    }

    return salt; // return raw binary salt as std::string
}

// Derive a 32-byte hash from password and salt using PBKDF2-HMAC-SHA256.
std::string CryptoEngine::hash_password(const std::string& password, const std::string& salt) {
    constexpr int kIterations = 100000; // high iteration count slows brute-force attacks
    constexpr int kHashSize = 32; // output hash length in bytes
    std::vector<unsigned char> hash(kHashSize);

    int rc = PKCS5_PBKDF2_HMAC(
        password.data(),
        static_cast<int>(password.size()),
        reinterpret_cast<const unsigned char*>(salt.data()),
        static_cast<int>(salt.size()),
        kIterations,
        EVP_sha256(),
        kHashSize,
        hash.data()); // derive key into binary buffer

    if (rc != 1) {
        throw std::runtime_error("PKCS5_PBKDF2_HMAC failed to derive password hash"); // propagate OpenSSL error
    }

    return std::string(reinterpret_cast<char*>(hash.data()), kHashSize); // return binary hash bytes
}

// Compare two strings in constant time to prevent timing attacks.
bool CryptoEngine::secure_compare(const std::string& a, const std::string& b) {
    if (a.size() != b.size()) {
        // Use CRYPTO_memcmp on equal-length prefix to keep timing consistent.
        size_t min_len = std::min(a.size(), b.size());
        volatile int cmp = CRYPTO_memcmp(a.data(), b.data(), min_len);
        (void)cmp;
        return false;
    }

    return CRYPTO_memcmp(a.data(), b.data(), a.size()) == 0;
}

MemoryGuard::MemoryGuard(void* buffer, std::size_t size) noexcept
    : buffer_(buffer), size_(size) {}

MemoryGuard::~MemoryGuard() {
    if (buffer_ && size_ > 0) {
        OPENSSL_cleanse(buffer_, size_);
    }
}
