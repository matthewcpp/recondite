#pragma once

#include "rBuild.hpp"

#include "rBehavior.hpp"
#include "rString.hpp"

namespace recondite {
	class RECONDITE_API BehaviorManager {
	public:
		BehaviorManager();
		~BehaviorManager();

	public:
		typedef Behavior*(*BehaviorFunction)();

	public:
		Behavior* CreateBehavior(const rString& className);
		bool DefineBehavior(const rString& className, BehaviorFunction entityFunction);
		bool UndefineBehavior(const rString& className);

		bool IsDefined(const rString& className);

		rString GetClassName(Behavior* behavior) const;

	private:
		struct Impl;
		Impl* _impl;
	};
}