#include<iostream>
#include<unordered_map>
#include<SFML/Audio.hpp>

namespace aether {
    class bgm {
        private:
            /// The bgm volume setting.
            static float volume;
            /// Keeps a list of BGMs loaded by filename to prevent duplicates from being loaded.
            /// Assists with bgm's memory management.
            static std::unordered_map<std::string,aether::bgm*> loadedBGM;
            /// Contains the internal BGM file descriptor. Credit to SFML
            sf::Music* music;
            /// The internal file name, allows the destructor to manage removing itself from the hash table.
            std::string internalFileName;
            /// Max allowable volume for the bgm to play.
            float maxVolume;
            /// How much volume to over/undershoot at any time for louder or quieter tunes.
            float soundDelta;
            /// Function to manage the volume of a BGM, called automatically as needed.
            void updateVolume();
        public:
            /// Retrieves an existing BGM track returning NULL if it cannot be found.
            static aether::bgm* get(std::string filename);
            /// Stops and Erases an existing BGM if it is loaded, does nothing otherwise.
            /// Called automatically if a BGM's destructor is called directly.
            static void erase(std::string filename);
            /// Stops and Erases all loaded BGMs.
            static void flush();
            /// Gets bgm volume.
            static float getVolume();
            /// Sets bgm volume.
            static void setVolume(float newVolume);
            /// Creates bgm instance automatically loading it into bgm's memory manager.
            /// If an existing bgm from the same file exists then it's destructor is called and is replaced with the new instance.
            /// If the sound should have an absolute position disable relativeToListener.
            /// NOTE: Spatialization only works for mono tracks
            bgm(std::string fileName,float maxV = 100, float soundD = 0, bool setLoop = false, bool relativeToListener = true);
            /// Stops existing bgm then clears any heap objects it is holding onto.
            ~bgm();
            /// Equivalent to Media Player Play
            void play();
            /// Equivalent to Media Player Pause
            void pause();
            /// Equivalent to Media Player Stop
            void stop();
            /// Changes the max volume for the bgm
            void setMaxVolume(float newMaxVolume);
            /// Changes how much to under/overshoot the sound for the bgm.
            void setSoundDelta(float newDelta);
            /// Changes the pitch. Values between 0 and 1 lower the pitch, values > 1 increase the pitch.
            void setPitch(float newPitch);
            /// Returns the current status of the BGM
            enum Status {Stopped,Paused,Playing};
            bgm::Status getStatus();
            /// Gets the position either relative to Listener or at absolute coordinates depending on relativeToListener flag.
            /// Affects spatialization
            sf::Vector2f getPosition();
            /// Sets the position either relative to Listener or at absolute coordinates depending on relativeToListener flag.
            /// Affects spatialization
            void setPosition(sf::Vector2f position);
            /// Gets the sound radius, how far away the Listener must be for attentuation to occur.
            /// Affects spatialization
            float getSoundRadius();
            /// Sets the sound radius, how far away the Listener must be for attentuation to occur.
            /// Affects spatialization
            void setSoundRadius(float radius);
            /// Gets the current attentuation, the magnitude of falloff as the sound radius is left.
            /// Affects spatialization
            float getAttenuation();
            /// Sets the current attentuation, the magnitude of falloff as the sound radius is left.
            /// Affects spatialization
            void setAttenuation(float attenuation);
    };
}
