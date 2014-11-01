recondite
=========

c++ framework for creating graphics applications

**Requirements**

[CMake](http://www.cmake.org/)

[SDL 1.2](http://www.libsdl.org/)

[GLEW](http://glew.sourceforge.net/)

[gtest](http://code.google.com/p/googletest/)

[freetype](http://www.freetype.org/)

[wxWidgets](http://www.wxwidgets.org/)

**Building on Windows**
1.  Set environment variables:
    - GLEW_ROOT
    - SDL_ROOT
    - GTEST_ROOT

**Building on Linux**

1.  Install required packages:  
    -   sudo apt-get install libgtest-dev libglew-dev libsdl1.2-dev
2.  Build gtest
    - cd /usr/src/gtest
    - sudo cmake CMakeLists.txt
    - sudo make
    - sudo cp *.a /usr/lib
