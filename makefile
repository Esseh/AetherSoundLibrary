# Set to SFML\include path
gpp=x86_64-w64-mingw32-g++ -std=c++14
SFML=..\SFML\include
build-listener: listener.o
	$(gpp) -c listener.cpp -I$(SFML) -o listener.o
build-sound: sound.o
	$(gpp) -c sound.cpp -I$(SFML) -o sound.o
build-bgm: bgm.o
	$(gpp) -c bgm.cpp -I$(SFML) -o bgm.o
build-lib: libaether-sound.a
	$(MAKE) build-listener
	$(MAKE) build-sound
	$(MAKE) build-bgm
	ar -x libsfml-audio.a
	ar rcs libaether-sound.a *.o
	rm *.o
build-main: main.exe
	$(gpp) main.cpp libaether-sound.a -I$(SFML) -o main.exe