# MSVC/Visual Studio command card

Run these from a Visual Studio developer shell and prefer checked-in wrappers or presets.

```powershell
cl
msbuild .\Product.sln /m /p:Configuration=Debug /p:Platform=x64
msbuild .\src\Widget\Widget.vcxproj /m /t:Build /p:Configuration=Debug /p:Platform=x64
cmake --preset windows-msvc-debug
cmake --build --preset windows-msvc-debug --parallel
ctest --preset windows-msvc-debug --output-on-failure
```

Fallback CMake pattern when the project has no presets:

```powershell
cmake -S . -B build\msvc-x64 -G "Visual Studio 17 2022" -A x64
cmake --build build\msvc-x64 --config Debug --parallel
ctest --test-dir build\msvc-x64 -C Debug --output-on-failure
```

Direct compilation is suitable only for a small isolated exercise:

```powershell
cl /nologo /std:c++20 /W4 /WX /EHsc /Zi src\main.cpp /Fe:build\app.exe
```

If no developer shell is available, locate Visual Studio with `vswhere.exe`, then invoke the discovered installation's developer-shell script. Do not bake a personal installation path into repository automation.
