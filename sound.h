#include<queue>
#include<iostream>
#include<SFML/Audio.hpp>

namespace aether {
    /// An object that takes certain specifications and fires off a sound effect immediately upon construction.
    /// The objects themselves should be made with 'new'.
    /// Manual deletion is not advised as the aether::sound objects self-manage their data.
    class sound {
        private:
            /// Controls the current volume of existing sound effects.
            static float volume;
            /// A container holding constructed sound effects.
            static std::queue<aether::sound*> loadedSounds;
            /// A function called by the sound effect constructor which activates the sound effect GC heuristic.
            static void flush();
            /// The descriptor/buffer pair for the sound effect file: Credit- SFML
            sf::Sound* soundDescriptor;
            sf::SoundBuffer* soundBuffer;
        public:
            /// The constructor for a sound effect object.
            /// Once constructed it fires off immediately with the specified behaviors.
            /// NOTE: Spatialization only works for mono tracks
            sound(
              std::string fileName,                     /// The file name for the sound file.
              float maxV = 100,                         /// The max volume allowable for the sound file. Useful in conjunction with soundDelta.
              float soundDelta = 0,                     /// A fixed volume to undershot/overshot the current volume setting. Can be used to make quieter or louder noises.
              float pitch = 1,                          /// Sets the pitch. Values below 1 lowers the pitch, values above 1 increases the pitch.
              bool relativeToListener = true,           /// Sets if the sound occurs relative to the player. Disabling will allow it to exist in global coordinates.
              sf::Vector2f pos = sf::Vector2f(0,0),     /// Sets the position of the sound, normally at (0,0) relative to the player to disable spatialization.
              float soundRadius = 1,                    /// If using spatialization this will affect how far a sound can be heard before attentuation takes place.
              float attenuation = 1                     /// Sets the attenuation (sound falloff magnitude) of the sound effect as the listener moves away.
            );
            ~sound();
            /// Gets volume for sound effects: 0 >= volume >= 100
            static float getVolume();
            /// Sets volume for sound effects: 0 >= volume >= 100
            static void setVolume(float newVolume);
    };
}
