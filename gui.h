#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <iostream>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include "Kiero/kiero.h"
#include "framework.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
static bool show = false;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (uMsg == WM_KEYUP && (wParam == 0x2D /*INSERT*/ || wParam == VK_F8 || (show && wParam == VK_ESCAPE)))
	{
		show = !show;
		ImGui::GetIO().MouseDrawCursor = show;
	}
	else if (uMsg == WM_QUIT && show)
	{
		ExitProcess(0);
	}

	if (show)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return TRUE;
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	if (show)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowBgAlpha(0.8);
		ImGui::SetNextWindowSize(ImVec2(560, 345));

		ImGui::Begin("NotTacos's Skin Changer", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

		static char cosmeticid[128] = "";
		static bool skin = false;
		static bool backbling = false;
		static bool yes = true;
		auto cosmetictype = EFortCustomPartType::Body;
		ImGui::InputText("Cosmetic ID:", cosmeticid, sizeof(cosmeticid));
		if (ImGui::Checkbox("Skin", &skin)) {
			cosmetictype = EFortCustomPartType::Body;
		}
		if (ImGui::Checkbox("Back Bling", &backbling)) {
		    cosmetictype = EFortCustomPartType::Backpack;
		}
		if (ImGui::Button("Refresh")) {
			yes = true; // just in case
			MessageBoxA(NULL, "Successfully refreshed.", "NotTacos's Skin Changer", MB_OK);
		}
		if (ImGui::Button("Change cosmetic")) {
			if (backbling || skin) {
				MessageBoxA(NULL, "You can't select 2. Press refresh once you picked one.", "NotTacos's Skin Changer", MB_OK);
				yes = false;
			}
			if (!backbling || !skin) {
				MessageBoxA(NULL, "Please select one of these. Press refresh once you picked one.", "NotTacos's Skin Changer", MB_OK);
				yes = false;
			}
			if (yes) {
				SDK::AFortPlayerPawn* Pawn{};
				static SDK::UClass* Skin = reinterpret_cast<SDK::UClass*>(SDK::UECore::GObjects->FindObjectFast(cosmeticid));
				if (Pawn) {
					Pawn->ServerChoosePart(cosmetictype, Skin);
				}
				else {
					MessageBoxA(NULL, "Failed to detect pawn.", "NotTacos's Skin Changer", MB_OK);
				}
				MessageBoxA(NULL, "Successfully changed cosmetic. Enjoy!", "NotTacos's Skin Changer", MB_OK);
			}
		}
		ImGui::End();

		ImGui::Render();

		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI GuiThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	std::cout << "Initialized GUI.";
	return TRUE;
}