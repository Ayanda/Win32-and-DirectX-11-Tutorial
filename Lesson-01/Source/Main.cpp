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

    // Make sure our unreferenced parameters don't cause any problems.
    UNREFERENCED_PARAMETER(prevInstance);
    UNREFERENCED_PARAMETER(cmdLine);
    UNREFERENCED_PARAMETER(cmdShow);

    // Initialize all our modules.
    InputModule *input = new InputModule();
    GraphicsModule *graphics = new GraphicsModule();
    SoundModule *sound = new SoundModule();
    SceneModule *scene = new SceneModule();

    // Initialize our game module.
    GameModule game = GameModule(input, graphics, sound, scene);

    // Check to make sure everything is working properly.
    game.Initialize(instance);

    // Show the game window.
    game.Show(true);

    // Main loop goes here.
    if (!game.MainLoop(&msg)) {
        MessageBox(NULL, L"Game loop ended.\nProgram will now close.", L"QUIT", MB_OK | MB_ICONEXCLAMATION);

        game.Show(false);
        game.Shutdown();

        return (int)msg.wParam;
    }

    return 0;
}