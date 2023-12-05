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
 -soundlib
 -src
 -CMakeLists.txt
 -LICENSE
 -README.md
 -.gitignore
--public
```

CC-BY-Licensed music files:
• 3playerSwitch.wav
Gabriel Araujo (2015), Sound Effects of Winning the game, Ear0.com. [online] Available at: https://www.ear0.com/sound/13209
• 6hitTank.wav
Ka, L. (2021), Bullets Hitting the Dirt/ Rock, Ear0.com. [online] Available at: https://www.ear0.com/sound/20883
• 10gameOver.wav
Rdholder (2019), Sound Effects of Winning the game/ Achieving goals, Ear0.com. [online] Available at: https://www.ear0.com/sound/18111 
Royalty Free or CC-Licensed music files from known games:
• 4gameStart.wav: from the original Battle City Game (NES)
• 6hitAmor.wav, 7occupied.wav, 7occupyFailed.wav, 7occupying.wav: from the Apex Legends sound effect pack
Other files in the “soundlib” directory are royalty free or under CC-License from online music library websites.


