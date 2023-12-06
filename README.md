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

How to Control Your Tank  
​
The game should have two player, `player1` and `player2`.  ​

Your tank can move in 4 directions: up, down, left and right. For the `player1`, you can use `W` to go up, use `S` to go down, use `A` to turn left and `D` to turn right. For `player2`, you should use `Up, Down, Left and Right` arrow key.  
​
`Player1` can use the `Space` to fire the bullet while `player2` should use the `0`.  

Player can also rotate the aim direction. `Player1` can use `J` to rotate clockwise while `K` for counter-clockwise. `Player2` should use `5` to rotate clockwise while `6` to rotate counter-clockwise.   
​
When one type of the bullet is run out, `player1` can use `B` to switch the bullet type while `player2` should use `7`.  
​
That's all!   
​
And Enjoy Your Game!  

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


