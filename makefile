main: main.cpp
	x86_64-w64-mingw32-g++ -std=c++14 listener.cpp sound.cpp bgm.cpp main.cpp -I..\SFML\include -L..\SFML\lib -lsfml-audio -o main.exe