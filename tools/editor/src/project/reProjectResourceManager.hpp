#pragma once

#include <set>

#include "interface/riResourceManager.hpp"
#include "stream/rIFileStream.hpp"

#include "reProject.hpp"

class reProjectResourceManager : public recondite::iResourceManager {
public:
	reProjectResourceManager(reProject* project);

	virtual rIStream* Open(const rString& handle) override;
	virtual bool Close(rIStream* stream) override;

private:
	reProject* _project;
	std::set<rIStream*> _openHandles;
};