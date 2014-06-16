#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Thor/Resources.hpp>
#include <Resources.h>
namespace My
{
class ResourceHandler
{
public:
    ResourceHandler();
    void Load();
    virtual ~ResourceHandler();
    std::shared_ptr<sf::Texture> GetTextures();
    std::shared_ptr<sf::SoundBuffer> GetAttack();
protected:
private:
    thor::ResourceCache<sf::Texture> c_Textures;
    thor::ResourceCache<sf::SoundBuffer> c_SoundBuffer;
    thor::ResourceKey<sf::Texture> k_Textures;
    thor::ResourceKey<sf::SoundBuffer> k_Attack;
};
}
#endif
