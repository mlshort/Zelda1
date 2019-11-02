/**
 *  @file       Main.cpp
 *  @brief      int main(int argc, char* argv[]) function application entry point
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 *
 *    We will be programming an open-world, Zelda 1 simulation in the 2-
 *    dimensional plane, viewed top-down. The instructor has provided all
 *    the necessary images (although you are allowed to create and use your
 *    own sprites if they have the same roles and complexity). Your task is
 *    to implement an SDL2-driven, window-based game through which you can
 *    observe the independent simulation of multiple types of objects.
 *
 *    What is more important than the simple functionality in this programs is
 *    that it builds up an abstract and flexible back-end with which we can
 *    build substantially more complex programs later in the semester. The
 *    instructor has provided you with the Source.cpp file which contains the
 *    declaration and construction of a game object.The Game object contains a
 *    GraphicsDevice and InputDevice which are wrappers that abstract all of the
 *    SDL2-specific calls necessary to interact with and display the game state to
 *    User-defined calls. The GraphicsDevice conducts all the screen management
 *    and hardware rendering and the InputDevice handles all of the keyboard inputs.
 *    Abstracting these calls as objects allow for the Game to be written independently
 *    of the Media Library (e.g., if done properly, this game could be written to
 *    run in SDL, OpenGL, or DirectX simply by rewriting the GraphicsDevice and
 *    InputDevice classes. The Game object also contains the game logic and game
 *    asset management.
 *
 *  <b>Cite:</b>
 *             * Example code from Dr. Bush, Sean Orme
 *             * Simple DirectMedia Layer (SDL) Wiki, https://wiki.libsdl.org/
 */

#ifdef _DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>
#endif
#ifdef _DEBUG
    #define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
    #define new DEBUG_NEW
#endif

#include "Common.h"
#include <Windows.h>
#include <iostream>
#include <random>
#include <memory>

#include "SDL.h"
#include "SDL_Image.h"

#include "Utility\DebugUtils.h"

#include "Game.h"

constexpr const TCHAR g_szLevelConfigFile[]  = _T("\\Assets\\Config\\level1.xml");
constexpr const TCHAR g_szObjectConfigFile[] = _T("\\Assets\\Config\\objects.xml");

// for testing
constexpr const TCHAR g_szObject_ArrowsConfigFile[] = _T("\\Assets\\Config\\objects_arrows.xml");


TCHAR g_szModulePath[MAX_PATH] = { 0 };


int main(int argc, char* argv[])
{
    argc;
    argv;

    {
        util::GetModulePath(g_szModulePath, _countof(g_szModulePath) - 1);
        //========================================
        //Construct Game
        //========================================
        CGame game;

        if (!game.Initialize())
        {
            util::DebugTrace(_T("Game could not Initialize!"));
            exit(1);
        }

        //========================================
        //Load Level
        //========================================
        tstring strFileName(g_szModulePath);
//        strFileName += g_szObjectConfigFile;
        strFileName += g_szObject_ArrowsConfigFile;

        if (!game.LoadObjectFile(strFileName.c_str()))
        {
            util::DebugTrace(_T("Game could not load object file: [%s] \n"), strFileName.c_str());
            exit(1);
        }

        strFileName = g_szModulePath;
        strFileName += g_szLevelConfigFile;

        if (!game.LoadLevelFile(strFileName.c_str()))
        {
            util::DebugTrace(_T("Game could not load level file: [%s] \n"), strFileName.c_str());
            exit(1);
        }

        //========================================
        //Main Game Loop
        //========================================
        bool bQuit = false;

        //While the user hasn't quit
        while (!bQuit)
        {
            bQuit = game.Run();
        }

        //========================================
        // Clean-up
        //========================================
        game.ShutDown();
    }

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif

    return 0;

}

