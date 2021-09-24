cl /DGLEW_STATIC /DIRRKLANG_STATIC main.cpp src/*.cpp ^
   -I dependencies/GLFW/include -I dependencies/GLEW/include -I dependencies/glm -I dependencies/irrKlang/include -I dependencies/FreeType/include -I dependencies/FreeType/include/freetype^
   -link dependencies/GLFW/lib/glfw3dll.lib dependencies/GLEW/lib/glew32s.lib dependencies/irrKlang/lib/Winx64-visualStudio/irrKlang.lib dependencies/FreeType/lib/freetype.lib^
   opengl32.lib user32.lib gdi32.lib legacy_stdio_definitions.lib
