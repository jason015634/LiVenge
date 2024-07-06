#pragma once
#include <fmod.hpp>
#include <map>
#include <string>

// ���� ������ ä�� ���
// ���� ä�γ����� volume, pause, resume ���� ������

enum CHANNEL
{
    BGM,
    SFX,
    PLAYER,
    END_CHANNEL,
};

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();
public:

    bool Initialize(const std::string& _folderPath);
    void Update();

private:
    void AddSound(std::string _soundPath, bool _bLoop);

public:
    static void Play(CHANNEL _ch, const std::string& _soundPath);
    static void Pause(CHANNEL _ch);
    static void Resume(CHANNEL _ch);
    static void Stop(CHANNEL _ch);
    static void SetVolume(CHANNEL _ch, float _vol);

private:
    static FMOD_SYSTEM* m_pSystem;
    static FMOD_CHANNEL* m_pChannel[CHANNEL::END_CHANNEL];
    static std::map<std::string, FMOD_SOUND*> m_sounds;

};