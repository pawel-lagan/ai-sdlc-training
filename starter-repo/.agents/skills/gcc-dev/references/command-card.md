# GCC/Linux command card

Use repository commands when present. These are fallback patterns, not universal commands.

```bash
gcc --version
g++ --version
cmake --version
ninja --version
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

Use checked-in `CMakePresets.json` when present: `cmake --preset <name>` and `cmake --build --preset <name>`.

Direct compilation for a small diagnostic exercise:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -g src/main.c -o build/app
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -g src/main.cpp -o build/app
```

Dynamic analysis patterns:

```bash
cmake -S . -B build-asan -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer" -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer"
cmake --build build-asan --parallel
ctest --test-dir build-asan --output-on-failure
valgrind --leak-check=full --error-exitcode=1 ./build/app
gdb --args ./build/app
```

Use ThreadSanitizer in a separate build tree. Do not combine it with AddressSanitizer.
