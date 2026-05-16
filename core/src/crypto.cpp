#include <openssl/rand.h>
#include <stdexcept>
#include <string>

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
