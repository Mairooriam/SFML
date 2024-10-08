ProjectDir = C:\Users\35850\Desktop\repositories\SFML
SFMLDir = C:\Users\35850\Documents\libraries\SFML-2.6.1
OpenALDir = C:\path\to\openal

all: compile link

compile:
	g++  -c main.cpp -I"$(SFMLDir)/include" -I"$(ProjectDir)/include" -DSFML_STATIC 
	g++  -c source/ball.cpp -I"$(SFMLDir)/include" -I"$(ProjectDir)/include" -DSFML_STATIC
	g++  -c source/physics.cpp -I"$(SFMLDir)/include" -I"$(ProjectDir)/include" -DSFML_STATIC
	g++  -c source/game.cpp -I"$(SFMLDir)/include" -I"$(ProjectDir)/include" -DSFML_STATIC
	g++  -c source/vectorOperators.cpp -I"$(SFMLDir)/include" -I"$(ProjectDir)/include" -DSFML_STATIC
	g++  -c source/debugOverlay.cpp -I"$(SFMLDir)/include" -I"$(ProjectDir)/include" -DSFML_STATIC
	g++  -c source/uiElements.cpp -I"$(SFMLDir)/include" -I"$(ProjectDir)/include" -DSFML_STATIC
	g++  -c source/enums.cpp -I"$(SFMLDir)/include" -I"$(ProjectDir)/include" -DSFML_STATIC
link:
	g++ main.o ball.o physics.o game.o vectorOperators.o debugOverlay.o uiElements.o enums.o -o main -L"$(SFMLDir)/lib" -L"$(OpenALDir)/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mconsole -lsfml-main -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lOpenAL32 -static-libgcc -static-libstdc++ -static
clean:
	rm -f main *.o