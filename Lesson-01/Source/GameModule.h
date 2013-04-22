// ============================================================================
//
//	Copyright (C) 2013 Josh Vega.
//
//	This file is licensed under the GNU LGPLv3 license. For the license text,
//	please visit: http://opensource.org/licenses/LGPL-3.0.
//
// ============================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "InputModule.h"
#include "GraphicsModule.h"
#include "SoundModule.h"
#include "SceneModule.h"

class GameModule {
public:
    GameModule(InputModule input, GraphicsModule graphics, SoundModule sound, SceneModule scene);

    void Initialize(HINSTANCE &instance);
    void Shutdown(void);

    void Show(bool show);

    bool MainLoop(MSG *msg);

private:
    InputModule *inputPtr;
    GraphicsModule *graphicsPtr;
    SoundModule *soundPtr;
    SceneModule *scenePtr;

    HWND window;
    WNDCLASSEX wndClass;
};


static RECT windowSize = {0, 0, 1280, 720};

LRESULT CALLBACK WndProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam);