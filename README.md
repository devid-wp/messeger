# messeger

## Build and Run Unit Tests

This project uses CMake for building the C++ core and tests.

1. Create a build directory:

```bash
mkdir -p build && cd build
```

2. Configure the project with CMake:

```bash
cmake ..
```

3. Build the test target:

```bash
cmake --build . --target auth_tests
```

4. Run the tests:

```bash
ctest --output-on-failure
```

## Python Bindings

The project also exposes Python bindings for the authentication and crypto core.

Build the Python extension modules from the same build directory:

```bash
cmake --build .
```

This produces Python extension modules such as `auth_module` and `crypto_module` in the build tree.

### Running Python binding tests

From the repo root after building the project:

```bash
python3 tests/test_bindings.py
```

If Python cannot find the generated extension modules, run with `PYTHONPATH` pointed at the build directory:

```bash
PYTHONPATH=build python3 tests/test_bindings.py
```
