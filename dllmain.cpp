// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"
#include "globals.h"

DWORD WINAPI Main(LPVOID) {
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w+", stdout);
    SetConsoleTitleA("NotTacos Skin Changer | GUI COMING SOON");
    if (!SDK::Init()) {
        std::cout << "Failed to initalize SDK";
    }
    if (SDK::Init()) {
        SDK::AFortPlayerPawn* Pawn{};
        static SDK::UClass* Skin = reinterpret_cast<SDK::UClass*>(SDK::UECore::GObjects->FindObjectFast(Globals::cosmetic));
        if (Pawn) {
            Pawn->ServerChoosePart(Globals::cosmetictype, Skin);
        }
    }

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, Main, lpReserved, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

