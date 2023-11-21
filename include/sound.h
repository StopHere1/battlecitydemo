#ifndef SOUND_H
#define SOUND_H
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"
#include "../../public/src/yssimplesound/src/yssimplesound.h"

class Sound
{
public:
    double bgmVolumeLevel;
    void BGM(); //load BGM and play in the background
protected:
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
    bool loadSound(YsSoundPlayer::SoundData &wav, std::string fileName);
    void loadEffects();
};

#endif //SOUND_H