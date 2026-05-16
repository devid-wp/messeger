#include <pybind11/pybind11.h>
#include "../core/include/crypto.h"

namespace py = pybind11;

PYBIND11_MODULE(crypto_module, m) {
    m.doc() = "Python bindings for the secure messenger cryptography utilities.";

    py::class_<CryptoEngine>(m, "CryptoEngine")
        .def(py::init<>())
        .def("generate_salt", &CryptoEngine::generate_salt,
             "Generate a cryptographically secure random salt.")
        .def("hash_password", &CryptoEngine::hash_password,
             "Hash a password with a given salt using PBKDF2-HMAC-SHA256.",
             py::arg("password"), py::arg("salt"))
        .def("secure_compare", &CryptoEngine::secure_compare,
             "Compare two binary strings in constant time.",
             py::arg("a"), py::arg("b"));
}
