#pragma once

#include "rBuild.hpp"
#include "rDefs.hpp"

#include "interface/riResourceManager.hpp"

namespace recondite {
	class RECONDITE_API ResourceManager : public iResourceManager {
	public:
		virtual rIStream* Open(const rString& handle) override;
		virtual bool Close(rIStream* stream) override;
	};
}
