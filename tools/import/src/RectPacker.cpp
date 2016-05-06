#include "RectPacker.hpp"

#include "rMathUtil.hpp"

namespace recondite { namespace import {
	RectPacker::RectPacker(){
		_maxSize.Set(1024, 1024);
		_sizeHint.Set(64, 64);
		_resultSize.Set(-1, -1);
	}

	void RectPacker::SetMaxSize(const rSize& maxSize){
		_maxSize = maxSize;
	}

	rSize RectPacker::GetMaxSize() const{
		return _maxSize;
	}

	bool RectPacker::AddItem(Item* item){
		if (item->sourceSize.x <= _maxSize.x && item->sourceSize.y <= _maxSize.y){
			_itemList.push_back(item);

			_sizeHint.x = std::max(int(rMath::NextHighestPowerOf2(item->sourceSize.x)), _sizeHint.x);
			_sizeHint.y = std::max(int(rMath::NextHighestPowerOf2(item->sourceSize.y)), _sizeHint.y);

			return true;
		}
		else{
			return false;
		}
	}

	size_t RectPacker::GetItemCount() const{
		return _itemList.size();
	}

	bool RectPacker::Pack(){
		std::vector<Item*> itemsToPack = _itemList;
		std::sort(itemsToPack.begin(), itemsToPack.end(), [](Item* item1, Item* item2) -> bool {
			return item1->sourceSize.y < item2->sourceSize.y;
		});


		rSize currentSize = _sizeHint;

		while (!PackInSize(itemsToPack, currentSize)){
			//if the items didnt fit, then try to grow the texture to make more room

			if (currentSize.y < currentSize.x){
				currentSize.y = rMath::NextHighestPowerOf2(currentSize.y + 1);
				if (currentSize.y > _maxSize.y){
					_resultSize.Set(-1, -1);
					return false;
				}
			}
			else{
				currentSize.x = rMath::NextHighestPowerOf2(currentSize.x + 1);
				if (currentSize.y > _maxSize.y){
					_resultSize.Set(-1, -1);
					return false;
				}
			}
		}

		_resultSize = currentSize;
		return true;
	}

	bool RectPacker::PackInSize(const ItemVector& itemsToPack, const rSize& currentSize){
		rPoint currentPoint(0, 0);
		int rowHeight = 0;

		for (size_t i = 0; i < itemsToPack.size(); i++){
			Item* item = itemsToPack[i];

			//move to a new line if the item does not fit
			if (currentPoint.x + item->sourceSize.x >= currentSize.x){
				currentPoint.y += rowHeight;
				currentPoint.x = 0;

				rowHeight = 0;
			}

			//make sure the item fits vertically
			if (currentPoint.y + item->sourceSize.y >= currentSize.y) return false;

			item->packedLocation = currentPoint;
			if (rowHeight == 0) rowHeight = item->sourceSize.y;

			currentPoint.x += item->sourceSize.x;

		}

		return true;
	}

	rSize RectPacker::GetResultSize() const{
		return _resultSize;
	}

	void RectPacker::CalculatePackedUVForItem(Item* item, rVector2& uvOrigin, rVector2& uvSize){
		uvOrigin.Set((float)item->packedLocation.x / _resultSize.x, 1.0 - ((float)item->packedLocation.y / _resultSize.y));
		uvSize.Set((float)item->sourceSize.x / _resultSize.x, (float)item->sourceSize.y / _resultSize.y);
	}
}}