#include<SFML/Audio.hpp>
namespace aether{
    class listener {
        public:
            /// Gets the 2D coordinates for the SFML Listener.
            static sf::Vector2f getPosition();
            /// Sets the SFML Listener to a location in 2D space.
            static void setPosition(sf::Vector2f pos);
            /// Gets the global listener volume: 0 >= volume >= 100
            static float getVolume();
            /// Sets the global listener volume: 0 >= volume >= 100
            static void setVolume(float newVolume);
    };
}
