#include"listener.h"
namespace aether {
    sf::Vector2f listener::getPosition(){
        sf::Vector3f Position3D = sf::Listener::getPosition();
        return sf::Vector2f(Position3D.x,Position3D.y);
    }
    void listener::setPosition(sf::Vector2f pos){
        sf::Listener::setPosition(pos.x,pos.y,0);
    }
    float listener::getVolume(){
        return sf::Listener::getGlobalVolume();
    }
    void listener::setVolume(float newVolume){
        sf::Listener::setGlobalVolume(newVolume);
    }
}
