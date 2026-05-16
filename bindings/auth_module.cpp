#include <pybind11/pybind11.h>
#include "../core/include/auth.h"

namespace py = pybind11;

PYBIND11_MODULE(auth_module, m) {
    m.doc() = "Python bindings for the secure messenger authentication layer.";

    py::class_<UserRecord>(m, "UserRecord")
        .def_readonly("login", &UserRecord::login)
        .def_readonly("hash", &UserRecord::hash)
        .def_readonly("salt", &UserRecord::salt);

    py::class_<AuthManager>(m, "AuthManager")
        .def(py::init<>())
        .def("register_user", &AuthManager::register_user,
             "Register a user and return a UserRecord.",
             py::arg("login"), py::arg("password"))
        .def("verify_user", &AuthManager::verify_user,
             "Verify user credentials against stored hash and salt.",
             py::arg("login"), py::arg("password"),
             py::arg("hash"), py::arg("salt"));
}
