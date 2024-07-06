#include "pch.h"
//#include "SoundManager.h"
//
//#include <filesystem>
//#include <cassert>
//
//FMOD_SYSTEM* Engine::SoundManager::m_pSystem = nullptr;
//FMOD_CHANNEL* Engine::SoundManager::m_pChannel[] = {};
//std::map<std::string, FMOD_SOUND*> Engine::SoundManager::m_sounds = {};
//
//Engine::SoundManager::SoundManager()
//{
//	FMOD_System_Create(&m_pSystem, FMOD_VERSION);
//	FMOD_System_Init(m_pSystem, CHANNEL::END_CHANNEL, FMOD_INIT_NORMAL, NULL);
//}
//
//Engine::SoundManager::~SoundManager()
//{
//	for (auto it = m_sounds.begin(); it != m_sounds.end(); it++)
//	{
//		FMOD_Sound_Release(it->second);
//	}
//	m_sounds.clear();
//
//	FMOD_System_Close(m_pSystem);
//	FMOD_System_Release(m_pSystem);
//
//	// ä���� �˾Ƽ� �����Ǵ���?
//}
//
//bool Engine::SoundManager::Initialize(const std::string& _folderPath)
//{
//	std::filesystem::path folderPath(_folderPath);
//	assert(std::filesystem::exists(folderPath));
//	assert(std::filesystem::is_directory(folderPath));
//
//	for (const auto& entry : std::filesystem::directory_iterator(_folderPath))
//	{
//		assert(entry.is_regular_file());
//
//		std::string filePath = entry.path().string();
//		std::string fileName = entry.path().filename().string();
//		std::string extension = entry.path().extension().string();
//
//		if (extension == ".mp3" || extension == ".wav" || extension == ".ogg")
//		{
//			// �������� '\\'�� ������ '/' �� ��ȯ
//			replace(filePath.begin(), filePath.end(), '\\', '/');
//
//			// ���� �� (loop)�� ���ԵǾ��ִٸ� true ��ȯ
//			bool bLoop = fileName.find("(loop)") != std::string::npos;
//
//			AddSound(filePath, bLoop);
//		}
//	}
//	return false;
//}
//
//void Engine::SoundManager::Update()
//{
//	FMOD_System_Update(m_pSystem);
//}
//
//void Engine::SoundManager::AddSound(std::string _soundPath, bool _bLoop)
//{
//	FMOD_SOUND* sound = nullptr;
//
//	FMOD_MODE mode;
//	if (_bLoop) mode = FMOD_LOOP_NORMAL;
//	else mode = FMOD_DEFAULT;
//
//	// ���� ��ο� ���� ���η� ���� ����
//	FMOD_System_CreateSound(m_pSystem, _soundPath.c_str(), mode, 0, &sound);
//
//	// ���尡 �� �����Ǿ��ٸ� nullptr�� �ƴϾ����
//	assert(sound != nullptr);
//
//	// ������ ���带 ���� ��θ� Ű������ ������ �ʿ� �־��ش�
//	m_sounds.insert(std::make_pair(_soundPath, sound));
//}
//
//void Engine::SoundManager::Play(CHANNEL _ch, const std::string& _soundPath)
//{
//	FMOD_SOUND* sound = nullptr;
//	if (m_sounds.find(_soundPath) != m_sounds.end())
//		sound = m_sounds[_soundPath];
//	assert(sound != nullptr);
//
//	FMOD_System_PlaySound(m_pSystem, sound, NULL, false, &m_pChannel[_ch]);
//	FMOD_Channel_SetVolume(m_pChannel[_ch], 0.5);
//}
//
//void Engine::SoundManager::Pause(CHANNEL _ch)
//{
//	FMOD_Channel_SetPaused(m_pChannel[_ch], true);
//}
//
//void Engine::SoundManager::Resume(CHANNEL _ch)
//{
//	FMOD_Channel_SetPaused(m_pChannel[_ch], false);
//}
//
//void Engine::SoundManager::Stop(CHANNEL _ch)
//{
//	FMOD_Channel_Stop(m_pChannel[_ch]);
//}
//
//void Engine::SoundManager::SetVolume(CHANNEL _ch, float _vol)
//{
//	FMOD_Channel_SetVolume(m_pChannel[_ch], _vol);
//}
//
////int SoundManager::Release() {
////	FMOD_System_Close(m_pSystem);
////	FMOD_System_Release(m_pSystem);
////
////	return 0;
////}
