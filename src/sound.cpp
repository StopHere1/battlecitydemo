#include "sound.h"

// protected
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

// pulbic
Sound::Sound()
{
    // set default bgm volume level to be 0.5
    bgmVolumeLevel = 0.5;
}

Sound::~Sound()
{
    bgmVolumeLevel = 0.5;

    bgmPlayer.End();
    effectPlayer.End();
}

void Sound::loadEffects()
{
    // load Sound Effects
    loadSound(selection[0], "../soundlib/1buttonClicked.wav");
    loadSound(selection[1], "../soundlib/2loadSelected.wav");
    loadSound(selection[2], "../soundlib/3playerSwitch.wav");

    loadSound(gameStatus[0], "../soundlib/4gameStart.wav");
    loadSound(gameStatus[1], "../soundlib/10gameOver.wav");
    loadSound(gameStatus[2], "../soundlib/11celebration.wav");

    loadSound(bulletShoot[0], "../soundlib/5bullet.wav");
    loadSound(bulletShoot[1], "../soundlib/5bullet2.wav");
    loadSound(bulletShoot[2], "../soundlib/5bullet3.wav");

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
    effectPlayer.MakeCurrent();
    effectPlayer.Start();
}

float Sound::getBGMVolume()
{
    return bgmVolumeLevel;
}

float Sound::setBGMVolume(float input)
{
    this->bgmVolumeLevel = input;
}

float Sound::volumeUp()
{
    if (bgmVolumeLevel <= 1.0)
    {
        this->bgmVolumeLevel += 0.1;
    }
    else
    {
        this->bgmVolumeLevel = 1.0;
    }
}

float Sound::volumeDown()
{
    if (bgmVolumeLevel >= 0.0)
    {
        this->bgmVolumeLevel -= 0.1;
    }
    else
    {
        this->bgmVolumeLevel = 0.0;
    }
}

void Sound::BGM()
{
    // load BGM
    // std::string bgmName = "../soundlib/0bgm.wav";
    std::string bgmName = "../soundlib/0bgm1.wav";
    loadSound(bgm, bgmName);
    bgmPlayer.MakeCurrent();
    bgmPlayer.Start();
    bgmPlayer.SetVolume(bgm, bgmVolumeLevel);
    bgmPlayer.PlayBackground(bgm);
}

void Sound::playButtonClick()
{
    effectPlayer.PlayOneShot(selection[0]);
}

void Sound::playLoadSelection()
{
    effectPlayer.PlayOneShot(selection[1]);
}

void Sound::playSwitchPlayerSelection()
{
    effectPlayer.PlayOneShot(selection[2]);
}

void Sound::playGameStart()
{
    effectPlayer.PlayOneShot(gameStatus[0]);
}

void Sound::playGameOver()
{
    effectPlayer.PlayOneShot(gameStatus[1]);
}

void Sound::playCelebration()
{
    effectPlayer.PlayOneShot(gameStatus[2]);
}

void Sound::playShootBullet1()
{
    effectPlayer.PlayOneShot(bulletShoot[0]);
}

void Sound::playShootBullet2()
{
    effectPlayer.PlayOneShot(bulletShoot[1]);
}

void Sound::playShootBullet3()
{
    effectPlayer.PlayOneShot(bulletShoot[2]);
}

void Sound::playHitTank()
{
    effectPlayer.PlayOneShot(hit[0]);
}

void Sound::playHitAmor()
{
    effectPlayer.PlayOneShot(hit[1]);
}

void Sound::playHitProp()
{
    effectPlayer.PlayOneShot(hit[2]);
}

void Sound::playHitWall()
{
    effectPlayer.PlayOneShot(hit[3]);
}

void Sound::playHitRebound()
{
    effectPlayer.PlayOneShot(hit[4]);
}

void Sound::playOccupying()
{
    effectPlayer.PlayOneShot(occupy[0]);
}

void Sound::playOccupied()
{
    effectPlayer.PlayOneShot(occupy[1]);
}

void Sound::playOccupyFailed()
{
    effectPlayer.PlayOneShot(occupy[2]);
}

void Sound::playCollectTool()
{
    effectPlayer.PlayOneShot(toolCollected);
}

void Sound::playDie()
{
    effectPlayer.PlayOneShot(playerStatus[0]);
}

void Sound::playRevive()
{
    effectPlayer.PlayOneShot(playerStatus[1]);
}