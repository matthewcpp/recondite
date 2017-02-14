#include "rBehaviorManager.hpp"

#include <map>

namespace recondite {
	struct BehaviorManager::Impl {
		std::map<uint32_t, BehaviorFunction> functionMap;
		std::map<uint32_t, rString> typeIndexMap;
		std::map<rString, uint32_t> classNameMap;

		uint32_t typeIndex;

		Impl() : typeIndex(1) {}
	};

	BehaviorManager::BehaviorManager() {
		_impl = new Impl();
	}

	BehaviorManager::~BehaviorManager() {
		delete _impl;
	}

	Behavior* BehaviorManager::CreateBehavior(const rString& className) {
		auto result = _impl->classNameMap.find(className);

		if (result != _impl->classNameMap.end()) {
			uint32_t typeIndex = _impl->classNameMap[className];

			BehaviorFunction behaviorFunction = _impl->functionMap[typeIndex];
			Behavior* behavior = behaviorFunction();
			behavior->_typeIndex = typeIndex;

			return behavior;
		}
		else {
			return nullptr;
		}
	}

	bool BehaviorManager::DefineBehavior(const rString& className, BehaviorFunction entityFunction) {
		if (_impl->classNameMap.count(className)) {
			return false;
		}
		else {
			uint32_t typeIndex = _impl->typeIndex++;

			_impl->functionMap[typeIndex] = entityFunction;
			_impl->typeIndexMap[typeIndex] = className;
			_impl->classNameMap[className] = typeIndex;

			return true;
		}
	}

	bool BehaviorManager::UndefineBehavior(const rString& className) {
		auto result = _impl->classNameMap.find(className);

		if (result == _impl->classNameMap.end()) {
			return false;
		}
		else {
			uint32_t typeIndex = result->second;

			_impl->functionMap.erase(typeIndex);
			_impl->typeIndexMap.erase(typeIndex);
			_impl->classNameMap.erase(result);

			return true;
		}
	}

	bool BehaviorManager::IsDefined(const rString& className) {
		return _impl->classNameMap.count(className) > 0;
	}

	rString BehaviorManager::GetClassName(Behavior* behavior) const {
		auto result = _impl->typeIndexMap.find(behavior->_typeIndex);

		if (result == _impl->typeIndexMap.end()) {
			return "";
		}
		else {
			return result->second;
		}
	}
}
