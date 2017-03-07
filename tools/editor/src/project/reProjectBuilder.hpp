#pragma once

#include <wx/wx.h>
#include <wx/process.h>

#include "project/reComponent.hpp"

class reProjectBuilder {
public:
	reProjectBuilder(reComponent* component);

public:
	bool BuildAndRun(const wxString& level);
	bool Build();
	bool Configure();
	bool Open();
	bool IsBuilt();

	bool IsBuilding() const;
	void DoneBuilding();

public:
	void AssetBundleComplete();
	void ConfigurationComplete();

private:
	void BundleAssets();
	void ConfigureProject();

private:
	reComponent* _component;

	bool _assetsBundled;
	bool _isBuilding;
	bool _run;
	bool _open;

	wxString _level;
};