compiler=x86_64-w64-mingw32-g++
SFML_PATH=..\SFML\include
build-lib: libaether-sound.a
	$(compiler) -std=c++14 -c listener.cpp -I$(SFML_PATH) -o listener.o
	$(compiler) -std=c++14 -c sound.cpp -I$(SFML_PATH) -o sound.o
	$(compiler) -std=c++14 -c bgm.cpp -I$(SFML_PATH) -o bgm.o
	ar -x libsfml-audio.a
	ar rcs libaether-sound.a *.o
	rm *.o
build-main: main.exe
	$(compiler) -std=c++14 main.cpp libaether-sound.a -I$(SFML_PATH) -o main.exe