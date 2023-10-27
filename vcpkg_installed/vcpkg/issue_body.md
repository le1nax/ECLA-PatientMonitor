Package: pcanbasic[core]:x86-windows -> 1.0.0

**Host Environment**

- Host: x64-windows
- Compiler: MSVC 19.36.32532.0
-    vcpkg-tool version: 2023-03-29-664f8bb619b752430368d0f30a8289b761f5caba
    vcpkg-readonly: true
    vcpkg-scripts version: 84df5613f71eda8a73ab08dc3041f3af7103a5b2

**To Reproduce**

`vcpkg install `

**Failure logs**

```
-- Using cached le1nax-medit-libs-2355b33862ee5e18b491f1e0f5d080a9ec698782.tar.gz.
-- Extracting source C:/Users/danie/AppData/Local/vcpkg/downloads/le1nax-medit-libs-2355b33862ee5e18b491f1e0f5d080a9ec698782.tar.gz
-- Using source at C:/Repositories/Medit/WiHi/ECLA-PatientMonitor/vcpkg_installed/vcpkg/blds/pcanbasic/src/a9ec698782-5befec5411.clean
CMake Error at C:/src/vcpkg/ports/pcanbasic/portfile.cmake:25 (file):
  file called with unknown argument "RENAME".
Call Stack (most recent call first):
  scripts/ports.cmake:147 (include)



```


**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "name": "ecla-pm",
  "version": "1.0.0",
  "dependencies": [
    {
      "name": "pcanbasic"
    },
    {
      "name": "vcpkg-cmake",
      "host": true
    }
  ]
}

```
</details>
