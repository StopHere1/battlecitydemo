### Source Code For Engineering Computation Cource Project

This work needs to be compiled using open source libraries provided by Professor Soji Yamakawa (Carnegie Mellon University):

Please clone the repository at the same level of the product with:

```shell
cd ${Your Project Repo}
git clone https://github.com/StopHere1/battlecitydemo.git
git clone http://github.com/captainys/public.git
cd battlecitydemo
mkdir build
cd build
```
Run one of the following sets of cmake command to compile the code and generate executable file
Make sure to run cmake inside build folder to ensure the file path is correct.
```shell
cmake ..
make
```
or
```shell
cmake --build . --target battle_city_demo
```

run the executable in the terminal:
For MacOS:
```shell
./battle_city_demo.app/Contents/MacOS/battle_city_demo
```
For windows
```shell
../debug/battle_city_demo
```

Source Tree:

```
--battlecitydemo
 -build
 -include
 -src
 -CMakeLists.txt
 -LICENSE
 -README.md
 -.gitignore
--public
```

