#pragma once
namespace SDK
{
	class UGameViewportClient;
	class UWorld;
	class AFortGameStateAthena;

	class UEngine : public UObject
	{
	public:
		UGameViewportClient* GameViewport();
	public:
		static UEngine* GetEngine();
	};

	class UGameViewportClient : public UObject
	{
	public:
		UWorld* World();
	};

	class UWorld : public UObject
	{
	public:
		AFortGameStateAthena* GameState();
	};

	class AActor : public UObject
	{
	public:

	};

	class UKismetStringLibrary : public UObject
	{
	public:
		static FName Conv_StringToName(const FString& InString);
	public:
		static UClass* StaticClass();
	};
}