#pragma once

#include "rBuild.hpp"

#include "rString.hpp"
#include "stream/rIStream.hpp"

namespace recondite {
	class RECONDITE_API iResourceManager {
	public:
		virtual rIStream* Open(const rString& handle) = 0;
		virtual bool Close(rIStream* stream) = 0;
	};
}