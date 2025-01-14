/*
*   name: include/core/scene_int.hpp
*   origin: Citrus Engine
*   purpose: Provide scene internals
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_SCENE_INTERNALS_HPP__
#define CITRUS_ENGINE_SCENE_INTERNALS_HPP__

#include "core/vector.hpp"
#include "core/object.hpp"
#include "core/pair.hpp"

namespace engine
{
	namespace internals
	{
		typedef void (*sceneConstructorPtr_t(void));
		class scene
		{
			public:
			int ID;
			// Scenes have special constructors generated to initalize everything in a scene.
			sceneConstructorPtr_t constructor;
			// TODO: Add a type for shaders
			// All objects in a scene
			Vector<object> objects;
			bool is2D;
		};
		
		extern scene *curScene;
		extern map<scene, int> scenes;
		extern bool loadNecesary;
		extern int currentScene; // Used with loadNecessary to load the next scene when timing lines up.

		extern size_t frameDelta;
		extern size_t frameDur;

		namespace physics
    	{	
        	extern size_t physicsDelta;
        	extern size_t physicsDur;
		}
	};
};

#endif