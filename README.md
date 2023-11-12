### Source Code For Engineering Computation Cource Project

This work needs to be compiled using open source libraries provided by Professor Soji Yamakawa (Carnegie Mellon University):

Please clone the repository at the same level of the product with:

```shell
cd ${Your Project Repo}
git clone https://github.com/StopHere1/battlecitydemo.git
git clone http://github.com/captainys/public.git
cd battlecitydemo
cmake ..
mkdir build
cd build
cmake --build . --target battle_city_demo
```

run the executable in the terminal:

```shell
./battle_city_demo.app/Contents/MacOS/battle_city_demo (For MacOS)
or
../debug/battle_city_demo (For win)
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

