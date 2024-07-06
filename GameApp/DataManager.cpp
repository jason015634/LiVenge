#include "DataManager.h"
#include "DataContainer.h"

#include <sstream> 
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;
//namespace fs = std::filesystem;
DataManager* DataManager::*m_instance = nullptr;

void DataManager::LoadData()
{
	LoadJson(m_JsonFilePath);
	LoadIniData();
	After_SerializeIn();
	Effect_SerializeIn();
}

bool DataManager::LoadJson(const std::wstring& _filePath)
{
	std::ifstream fileRead(_filePath);  // 읽기용으로 파일 열기

	if (!fileRead.is_open())
	{
		LOG_ERROR(L"File Not Found : %s", _filePath.c_str());
		return false;
	}

	std::string str((std::istreambuf_iterator<char>(fileRead)), std::istreambuf_iterator<char>());
	fileRead.close();

	// 이후 str을 가공하거나 필요한 처리를 수행 //

	json readJson = json::parse(str);
	SerializeIn(readJson);

	return true;
}

// [Tile Render Offset]
bool DataManager::LoadIniData()
{
	// Tile Render Offset
	m_TileRenderOffsetY = GetPrivateProfileIntA("TileRender_Offset", "y", 0, m_FilePath_INI);

	// Unit AnimFrame
	for (auto& [unit_id , unit_data] : m_UnitDatas)
	{
		DummyAnimStruct dummyAnimData;

		// Reading from ths INI file
		std::wstring img_Wname = Utf8ToWstring(unit_data.unit_Img.imageName);

		wchar_t buffer[512];
		GetPrivateProfileStringW(img_Wname.c_str(), L"Anim_Path", L"", buffer, sizeof(buffer) / sizeof(wchar_t), m_AnimFrameWPath_INI);
		dummyAnimData.bitmapPath = buffer;

		// idle
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				std::string key = "Idle_" + std::to_string(j) + std::to_string(i);
				dummyAnimData.idle_ULDR[j][i] = GetPrivateProfileIntA(unit_data.unit_Img.imageName.c_str(), key.c_str(), 0, m_AnimFramePath_INI);
			}
		}

		// move
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				std::string key = "Move_" + std::to_string(j) + std::to_string(i);
				dummyAnimData.move_ULDR[j][i] = GetPrivateProfileIntA(unit_data.unit_Img.imageName.c_str(), key.c_str(), 0, m_AnimFramePath_INI);
			}
		}

		// attack_Up
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				std::string key = "Attack_Up_" + std::to_string(j) + std::to_string(i);
				dummyAnimData.attack_Up[j][i] = GetPrivateProfileIntA(unit_data.unit_Img.imageName.c_str(), key.c_str(), 0, m_AnimFramePath_INI);
			}
		}

		// attack_Left
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				std::string key = "Attack_Left_" + std::to_string(j) + std::to_string(i);
				dummyAnimData.attack_Left[j][i] = GetPrivateProfileIntA(unit_data.unit_Img.imageName.c_str(), key.c_str(), 0, m_AnimFramePath_INI);
			}
		}

		// attack_Down
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				std::string key = "Attack_Down_" + std::to_string(j) + std::to_string(i);
				dummyAnimData.attack_Down[j][i] = GetPrivateProfileIntA(unit_data.unit_Img.imageName.c_str(), key.c_str(), 0, m_AnimFramePath_INI);
			}
		}

		// attack_Right
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				std::string key = "Attack_Right_" + std::to_string(j) + std::to_string(i);
				dummyAnimData.attack_Right[j][i] = GetPrivateProfileIntA(unit_data.unit_Img.imageName.c_str(), key.c_str(), 0, m_AnimFramePath_INI);
			}
		}

		m_DummyAnimData[unit_id] = dummyAnimData;
	}

	return true;
}

// [Tile Data]  [Obj Data]  [Unit data]
void DataManager::SerializeIn(json& obj)
{
	std::vector<json> saveJsonVec = obj; // JSON 데이터를 가져옴

	// Stage Info
	json stage_Json = saveJsonVec[0];
	for (auto& roundData : stage_Json.items())
	{
		RoundStruct round;
		for (auto& tileData : roundData.value())
		{
			TileStruct myTileData;
			myTileData.x = tileData["x"];
			myTileData.y = tileData["y"];
			myTileData.obj_id = tileData["obj_id"];
			myTileData.unit_id = tileData["unit_id"];
			round.tileMapData.push_back(myTileData);
		}

		m_DummyRoundData.push(round);
	}

	// Object File Info
	json objFileMap_Json = saveJsonVec[1];
	for (auto& objData : objFileMap_Json)
	{
		for (auto& obj : objData.items())
		{
			UnitSaveData myObj;

			myObj.unit_Img.imageName = obj.key();
			myObj.unit_Img.imageWName = Utf8ToWstring(obj.key());

			myObj.unit_id = obj.value()["obj_id"];
			myObj.unit_teamID = obj.value()["obj_teamID"];

			if (myObj.unit_id != 0)
				m_UnitDatas[myObj.unit_id] = myObj;
		}
	}

	// Unit File Info
	json unitFileMap_Json = saveJsonVec[2];
	for (auto& unitData : unitFileMap_Json)
	{
		for (auto& unit : unitData.items())
		{
			UnitSaveData myObj;
			myObj.unit_Img.imageName = unit.key();
			myObj.unit_Img.imageWName = Utf8ToWstring(unit.key());

			myObj.unit_id = unit.value()["unit_id"];
			myObj.unit_hp = unit.value()["unit_hp"];
			myObj.unit_atk = unit.value()["unit_atk"];
			myObj.unit_atkSp = unit.value()["unit_atkSp"];
			myObj.unit_defense = unit.value()["unit_defense"];
			myObj.unit_teamID = unit.value()["unit_teamID"];
			myObj.unit_moveSp = unit.value()["unit_moveSp"];
			myObj.manaCost = unit.value()["manaCost"];
			myObj.lifeCost = unit.value()["lifeCost"];

			if (myObj.unit_id != 0)
				m_UnitDatas[myObj.unit_id] = myObj;
		}
	}

	// smallData
	json smallDataMap_Json = saveJsonVec[3];
	smallData.m_TileColorMap_One.clear();
	smallData.m_TileColorMap_Two.clear();
	smallData.m_gridRowsMap.clear();
	smallData.m_gridColsMap.clear();

	for (const auto& entry : smallDataMap_Json["m_TileColorMap_One"].items())
	{
		int key = std::stoi(entry.key());
		const json& colorArray = entry.value();
		float values[4] = { colorArray[0], colorArray[1], colorArray[2], colorArray[3] };
		smallData.SetTileColorMapOneValue(key, values);
	}

	for (const auto& entry : smallDataMap_Json["m_TileColorMap_Two"].items())
	{
		int key = std::stoi(entry.key());
		const json& colorArray = entry.value();
		float values[4] = { colorArray[0], colorArray[1], colorArray[2], colorArray[3] };
		smallData.SetTileColorMapTwoValue(key, values);
	}

	for (const auto& entry : smallDataMap_Json["m_gridRowsMap"].items())
	{
		int key = std::stoi(entry.key());
		int value = entry.value();
		smallData.SetGridRowsMapValue(key, value);
	}

	for (const auto& entry : smallDataMap_Json["m_gridColsMap"].items())
	{
		int key = std::stoi(entry.key());
		int value = entry.value();
		smallData.SetGridColsMapValue(key, value);
	}

	json maxRound_Json = saveJsonVec[4];
	if (maxRound_Json.contains("m_maxRound"))
	{
		m_maxRound = maxRound_Json["m_maxRound"];
	}
}

void DataManager::After_SerializeIn()
{
	StageStruct stage;
	stage.roundData.clear();
		
	for (int i = 1; i <= m_maxRound; ++i)
	{
		RoundStruct round = m_DummyRoundData.front();
		m_DummyRoundData.pop();

		round.tileColor_One[0] = smallData.m_TileColorMap_One[i][0];
		round.tileColor_One[1] = smallData.m_TileColorMap_One[i][1];
		round.tileColor_One[2] = smallData.m_TileColorMap_One[i][2];
		round.tileColor_One[3] = smallData.m_TileColorMap_One[i][3];

		round.tileColor_Two[0] = smallData.m_TileColorMap_Two[i][0];
		round.tileColor_Two[1] = smallData.m_TileColorMap_Two[i][1];
		round.tileColor_Two[2] = smallData.m_TileColorMap_Two[i][2];
		round.tileColor_Two[3] = smallData.m_TileColorMap_Two[i][3];

		round.grid_x =  smallData.m_gridRowsMap[i];
		round.grid_y =  smallData.m_gridColsMap[i];

		stage.roundData.push_back(round);
	}
	m_StageData.push_back(stage);


	for (auto& child : m_DummyAnimData)
	{
#pragma region Idle Frame

		Hide::Component::FrameInfo idle_Up (
			child.second.idle_ULDR[0][0],
			child.second.idle_ULDR[0][1],
			child.second.idle_ULDR[0][2],
			child.second.idle_ULDR[0][3],
			0.1f );
		Hide::Component::FrameInfo idle_Left (
			child.second.idle_ULDR[1][0],
			child.second.idle_ULDR[1][1],
			child.second.idle_ULDR[1][2],
			child.second.idle_ULDR[1][3],
			0.1f );
		Hide::Component::FrameInfo idle_Down (
			child.second.idle_ULDR[2][0],
			child.second.idle_ULDR[2][1],
			child.second.idle_ULDR[2][2],
			child.second.idle_ULDR[2][3],
			0.1f );
		Hide::Component::FrameInfo idle_Right (
			child.second.idle_ULDR[3][0],
			child.second.idle_ULDR[3][1],
			child.second.idle_ULDR[3][2],
			child.second.idle_ULDR[3][3],
			0.1f );
#pragma endregion

#pragma region Attack Frame
		 
		// Up Attack
		Hide::Component::FrameInfo attack_Up1(
			child.second.attack_Up[0][0],
			child.second.attack_Up[0][1],
			child.second.attack_Up[0][2],
			child.second.attack_Up[0][3],
			0.5f);
		Hide::Component::FrameInfo attack_Up2(
			child.second.attack_Up[1][0],
			child.second.attack_Up[1][1],
			child.second.attack_Up[1][2],
			child.second.attack_Up[1][3],
			0.5f);

		// Left Attack
		Hide::Component::FrameInfo attack_Left1(
			child.second.attack_Left[0][0],
			child.second.attack_Left[0][1],
			child.second.attack_Left[0][2],
			child.second.attack_Left[0][3],
			0.5f);
		Hide::Component::FrameInfo attack_Left2(
			child.second.attack_Left[1][0],
			child.second.attack_Left[1][1],
			child.second.attack_Left[1][2],
			child.second.attack_Left[1][3],
			0.5f);

		// Down Attack
		Hide::Component::FrameInfo attack_Down1(
			child.second.attack_Down[0][0],
			child.second.attack_Down[0][1],
			child.second.attack_Down[0][2],
			child.second.attack_Down[0][3],
			0.5f);
		Hide::Component::FrameInfo attack_Down2(
			child.second.attack_Down[1][0],
			child.second.attack_Down[1][1],
			child.second.attack_Down[1][2],
			child.second.attack_Down[1][3],
			0.5f);

		// Right Attack
		Hide::Component::FrameInfo attack_Right1(
			child.second.attack_Right[0][0],
			child.second.attack_Right[0][1],
			child.second.attack_Right[0][2],
			child.second.attack_Right[0][3],
			0.5f);
		Hide::Component::FrameInfo attack_Right2(
			child.second.attack_Right[1][0],
			child.second.attack_Right[1][1],
			child.second.attack_Right[1][2],
			child.second.attack_Right[1][3],
			0.5f);

#pragma endregion

		Hide::Component::AnimationAsset animAsset;
		animAsset.animations[L"Idle_Up"].frameInfo.push_back(idle_Up);
		animAsset.animations[L"Idle_Left"].frameInfo.push_back(idle_Left);
		animAsset.animations[L"Idle_Down"].frameInfo.push_back(idle_Down);
		animAsset.animations[L"Idle_Right"].frameInfo.push_back(idle_Right);
		
		animAsset.animations[L"Attack_Up"].frameInfo.push_back(attack_Up1);
		animAsset.animations[L"Attack_Up"].frameInfo.push_back(attack_Up2);

		animAsset.animations[L"Attack_Left"].frameInfo.push_back(attack_Left1);
		animAsset.animations[L"Attack_Left"].frameInfo.push_back(attack_Left2);

		animAsset.animations[L"Attack_Down"].frameInfo.push_back(attack_Down1);
		animAsset.animations[L"Attack_Down"].frameInfo.push_back(attack_Down2);

		animAsset.animations[L"Attack_Right"].frameInfo.push_back(attack_Right1);
		animAsset.animations[L"Attack_Right"].frameInfo.push_back(attack_Right2);

		animAsset.m_Path = child.second.bitmapPath;

		m_AnimDatas[child.first] = animAsset;
	}
}
void DataManager::Effect_SerializeIn()
{
	//img
	Hide::Component::FrameInfo Arrow(116, 159, 147, 190, 0.1f);
	Hide::Component::FrameInfo Debuff_Tower(116, 279, 371, 534, 0.1f);
	Hide::Component::FrameInfo Enemy_Hero(116, 1289, 243, 1416, 0.1f);

	// team
	// (0, 0, 31, 31, 0.1f)
	Hide::Component::FrameInfo Team_Melee1(116, 909, 147, 940, 0.1f);
	Hide::Component::FrameInfo Team_Melee2(147, 909, 178, 940, 0.1f);

	//(0, 0, 127, 127, 0.1f)
	Hide::Component::FrameInfo Drain1(116, 623, 243, 750, 0.1f);
	Hide::Component::FrameInfo Drain2(243, 623, 370, 750, 0.1f);
	Hide::Component::FrameInfo Drain3(370, 623, 497, 750, 0.1f);

	// (0, 0, 32, 32, 0.1f)
	Hide::Component::FrameInfo Summon1(116, 1575, 147, 1607, 0.1f);
	Hide::Component::FrameInfo Summon2(148, 1575, 179, 1607, 0.1f);
	Hide::Component::FrameInfo Summon3(180, 1575, 211, 1607, 0.1f);
	Hide::Component::FrameInfo Summon4(212, 1575, 243, 1607, 0.1f);

	//(0, 0, 127, 127, 0.1f)
	Hide::Component::FrameInfo Projectile1(116, 2052, 242, 2179, 0.1f);
	Hide::Component::FrameInfo Projectile2(242, 2052, 369, 2179, 0.1f);
	Hide::Component::FrameInfo Projectile3(369, 2052, 497, 2179, 0.1f);
	Hide::Component::FrameInfo Projectile4(497, 2052, 624, 2179, 0.1f);

	// enemy
	//(0 , 0, 31, 31, 0.1f)
	Hide::Component::FrameInfo Enemy_Melee1(116, 1099, 147, 1130, 0.1f);
	Hide::Component::FrameInfo Enemy_Melee2(147, 1099, 178, 1130, 0.1f);

	//(0, 0, 127, 127, 0.1f)
	Hide::Component::FrameInfo Arrow_Tower1(116, 1765, 243, 2020, 0.1f);
	Hide::Component::FrameInfo Arrow_Tower2(243, 1765, 370, 2020, 0.1f);
	Hide::Component::FrameInfo Arrow_Tower3(370, 1765, 497, 2020, 0.1f);

	Hide::Component::AnimationAsset effectAsset;

	effectAsset.animations[L"Arrow"].frameInfo.push_back(Arrow);
	effectAsset.animations[L"Debuff_Tower"].frameInfo.push_back(Debuff_Tower);
	effectAsset.animations[L"Enemy_Hero"].frameInfo.push_back(Enemy_Hero);

	effectAsset.animations[L"Team_Melee"].frameInfo.push_back(Team_Melee1);
	effectAsset.animations[L"Team_Melee"].frameInfo.push_back(Team_Melee2);

	effectAsset.animations[L"Drain"].frameInfo.push_back(Drain1);
	effectAsset.animations[L"Drain"].frameInfo.push_back(Drain2);
	effectAsset.animations[L"Drain"].frameInfo.push_back(Drain3);

	effectAsset.animations[L"Summon"].frameInfo.push_back(Summon1);
	effectAsset.animations[L"Summon"].frameInfo.push_back(Summon2);
	effectAsset.animations[L"Summon"].frameInfo.push_back(Summon3);
	effectAsset.animations[L"Summon"].frameInfo.push_back(Summon4);

	effectAsset.animations[L"Projectile"].frameInfo.push_back(Projectile1);
	effectAsset.animations[L"Projectile"].frameInfo.push_back(Projectile2);
	effectAsset.animations[L"Projectile"].frameInfo.push_back(Projectile3);
	effectAsset.animations[L"Projectile"].frameInfo.push_back(Projectile4);

	effectAsset.animations[L"Enemy_Melee"].frameInfo.push_back(Enemy_Melee1);
	effectAsset.animations[L"Enemy_Melee"].frameInfo.push_back(Enemy_Melee2);

	effectAsset.animations[L"Arrow_Tower"].frameInfo.push_back(Arrow_Tower1);
	effectAsset.animations[L"Arrow_Tower"].frameInfo.push_back(Arrow_Tower2);
	effectAsset.animations[L"Arrow_Tower"].frameInfo.push_back(Arrow_Tower3);

	effectAsset.m_Path = L"..\\..\\..\\4_Resources/Effect/Effect_Sprite.png";

	m_EffectDatas[0] = effectAsset;
}

// UTF-8 to std::wstring
std::wstring DataManager::Utf8ToWstring(const std::string& utf8Str) {
	int requiredLength = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
	if (requiredLength == 0) {
		return L"";
	}

	std::wstring wstr;
	wstr.resize(requiredLength - 1); // Exclude null terminator
	MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, wstr.data(), requiredLength);
	return wstr;
}
