// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "framework.h"

DWORD WINAPI Main(LPVOID) {
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w+", stdout);
    SetConsoleTitleA("NotTacos Skin Changer | GUI COMING SOON");
    AFortPlayerPawn* Pawn;
    static UClass* Skin = reinterpret_cast<UClass*>(UECore::GObjects->FindObjectFast("")); // put any skin you want like CID_028_Athena_Commando_F or something idk
    if (Pawn) {
        Pawn->ServerChoosePart(EFortCustomPartType::Body, Skin);
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
        CreateThread(0, 0, Main, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

