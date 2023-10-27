#pragma once

#include <map>
#include <memory>
#include <assert.h>

#include "SFML/Graphics.hpp"

namespace Textures
{
	enum ID {
		Airplane,
		Landscape,
		Missile
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void Load(Identifier id, const std::string& filePath)
	{
		std::unique_ptr<Resource> resrouce(new Resource());
		bool loaded = resrouce->loadFromFile(filePath);
		if (!loaded) throw std::runtime_error("ResourceHolder::Load - failed to load: " + filePath);

		auto inserted = _resourceMap.insert(std::make_pair(id, std::move(resrouce)));
		assert(inserted.second);
	}

	template <typename Parameter>
	void Load(Identifier id, const std::string& filePath, const Parameter& secondParam)
	{
		std::unique_ptr<Resource> resrouce(new Resource());
		bool loaded = resrouce->loadFromFile(filePath, secondParam);
		if (!loaded) throw std::runtime_error("ResourceHolder::Load - failed to load: " + filePath);

		auto inserted = _resourceMap.insert(std::make_pair(id, std::move(resrouce)));
		assert(inserted.second);
	}

	Resource& Get(Identifier id)
	{
		auto found = _resourceMap.find(id);
		assert(found != _resourceMap.end());
		return *(found->second);
	}

	const Resource& Get(Identifier id) const
	{
		auto found = _resourceMap.find(id);
		assert(found != _resourceMap.end());
		return *(found->second);
	}

private:
	std::map<Identifier, std::unique_ptr<Resource>> _resourceMap;
};
