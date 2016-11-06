#pragma once

#include "rColor.hpp"

struct ModelViewerSettings {
	rColor skeletonLineColor;
	rColor skeletonTextColor;

	bool renderSkeleton;
	bool renderBoneNames;

public:
	ModelViewerSettings() : 
		skeletonLineColor(rColor::Green), 
		skeletonTextColor(rColor::White), 
		renderSkeleton(true),
		renderBoneNames(true) {}
};