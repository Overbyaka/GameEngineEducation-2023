// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"
//#include "INIReader.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();

    GameObject* cube = new CubeGameObject();
    renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    //INIReader reader("../Assets/Configs/actionmap.ini");

    /*if (reader.ParseError() < 0) {
        //"Can't load '.ini'";
        return 1;
    }
    char config[2];
    config[0] = reader.Get("Keyboard", "GoLeft", "UNKNOWN")[0];
    config[1] = reader.Get("Keyboard", "GoRight", "UNKNOWN")[0];*/

    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            /*float t = 0;
            timer.Tick();
            t = sin(timer.TotalTime())*2;
            cube->SetPosition(t, 0.0f, 0.0f);*/

            float speed = 0.2f;

            switch (msg.message)
            {
                case WM_CHAR: // WM_KEYDOWN doesnt work ??
                    if (GetAsyncKeyState(0x41)) // A
                        cube->AddX(-speed);
                    else if (GetAsyncKeyState(0x44)) // D
                        cube->AddX(speed);
                    break;
                default:
                    break;
            }



            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
