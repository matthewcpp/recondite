#pragma once

#include "rBuild.hpp"

#include "rSize.hpp"
#include "rPoint.hpp"

namespace recondite { namespace import {
	class RectPacker {
	public:
		class Item {
		public:
			rSize sourceSize;
			rPoint packedLocation;
		};
	};
}}