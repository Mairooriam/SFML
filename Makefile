ProjectDir = C:\Users\35850\Desktop\repositories\SFML
SFMLDir = C:\Users\35850\Documents\libraries\SFML-2.6.1
OpenALDir = C:\path\to\openal

all: compile link

compile:
	g++ -g -c main.cpp -I"$(SFMLDir)/include" -I"$(ProjectDir)/include" -DSFML_STATIC 
	g++ -g -c source/ball.cpp -I"$(SFMLDir)/include" -I"$(ProjectDir)/include" -DSFML_STATIC

link:
	g++ main.o ball.o -o main -L"$(SFMLDir)/lib" -L"$(OpenALDir)/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mconsole -lsfml-main -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lOpenAL32 -static-libgcc -static-libstdc++ -static
clean:
	rm -f main *.o