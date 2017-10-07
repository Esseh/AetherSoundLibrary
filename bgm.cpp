#include<vector>
#include"bgm.h"
namespace aether {
    float bgm::volume = 75;
    std::unordered_map<std::string,aether::bgm*> bgm::loadedBGM = {};
    void bgm::updateVolume(){
        /// If current volume is above max volume use max volume instead.
        if(bgm::getVolume() > maxVolume) music->setVolume(maxVolume + soundDelta);
        /// Apply under/overshoot for sound volume.
        else music->setVolume(bgm::getVolume() + soundDelta);
        /// Do not allows volume values below 0.
        if(music->getVolume() < 0) music->setVolume(0);
        /// Do not allows volume values above 100.
        if(music->getVolume() > 100) music->setVolume(100);
    }
    aether::bgm* bgm::get(std::string filename){
        auto item = bgm::loadedBGM.find(filename);
        if(item == bgm::loadedBGM.end()) return NULL;
        return item->second;
    }
    void bgm::erase(std::string filename){
        auto item = bgm::loadedBGM.find(filename);
        if(item != bgm::loadedBGM.end()) delete item->second;
    }
    void bgm::flush(){
        /// Get each file Nnme
        std::vector<std::string> fileNames;
        for(auto i:loadedBGM) fileNames.push_back(i.first);
        /// Erase each element by file name
        for(auto fn:fileNames) bgm::erase(fn);
    }
    float bgm::getVolume(){
        return volume;
    }
    void bgm::setVolume(float newVolume){
        /// Do not allow global volume below 0.
        if(newVolume < 0) newVolume = 0;
        /// Do not allow global volume above 100.
        if(newVolume > 100) newVolume = 100;
        volume = newVolume;
        /// Update the volume for all existing BGM objects.
        for(auto i:loadedBGM) (i.second)->updateVolume();
    }
    bgm::bgm(std::string fileName,float maxV, float soundD, bool setLoop, bool relativeToListener){
        static bool init = false;
        /// If listener direction hasn't already been set then do so.
        if(!init){
            sf::Listener::setDirection(0.f, 0.f, -1.f);
            init = true;
        }
        /// Erase existing entry if duplicate exists.
        bgm::erase(fileName);
        /// Build object.
        music = new sf::Music();
        music->openFromFile(fileName);
        internalFileName = fileName;
        maxVolume = maxV;
        soundDelta = soundD;
        music->setLoop(setLoop);
        music->setRelativeToListener(relativeToListener);
        music->setVolume(bgm::getVolume());
        updateVolume();
        /// Insert into memory manager.
        bgm::loadedBGM.insert({fileName,this});
    }
    bgm::~bgm(){
        music->stop();
        delete music;
        loadedBGM.erase(internalFileName);
    }
    void bgm::play(){
        music->play();
    }
    void bgm::pause(){
        music->pause();
    }
    void bgm::stop(){
        music->stop();
    }
    void bgm::setMaxVolume(float newMaxVolume){
        maxVolume = newMaxVolume;
        updateVolume();
    }
    void bgm::setSoundDelta(float newDelta){
        soundDelta = newDelta;
        updateVolume();
    }
    void bgm::setPitch(float newPitch){
        music->setPitch(newPitch);
    }
    bgm::Status bgm::getStatus(){
        auto SFMLStatus = music->getStatus();
        if(SFMLStatus == sf::SoundSource::Status::Paused) return bgm::Status::Paused;
        if(SFMLStatus == sf::SoundSource::Status::Playing)return bgm::Status::Playing;
        if(SFMLStatus == sf::SoundSource::Status::Stopped)return bgm::Status::Stopped;
    }
    sf::Vector2f bgm::getPosition(){
        /// Convert internal 3D vector to 2D
        sf::Vector3f Position3D = music->getPosition();
        return sf::Vector2f(Position3D.x,Position3D.y);
    }
    void bgm::setPosition(sf::Vector2f position){
        /// Translate 2D vector to internal 3D one.
        music->setPosition(position.x,position.y,0);
    }
    float bgm::getSoundRadius(){
        return music->getMinDistance();
    }
    void bgm::setSoundRadius(float radius){
        music->setMinDistance(radius);
    }
    float bgm::getAttenuation(){
        return music->getAttenuation();
    }
    void bgm::setAttenuation(float attenuation){
        music->setAttenuation(attenuation);
    }
}
