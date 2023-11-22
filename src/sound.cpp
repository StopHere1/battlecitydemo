#include <string>
#include "sound.h"

bool Sound::loadSound(YsSoundPlayer::SoundData &wav, std::string fileName)
{
    FsChangeToProgramDir();
    if (YSOK != wav.LoadWav(fileName.c_str()))
    {
        std::cout << "Error: Cannot load wav file " << fileName << std::endl;
        return false;
    }
    else
    {
        std::cout << "Successfully load wav file " << fileName << std::endl;
        return true;
    }
}

void Sound::BGM()
{
    // load BGM
    std::string bgmName = "../soundlib/0bgm.wav";
    loadSound(bgm, bgmName);
    bgmPlayer.Start();
    bgmPlayer.SetVolume(bgm, 0.5);
    bgmPlayer.PlayBackground(bgm);
}

void Sound::loadEffects()
{
    // load Sound Effects
    loadSound(selection[0], "../soundlib/1buttonClicked.wav");
    loadSound(selection[1], "../soundlib/2loadSelected.wav");
    loadSound(selection[2], "../soundlib/3playerSwitch.wav");
    
    loadSound(gameStatus[0], "../soundlib/4gameStart.wav");
    loadSound(gameStatus[0], "../soundlib/10gameOver.wav");
    loadSound(gameStatus[2], "../soundlib/11celebration.wav");
    
    loadSound(bulletShoot[0], "../soundlib/5bullet.wav");
    loadSound(bulletShoot[1], "../soundlib/5bullet2.wav");
    loadSound(bulletShoot[1], "../soundlib/5bullet3.wav");
    
    loadSound(hit[0], "../soundlib/6hitTank.wav");
    loadSound(hit[1], "../soundlib/6hitArmor.wav");
    loadSound(hit[2], "../soundlib/6hitProp.wav");
    loadSound(hit[3], "../soundlib/6hittWall.wav");
    loadSound(hit[4], "../soundlib/6hitRebound.wav");
    
    loadSound(occupy[0], "../soundlib/7occupying.wav");
    loadSound(occupy[1], "../soundlib/7occupied.wav");
    loadSound(occupy[2], "../soundlib/7occupyFailed.wav");
    
    loadSound(toolCollected, "../soundlib/8toolCollected.wav");
    
    loadSound(playerStatus[0], "../soundlib/9playerDie.wav");
    loadSound(playerStatus[1], "../soundlib/9playerRevive.wav");
    effectPlayer.Start();
}
