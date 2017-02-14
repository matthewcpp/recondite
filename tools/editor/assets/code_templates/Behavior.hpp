#pragma once

#include "rBehavior.hpp"

class __NAME__ : public recondite::Behavior{
		/**
		Called when the entity is created before any call to Update is made
		*/
		virtual void Init(rEngine* engine, const rString& id);
		
		/**
		Called every time the game engine updates
		*/
		virtual void Update();

		/**
		Called when the entity will be destroyed
		*/
		virtual void Uninit();
};