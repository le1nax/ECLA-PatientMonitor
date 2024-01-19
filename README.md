Install and build the project on Windows:

1) Download msys2 on https://www.msys2.org/
2) install mingw toolchain with 'pacman -Sy base-devel mingw-w64-x86_64-toolchain'
3) Download vscode on https://code.visualstudio.com/
4) install C/C++ 'Extention Pack' and 'CMakeTools' in VSCode Extentions Marketplace
5) Clone VcPkg the way it is described on https://vcpkg.io/en/getting-started.html
6) Clone PCANBasic VcPkg custom port from https://github.com/le1nax/pcanbasicPort
7) rename the custom port to 'pcanbasic' copy the custom port into C:/src/vcpkg/ports, so that the resulting path is 'C:/src/vcpkg/ports/pcanbasic'
8) install PCANBasic USB driver on https://www.peak-system.com/Drivers.523.0.html?&L=1&gclid=Cj0KCQiAhomtBhDgARIsABcaYymK2YJHcDezRRLWyHRyjNoiTxcTiBKGofs6HnykRkif9vdrBY0sDl8aAmVpEALw_wcB
9) Clone the ECLAPatientmonitor repo into your prefered Repository directory
10) Open the CMakeLists.txt directory of the project in VsCode and select gcc mingw kit (F1, type in 'CMake: Select Kit')
11) Build the project with the selected kit, vcpkg install requirements will be executed automatically

   
