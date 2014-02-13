#ifndef R_MODULE_HPP
#define R_MODULE_HPP

#include "rEngine.hpp"
#include "ui/ruiOverlayManager.hpp"

class rModule {
public:

	virtual void Update(rEngine& engine) = 0;
	virtual void Draw(rEngine& engine) =0;
	virtual void Init(rEngine& engine) = 0;
	virtual void InitUI(ruiOverlayManager& manager, rEngine& engine) = 0;
	virtual void Uninit(rEngine& engine) = 0;

};


#endif