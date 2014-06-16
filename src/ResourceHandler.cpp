#include "ResourceHandler.hpp"
using namespace My;
ResourceHandler::ResourceHandler()
    : k_Textures(thor::Resources::fromFile<sf::Texture>(RESOURCE_TEXTURES_PATH))
	, k_Attack(thor::Resources::fromFile<sf::SoundBuffer>(RESOURCE_ATTACK))
{
}
ResourceHandler::~ResourceHandler() 
{
}
void ResourceHandler::Load()
{
    c_Textures.setReleaseStrategy(thor::Resources::AutoRelease);
    c_Textures.acquire(k_Textures);
}
std::shared_ptr<sf::Texture> ResourceHandler::GetTextures()
{
    return c_Textures.acquire(k_Textures);
}
std::shared_ptr<sf::SoundBuffer> ResourceHandler::GetAttack()
{
	return c_SoundBuffer.acquire(k_Attack);
}
