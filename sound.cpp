#include"sound.h"

namespace aether {
    float sound::volume = 75;
    std::queue<aether::sound*> sound::loadedSounds = std::queue<aether::sound*>();
    void sound::flush(){
        /// Repeat deleting sound effects from the front that are finished playing.
        while(!loadedSounds.empty() && (loadedSounds.front())->soundDescriptor->getStatus() == sf::SoundSource::Status::Stopped){
            delete loadedSounds.front();
            loadedSounds.pop();
        }
    }
    sound::sound(std::string fileName,
                 float maxV,
                 float soundDelta,
                 float pitch,
                 bool relativeToListener,
                 sf::Vector2f pos,
                 float soundRadius,
                 float attenuation
    ){
        /// Initialize Global Listener direction if it hasn't been yet.
        static bool init = false;
        if(!init){
                sf::Listener::setDirection(0.f, 0.f, -1.f);
                init = true;
        }
        /// Run GC heuristic.
        aether::sound::flush();
        /// Build Object
        soundBuffer = new sf::SoundBuffer();
        soundBuffer->loadFromFile(fileName);
        soundDescriptor = new sf::Sound();
        soundDescriptor->setBuffer(*soundBuffer);
        soundDescriptor->setLoop(false);
        soundDescriptor->setPitch(pitch);
        soundDescriptor->setRelativeToListener(relativeToListener);
        soundDescriptor->setPosition(pos.x,pos.y,0);
        soundDescriptor->setMinDistance(soundRadius);
        soundDescriptor->setAttenuation(attenuation);
        if(aether::sound::volume > maxV) soundDescriptor->setVolume(maxV);
        else soundDescriptor->setVolume(aether::sound::volume);
        soundDescriptor->setVolume(soundDescriptor->getVolume() + soundDelta);
        /// Add to list of sounds and play.
        loadedSounds.push(this);
        soundDescriptor->play();
    }
    sound::~sound(){
        delete soundDescriptor;
        delete soundBuffer;
    }
    float sound::getVolume(){
        return sound::volume;
    }
    void sound::setVolume(float newVolume){
        sound::volume = newVolume;
    }

}
