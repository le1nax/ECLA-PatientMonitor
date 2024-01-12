Install and build the project on Windows:

1) Download msys2 on https://www.msys2.org/
  1.1) install gcc with 'pacman -S mingw-w64-ucrt-x86_64-gcc'
  1.2) install mingw toolchain with 'pacman -S --needed base-devel mingw-w64-86_64-toolchain'
2) Download vscode on https://code.visualstudio.com/
  2.1) install C/C++ 'Extention Pack' and 'CMakeTools' in VSCode Extentions Marketplace
3) Clone VcPkg the way it is described on https://vcpkg.io/en/getting-started.html
4) Clone PCANBasic VcPkg custom port from https://github.com/le1nax/pcanbasicPort
  4.1) copy the custom port into C:/src/vcpkg/ports
5) Clone the ECLAPatientmonitor repo into your prefered Repository directory
6) Open the CMakeLists.txt directory of the project in VsCode and select gcc mingw kit
   6.1) Build the project with the selected kit, vcpkg install requirements will be executed automatically
   
