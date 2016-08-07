#pragma once

#include <vector>
#include <algorithm>

#include "rBuild.hpp"

#include "rSize.hpp"
#include "rPoint.hpp"
#include "rVector2.hpp"


namespace recondite { namespace import { namespace internal {
	class RectPacker {
	public:
		class Item {
		public:
			rSize sourceSize;
			rPoint packedLocation;
		};

	public:
		RectPacker();

	public:
		bool AddItem(Item* item);
		size_t GetItemCount() const;
		bool Pack();
		rSize GetResultSize() const;

		void CalculatePackedUVForItem(Item* item, rVector2& uvOrigin, rVector2& uvSize);

	public:
		void SetMaxSize(const rSize& maxSize);
		rSize GetMaxSize() const;

	private:
		typedef std::vector<Item*> ItemVector;
		bool PackInSize(const ItemVector& itemsToPack, const rSize& currentSize);

	private:
		ItemVector _itemList;
		rSize _sizeHint;
		rSize _maxSize;
		rSize _resultSize;
	};
}}}