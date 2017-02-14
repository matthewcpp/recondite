#pragma once

#include <cstdint>

#include "rBuild.hpp"
#include "rString.hpp"

class rEngine;

namespace recondite {
	/**
	Abstract class that encapsulates scriptable functionality which can be attached to objects
	*/
	class RECONDITE_API Behavior {
	public:
		Behavior() :_typeIndex(0) {}
		virtual ~Behavior() {}

	public:
		/**
		Called when the entity is created before any call to Update is made
		*/
		virtual void Init(rEngine* engine, const rString& id) {}
		
		/**
		Called every time the game engine updates
		*/
		virtual void Update() {}

		/**
		Called when the entity will be destroyed
		*/
		virtual void Uninit() {}

		/**
		Gets The type identifier of this behavior
		*/
		inline uint32_t GetTypeIndex() const;

		uint32_t _typeIndex;
	};

	inline uint32_t Behavior::GetTypeIndex() const {
		return _typeIndex;
	}
}