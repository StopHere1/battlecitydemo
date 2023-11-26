#ifndef SOUND_H
#define SOUND_H
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <string>
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"
#include "../../public/src/yssimplesound/src/yssimplesound.h"

class Sound
{
private:
    float bgmVolumeLevel;
    YsSoundPlayer bgmPlayer;
    YsSoundPlayer::SoundData bgm;
    YsSoundPlayer effectPlayer;
    YsSoundPlayer::SoundData selection[3];
    YsSoundPlayer::SoundData gameStatus[3];
    YsSoundPlayer::SoundData bulletShoot[3];
    YsSoundPlayer::SoundData hit[5];
    YsSoundPlayer::SoundData occupy[3];
    YsSoundPlayer::SoundData toolCollected;
    YsSoundPlayer::SoundData playerStatus[2];
protected:
    bool loadSound(YsSoundPlayer::SoundData &wav, std::string fileName);
public:
    Sound();
    ~Sound();
    float getBGMVolume();
    float setBGMVolume(float input);
    float volumeUp(); // if the "Volume Up" button is clicked
    float volumeDown(); // if the "Volume Down" button is clicked

    //load BGM and play in the background
    void BGM(); 
    
    // load sound effects and start the effectPlayer
    void loadEffects(); 
    // play one shot of respective sound effects //
    void playButtonClick(); // click on the menu button
    void playLoadSelection(); // select loading for each player
    void playSwitchPlayerSelection(); // switch to the other player after one confirmed selection
    void playGameStart(); // pre-game selection finished and game starts
    void playGameOver(); // winning condition matched and game over
    void playCelebration(); // celebrate for the winner
    void playShootBullet1(); // shoot bullet type 1
    void playShootBullet2();
    void playShootBullet3();
    void playHitTank(); // when the bullet hits a tank
    void playHitAmor(); // hits the armor and it crashed
    void playHitProp(); // hits the prop
    void playHitWall(); // hits the wall or block and it crashed
    void playHitRebound(); // hits the indestructible wall or blocks
    void playOccupying(); // when a player is occupying a point
    void playOccupied(); // when a player successfully occupied a point
    void playOccupyFailed(); // the occupying process is disrupted and failed
    void playCollectTool(); // when collecting a tool from the map
    void playDie(); // when a player dies
    void playRevive(); // when a player revives
};

#endif //SOUND_H