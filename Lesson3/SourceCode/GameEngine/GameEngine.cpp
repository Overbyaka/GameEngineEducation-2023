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
#include "InputHandler.h"


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
    InputHandler* inputHandler = new InputHandler();

    const int n = 100;
    GameObject* cube[n];
    std::srand(std::time(nullptr));

    for (int i = 0; i < n; i++)
    {
        int random = std::rand() % 3;
        switch (random)
        {
            case 0:
                cube[i] = new JumpCubeGameObject();
                break;
            case 1:
                cube[i] = new ControlCubeGameObject();
                break;
            case 2:
                cube[i] = new RandomCubeGameObject();
                break;
        }
        renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube[i]->GetRenderProxy());
        float x = std::rand() % 50 / 10.0f;
        float y = std::rand() % 50 / 10.0f;
        float signX = std::rand() % 2;
        float signY = std::rand() % 2;
        if (signX == 0 && signY == 0)
            cube[i]->SetPosition(x, 0.0f, y);
        else if(signX == 0 && signY == 1)
            cube[i]->SetPosition(x, 0.0f, -y);
        else if (signX == 1 && signY == 0)
            cube[i]->SetPosition(-x, 0.0f, y);
        else
            cube[i]->SetPosition(-x, 0.0f, -y);
    }

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    float newPositionX = 0.0f;

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
            inputHandler->Update();

            float t = 0;
            timer.Tick();
            t = sin(timer.TotalTime())*2;

            for (int i = 0; i < n; i++)
            {
                float velocity = 0.0f;
                if (inputHandler->GetInputState().test(eIC_GoLeft))
                    velocity -= 0.4f;
                if (inputHandler->GetInputState().test(eIC_GoRight))
                    velocity += 0.4f;
                cube[i]->Move(velocity, timer.TotalTime());
            }

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
