# Zelda1: Quest 1

Directory Structure
====================

```
Zelda1 (Solution File)
  |
  +-- Assets
  |   |
  |   +-- Config (XML Configuration Files)
  |   |
  |   +-- Images (PNG Files)
  |
  +-- Game (binaries)
  |
  +-- Source (Source code) (Project file)
  |
  +-- Documentation (Project Specifications)
  |
  +-- Obj (compile time intermediaries objects)
  |
  +-- Third Party
  |
  +-- External (libjpeg-9.dll, libpng16-16.dll, etc.)
      |
      +-- SDL2.0.5 (SDL2.DLL, SDL2main.lib)
      |
      +-- SDL_Image2.0.1 (SDL2_image.dll)
```

Project Overview
================

We will be programming an open-world, Zelda 1 simulation in the 2-
dimensional plane, viewed top-down. The instructor has provided all
the necessary images (although you are allowed to create and use your
own sprites if they have the same roles and complexity). Your task is
to implement an SDL2-driven, window-based game through which you can
observe the independent simulation of multiple types of objects.

What is more important than the simple functionality in this programs is
that it builds up an abstract and flexible back-end with which we can
build substantially more complex programs later in the semester. The
instructor has provided you with the Source.cpp file which contains the
declaration and construction of a game object.The Game object contains a
GraphicsDevice and InputDevice which are wrappers that abstract all of the
SDL2-specific calls necessary to interact with and display the game state to
User-defined calls. The GraphicsDevice conducts all the screen management
and hardware rendering and the InputDevice handles all of the keyboard inputs.
Abstracting these calls as objects allow for the Game to be written independently
of the Media Library (e.g., if done properly, this game could be written to
run in SDL, OpenGL, or DirectX simply by rewriting the GraphicsDevice and
InputDevice classes. The Game object also contains the game logic and game
asset management.

Project Enhancements
====================

1. Source Code Repository
    https://ualr-projects.visualstudio.com/Zelda1/Zelda1%20Team
    https://ualr-projects.visualstudio.com/Zelda1/Zelda1%20Team/_versionControl

2. Windows Unicode Compliant

3. Builds and in both Release & Debug Modes, without warnings or errors on /W4

4. Latest versions of SDL and SDL_Image libraries built and incorporated into this project

5. Main Window can be Maximized and is Re-sizable.

Noted Deviations from Original Project Template
===============================================

1.  Various portions of the Project was reorganized, modified or otherwise fixed.
    For example, the Release build was previously nonfunctional.

2.  XmlLite was used in lieu of TinyXML.
    TinyXML was removed.  XML parsing was done in a similar manner as Project0.

3.  Latest versions of SDL & SDL_Image were built and used.

4.  Changes to the Library & Executable naming conventions.

    *  Release Build outputs was not changed
    *  Debug Builds uses the 'D' suffix and links in 'D' suffix named dependencies

5.  Various additional classes implemented and used.  

    *  CActor serves as the base class in lieu of Object.
    *  Various class factories implemented as generic class templates.

6.  Additional checks for memory leaks added.  This was due mostly to issues encountered with smart pointers.

7.  All bugs encountered in sample code were fixed.

8.  Some new image PNG files were added and used, specifically for Red/Blue Leever.

    *  Red Arrow & Blue Arrow were used in order to better track "direction" based calculation implementations

9.  Black Background was used.


Implementation Specifics
========================
1. Keyboard Events  

   *  UP, DOWN, LEFT, RIGHT : scrolls the view
   *  TAB : changes view focus and centers camera on next CActor
   *  \- : appropriately handles changing the Windows size.
   *  ESCAPE : exits the application
   *  SPACEBAR : pauses and resumes application

2. Agent Movement(s)

   *  RED OCTOROK : A big circle with a randomly determined radius.
   *  All others : In the direction, determined by the Angle given from the XML file, at a random speed, for a random distance (and then returning).
   *  BLUE OCTOROK : Spins while moving.
   *  RED & BLUE LEEVERS : points in the direction they are moving.

3. The program was implemented as a Windows Application and not a Console.

   *  The console window looked cheesy and I don't have any use for it as my debug output is handled by a connected debugger via the Windows API OutputDebugString.

Issues Encountered
==================

A floating point rounding issue, both in my vector2d library and with std::cosine.
* After some research, I implemented the following "hack" to get around it for now:  

```c++
template<class _Ty>
inline bool fEqual(const _Ty& x, const _Ty& y, int iEpsilonFactor) noexcept
{
    if (x == y)
    {
        return true;
    }
    else
    {
        _Ty nDelta = std::abs(x - y);
        _Ty nTolerance = iEpsilonFactor * std::numeric_limits<_Ty>::epsilon();
        return (nDelta <= nTolerance);
    }
};
```

