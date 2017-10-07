# AetherSoundLibrary
Aether Engine's Audio Module built with SFML

This is the Audio Module of the Aether Game Engine Project. It can be used standalone and should be cross-platform compatible(not tested) assuming the following...
1. sfml-audio/sfml-system .dll/.so files are provided for target platform/architecture
2. libsfml-audio.a is provided for correct target platform/architecture. 

The version hosted in the respotory is Windows 64bit compiled with MinGW through git bash.
For usage refer to the specific .h files.

Built using SFML. 

It supports the following features:
	1. Memory is managed automatically within the modules. 
	2. Construction is protected, and even if you delete a retrieved object the santicty of the manager isn't violated.
	3. Two interfaces, one for long lived BGM and the other for short lived SE optimized for their respective purposes.
	4. Being built with SFML sound spatialization is available in an easy to use interface.
	5. Sound volume is automatically managed through a rule based architecture.
	
Setup-
	When making the correct modifications as listed at the start of the README run the makefile and it should compile a new libaether-sound.a.
	Now with your new static link library provide it with a project and statically link this file providing the SFML/include path to the compiler/IDE.
	It should compile fine and the library will be ready to use.
	
Being mostly for personal use I don't have much of an obligation to create forks for many architectures at the moment. If I get to the point where I have a game ready to release
I will create forks for different Windows/Linux architectures. I do not own a Mac so a Mac user would have to provide their own forks. Users can provide their own forks if they wish.