#pragma once
#include <windows.h>
#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <memory>
#include <type_traits>
#include <fstream>
#include <sstream>
#include <mutex>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include "../memcury.h"
#include "SDK/Basic.h"
#include "SDK/Engine.h"
#include "SDK/Fortnite.h"

namespace SDK
{
	namespace Addresses
	{

		extern uintptr_t ObjObjectsAddr = 0;
		extern uintptr_t FName__ToString = 0;
		extern uintptr_t FName__ToStringVoid = 0;
		extern uintptr_t UObject__ProcessEvent = 0;
		namespace MemberOffsets
		{
			extern int UStruct__SuperStruct = -1;
			extern int UStruct_Children = -1;
			extern int UStruct_MinAllignment = -1;
			extern int UStruct_Script = -1;
			extern int UStruct_PropertyLink = -1;
			extern int UStruct_RefLink = -1;
			extern int UStruct_DestructorLink = -1;
			extern int UStruct_PostConstructLink = -1;
			extern int UStruct_ScriptObjectReferences = -1;
			extern int UProperty__Offset_Internal = -1;
			extern int UFunction__Func = -1;
			/*inline int UClass__ClassDefaultObject = -1;*/
		}
	}
	namespace GameInfo
	{
		uintptr_t GetBaseAddress();
	}

	namespace UE
	{
		extern std::string EngineVersion = "";

		float GetFortniteVersion();

		double GetEngineVersion();

		int GetFortniteCL();
	}

	namespace UECore
	{
		extern std::unique_ptr<SDK::FUObjectArray> GObjects;
		extern SDK::UEngine* GEngine;
		extern SDK::UWorld* GWorld;
	}

	bool InitGObjects();
	bool InitMemberOffsets();
	bool InitFName();
	bool SetupEngineVersion();
	bool InitProcessEvent();
	bool Init();
}