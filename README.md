Install and build the project on Windows:

1) Download msys2 on https://www.msys2.org/
2) install gcc with 'pacman -S mingw-w64-ucrt-x86_64-gcc'
3) install mingw toolchain with 'pacman -S --needed base-devel mingw-w64-86_64-toolchain'
4) Download vscode on https://code.visualstudio.com/
5) install C/C++ 'Extention Pack' and 'CMakeTools' in VSCode Extentions Marketplace
6) Clone VcPkg the way it is described on https://vcpkg.io/en/getting-started.html
7) Clone PCANBasic VcPkg custom port from https://github.com/le1nax/pcanbasicPort
8) copy the custom port into C:/src/vcpkg/ports
9) install PCANBasic USB driver on https://www.peak-system.com/Drivers.523.0.html?&L=1&gclid=Cj0KCQiAhomtBhDgARIsABcaYymK2YJHcDezRRLWyHRyjNoiTxcTiBKGofs6HnykRkif9vdrBY0sDl8aAmVpEALw_wcB
10) Clone the ECLAPatientmonitor repo into your prefered Repository directory
11) Open the CMakeLists.txt directory of the project in VsCode and select gcc mingw kit (F1, type in 'CMake: Select Kit')
12) Build the project with the selected kit, vcpkg install requirements will be executed automatically

   
