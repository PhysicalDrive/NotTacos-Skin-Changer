#include "../SDK.h"
#include "Fortnite.h"
using namespace SDK;

SDK::UClass* SDK::FPlaylistPropertyArray::GetScriptClass()
{
	static SDK::UClass* Class = nullptr;

	if (!Class)
		Class = reinterpret_cast<UClass*>(SDK::UECore::GObjects->FindObjectFast("PlaylistPropertyArray"));
	return Class;
}

SDK::UObject* SDK::FPlaylistPropertyArray::BasePlaylist()
{
	return *reinterpret_cast<UObject**>(__int64(this) + GET_PROPERTYSTRUCT_OFFSET(this, "BasePlaylist"));
}

SDK::UClass* SDK::UIExtensionClass::GetScriptClass()
{
	static SDK::UClass* Class = nullptr;
	if (!Class)
		Class = reinterpret_cast<UClass*>(SDK::UECore::GObjects->FindObjectFast("PlaylistUIExtension")); //add the other one later
	return Class;
}

void ServerChoosePart(EFortCustomPartType Part, UObject* ChosenCharacterPart) {
	static SDK::UFunction* ChickenJockey = nullptr;
	if (!ChickenJockey)
		ChickenJockey = UKismetStringLibrary::StaticClass()->FindFunctionByName("ServerChoosePart");

	struct FlintAndSteel {
		EFortCustomPartType Part;    
		UObject* ChosenCharacterPart;
	};
	FlintAndSteel Params;
	Params.Part = std::move(Part);
	Params.ChosenCharacterPart = std::move(ChosenCharacterPart);

	UKismetStringLibrary::StaticClass()->GetDefaultObj()->ProcessEvent(ChickenJockey, &Params);
}