#include "ui/ruiAbsoluteLayout.hpp"

void ruiLayout::Layout(rRect& rect){
	for (size_t i = 0; i < m_layoutItems.size(); i++){
		ruiLayoutItem* layoutItem = m_layoutItems[i];
		rPoint position(0,0);

		rSize itemSize = layoutItem->GetSize();

		
		

		layoutItem->SetPosition(position);
	}
}