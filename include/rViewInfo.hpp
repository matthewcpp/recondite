#ifndef R_VIEWINFO_HPP
#define R_VIEWINFO_HPP

#include "rBuild.hpp"

#include "rViewport.hpp"
#include "ui/ruiOverlay.hpp"

class RECONDITE_API rViewInfo {
public:
	rViewport* viewport;
	ruiOverlay* overlay;
};

#endif