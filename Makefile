all: compile link

compile:
	g++ -c main.cpp -I"C:\Users\35850\Documents\libraries\SFML-2.6.1\include" -DSFML_STATIC 
	

link:
	g++ main.o -o main -L"C:\Users\35850\Documents\libraries\SFML-2.6.1\lib" -L"C:\Users\35850\Documents\libraries\OpenAL 1.1 SDK\libs\Win64" -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lOpenAL32
clean:
	rm -f main *.o