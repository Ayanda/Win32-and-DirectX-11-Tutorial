// ============================================================================
//
//	Copyright (C) 2013 Josh Vega.
//
//	This file is licensed under the GNU LGPLv3 license. For the license text,
//	please visit: http://opensource.org/licenses/LGPL-3.0.
//
// ============================================================================

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "GameModule.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow) {
    MSG msg;

    InputModule input = InputModule();
    GraphicsModule graphics = GraphicsModule();
    SoundModule sound = SoundModule();
    SceneModule scene = SceneModule();

    GameModule game = GameModule(input, graphics, sound, scene);

    game.Initialize(instance);

    game.Show(true);

    // Main loop goes here.
    if (game.MainLoop(&msg) != 0) {
        MessageBox(NULL, L"Game loop ended.\nProgram will now close.", L"QUIT", MB_OK | MB_ICONERROR);

        game.Show(false);
        game.Shutdown();

        return (int)msg.wParam;
    }

    return 0;
}