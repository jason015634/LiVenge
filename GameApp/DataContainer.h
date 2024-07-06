#pragma once
#include "framework.h"
#include "../Component/Animator.h"
#include <d2d1.h>

struct DummyAnimStruct
{
	// Anim Frame
	int idle_ULDR[4][4] = { 0 };

	int move_ULDR[4][4] = { 0 };

	int attack_Up[2][4] = { 0 };
	int attack_Left[2][4] = { 0 };
	int attack_Down[2][4] = { 0 };
	int attack_Right[2][4] = { 0 };

	std::wstring bitmapPath = L"";
};

struct TileStruct
{
	int x;
	int y;

	int obj_id;
	int unit_id;
};

struct RoundStruct
{
	std::vector<TileStruct> tileMapData;

	float tileColor_One[4] = { 1.f, 1.f, 1.f, 1.f };
	float tileColor_Two[4] = { 0.5f, 0.5f, 0.6f, 1.f };

	int grid_x = 10;
	int grid_y = 10;
};

struct StageStruct
{
	std::vector<RoundStruct> roundData;
};

struct ImageData
{
	int width = 0;
	int height = 0;
	std::pair<int, int> offset_x = { 0, 0 };

	// for use Save-Load Key
	std::string imageName = "";

	// for use Map's Key
	std::wstring imageWName = L"";
};

// Tile Object
struct ObjectSaveData
{
	int obj_id = 0;
	int obj_teamID = 3;

	// For Tool
	ImageData obj_Img;
};

// Unit
struct UnitSaveData
{
	int unit_id = 0;
	double unit_hp = 0;
	double unit_atk = 0;
	double unit_atkSp = 0;
	double unit_defense = 0;
	double unit_teamID = 0;
	double unit_moveSp = 0;

	int manaCost = 0;
	int lifeCost = 0;

	std::wstring imagePath = L"";

	// For Tool
	ImageData unit_Img;
};

// round Data
struct SmallData
{
	std::map<int, float[4]> m_TileColorMap_One;
	std::map<int, float[4]> m_TileColorMap_Two;

	std::map<int, int> m_gridRowsMap;
	std::map<int, int> m_gridColsMap;


	void SetTileColorMapOneValue(int key, const float values[4])
	{
		m_TileColorMap_One[key][0] = values[0];
		m_TileColorMap_One[key][1] = values[1];
		m_TileColorMap_One[key][2] = values[2];
		m_TileColorMap_One[key][3] = values[3];
	}

	void SetTileColorMapTwoValue(int key, const float values[4])
	{
		m_TileColorMap_Two[key][0] = values[0];
		m_TileColorMap_Two[key][1] = values[1];
		m_TileColorMap_Two[key][2] = values[2];
		m_TileColorMap_Two[key][3] = values[3];
	}

	void SetGridRowsMapValue(int key, int value)
	{
		m_gridRowsMap[key] = value;
	}

	void SetGridColsMapValue(int key, int value)
	{
		m_gridColsMap[key] = value;
	}
};