// ============================================================================
//
//	Copyright (C) 2013 Josh Vega.
//
//	This file is licensed under the GNU LGPLv3 license. For the license text,
//	please visit: http://opensource.org/licenses/LGPL-3.0.
//
// ============================================================================

#include "GameModule.h"

LRESULT CALLBACK WndProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_DESTROY: {
            PostQuitMessage(0);

            return 0;
        }
    }

    return DefWindowProc(wnd, message, wParam, lParam);
}

GameModule::GameModule(InputModule *input, GraphicsModule *graphics, SoundModule *sound, SceneModule *scene) {
    this->inputPtr = input;
    this->graphicsPtr = graphics;
    this->soundPtr = sound;
    this->scenePtr = scene;
}

void GameModule::Initialize(HINSTANCE &instance) {
    if (!this->inputPtr->Initialize()) {
        MessageBox(NULL, L"Error initializing input module.\nProgram will now close.", L"Error", MB_OK | MB_ICONERROR);

        ExitProcess(1);
    }

    if (!this->graphicsPtr->Initialize()) {
        MessageBox(NULL, L"Error initializing graphics module.\nProgram will now close.", L"Error", MB_OK | MB_ICONERROR);

        ExitProcess(2);
    }

    if (!this->soundPtr->Initialize()) {
        MessageBox(NULL, L"Error initializing sound module.\nProgram will now close.", L"Error", MB_OK | MB_ICONERROR);

        ExitProcess(3);
    }

    if (!this->scenePtr->Initialize()) {
        MessageBox(NULL, L"Error initializing scene module.\nProgram will now close.", L"Error", MB_OK | MB_ICONERROR);

        ExitProcess(4);
    }

    ZeroMemory(&this->wndClass, sizeof(WNDCLASSEX));

    // Create our window description.
    this->wndClass.cbSize = sizeof(WNDCLASSEX);
    this->wndClass.style = CS_HREDRAW | CS_VREDRAW;
    this->wndClass.lpfnWndProc = WndProc;
    this->wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    this->wndClass.hInstance = instance;
    this->wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    this->wndClass.lpszClassName = L"Win32-And-DirectX-11-Tutorial";

    // Register our window description.
    RegisterClassEx(&this->wndClass);

    // Make sure the window working space is the size we specificed.
    AdjustWindowRect(&windowSize, WS_OVERLAPPEDWINDOW, FALSE);

    // Position the window in the center of the screen.
    int posX = (GetSystemMetrics(SM_CXSCREEN) - (windowSize.right - windowSize.left)) / 2;
    int posY = (GetSystemMetrics(SM_CYSCREEN) - (windowSize.bottom - windowSize.top)) / 2;

    // Create the window.
    this->window = CreateWindowEx(NULL, L"Win32-And-DirectX-11-Tutorial", L"Win32 And DirectX 11 Tutorial Series",
                                    WS_OVERLAPPEDWINDOW, posX, posY, (windowSize.right - windowSize.left),
                                    (windowSize.bottom - windowSize.top), NULL, NULL, instance, NULL);
}

void GameModule::Shutdown(void) {
    this->inputPtr->Shutdown();
    delete this->inputPtr;
    this->inputPtr = NULL;

    this->graphicsPtr->Shutdown();
    delete this->graphicsPtr;
    this->graphicsPtr = NULL;

    this->soundPtr->Shutdown();
    delete this->soundPtr;
    this->soundPtr = NULL;

    this->scenePtr->Shutdown();
    delete this->scenePtr;
    this->scenePtr = NULL;
}

void GameModule::Show(bool show) {
    if (show == true) {
        ShowWindow(this->window, SW_SHOW);
    } else {
        ShowWindow(this->window, SW_HIDE);
    }
}

bool GameModule::MainLoop(MSG *msg) {
    bool running = true;

    while (running) {
        while (PeekMessage(msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(msg);
            DispatchMessage(msg);
        }

        if (msg->message == WM_QUIT) {
            break;
        }
    }

    return 0;
}