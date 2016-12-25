#include "rRenderingOptions.hpp"

class RECONDITE_API rPickingColorManager {
public:
	rPickingColorManager() : r(0), g(0), b(0), a(UINT8_MAX) {}

	bool GetNextColor(rColor& color);
	void ReturnColor(const rColor& color);

private:
	typedef std::queue<rColor> PickingColorQueue;

private:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	PickingColorQueue m_availableColors;
};

bool rPickingColorManager::GetNextColor(rColor& color){
	if (m_availableColors.size() > 0){
		color = m_availableColors.front();
		m_availableColors.pop();
		return true;
	}

	rColor nextColor(r, g, b, a);

	if (r < UINT8_MAX)
		r++;
	else if (g < UINT8_MAX)
		g++;
	else if (b < UINT8_MAX)
		b++;
	else
		return false;

	color = nextColor;
	return true;
}

rPickingColorManager s_pickingColorManager;

void rPickingColorManager::ReturnColor(const rColor& color){
	m_availableColors.push(color);
}
