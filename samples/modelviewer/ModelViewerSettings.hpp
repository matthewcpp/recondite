#pragma once

#include "rColor.hpp"

struct ModelViewerSettings {
	rColor skeletonLineColor;
	rColor skeletonTextColor;

	bool renderSkeleton;
	bool renderBoneNames;

	bool animatedModel;

public:
	ModelViewerSettings() : 
		skeletonLineColor(rColor::Green), 
		skeletonTextColor(rColor::White), 
		renderSkeleton(false),
		renderBoneNames(false),
		animatedModel(false) {}
};