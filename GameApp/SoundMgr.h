#pragma once
#include <fmod.hpp>
#include <map>
#include <string>
#include <memory>

// 따로 관리될 채널 목록
// 같은 채널끼리는 volume, pause, resume 등을 공유함

enum CHANNEL
{
	BGM,
	SFX,
	PLAYER,
	END_CHANNEL,
};

class SoundMgr
{
public:
	static SoundMgr& Instance()
	{
		static std::shared_ptr<SoundMgr> m_instance = std::make_shared<SoundMgr>();
		return *m_instance;
	}

//public:
//	SoundMgr();
//	~SoundMgr();

public:
	virtual bool Initialize() { return true; };
	virtual void Finalize() {};

public:
	//int Release();
	bool Initialize(const std::string& _folderPath);
	void Update();

private:
	void AddSound(std::string _soundPath, bool _bLoop);

public:
	void Play(CHANNEL _ch, const std::string& _soundPath);
	void Pause(CHANNEL _ch);
	void Resume(CHANNEL _ch);
	void Stop(CHANNEL _ch);
	void SetVolume(CHANNEL _ch, float _vol);

private:
	FMOD_SYSTEM* m_pSystem;
	FMOD_CHANNEL* m_pChannel[CHANNEL::END_CHANNEL];
	std::map<std::string, FMOD_SOUND*> m_sounds;
};
