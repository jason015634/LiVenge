#pragma once
#include "framework.h"
#include "DataContainer.h"

#include <map>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <Windows.h>
#include <queue>

// 이곳에 모든 데이터 등록!
using json = nlohmann::json;

class DataManager
{
private:
    //static DataManager* m_instance;
public:
    static DataManager& GetInstance()
    {
        static std::shared_ptr<DataManager> m_instance = std::make_shared<DataManager>();
        return *m_instance;
    }

public:
    // Data Func
    void LoadData();

    void SerializeIn(json& object);
    void After_SerializeIn();
    void Effect_SerializeIn();

    bool LoadJson(const std::wstring& _filePath);
    bool LoadIniData();

    // Util //
    std::wstring Utf8ToWstring(const std::string& utf8Str);

    std::map<int, UnitSaveData> GetUnitMap()
    {
        return m_UnitDatas;
    }

private:
    // ini Path
   // const char* m_FilePath_INI = "..\\Resource/Data/config.ini";
    const char* m_FilePath_INI = "..\\..\\..\\4_Resources/Data/config.ini";
    const wchar_t* m_WFilePath_INI = L"..\\..\\..\\4_Resources/Data/config.ini";

    // Json Path
    const std::wstring m_JsonFilePath = L"..\\..\\..\\4_Resources/Data/Data.json";

    // Resource file
    std::wstring m_SearchFilePath_OBJ = L"..\\..\\..\\4_Resources/Obj_rsc/";
    std::wstring m_SearchFilePath_UNIT = L"..\\..\\..\\4_Resources/Unit_rsc/";

    const char* m_AnimFramePath_INI = "..\\..\\..\\4_Resources/Data/AnimFrame.ini";
    const wchar_t* m_AnimFrameWPath_INI = L"..\\..\\..\\4_Resources/Data/AnimFrame.ini";

    SmallData smallData = {};

    int m_maxRound = 0;
    int m_TileRenderOffsetY = 0;

    std::queue<RoundStruct> m_DummyRoundData;
    std::map<int, DummyAnimStruct> m_DummyAnimData;

public:
    // Container
    std::map<int, UnitSaveData>m_UnitDatas;
    std::map<int, Hide::Component::AnimationAsset> m_AnimDatas;
    std::map<int, Hide::Component::AnimationAsset> m_EffectDatas;
    std::map<int, ID2D1Bitmap*> m_Card;
    std::map<int, ID2D1Bitmap*> m_Shop;

    std::vector<StageStruct> m_StageData;
};