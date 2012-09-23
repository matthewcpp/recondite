#include "rGraphicsDevice.hpp"

rGraphicsDevice::rGraphicsDevice(){
	InitRectangle();
	InitBox();
}

rGraphicsDevice::~rGraphicsDevice(){
}

void rGraphicsDevice::InitBox(){
	boxPoints.resize(8);
	
	unsigned short indicies []= {0,1,1,2,2,3,3,0,1,5,2,6,0,4,3,7,4,5,5,6,6,7,7,4};
	wireBoxIndicies.resize(sizeof(indicies) / 2);

	for (size_t i = 0 ; i < wireBoxIndicies.size(); i++)
		wireBoxIndicies[i] = indicies[i];
		
}

void rGraphicsDevice::InitRectangle(){
	unsigned short shadedRectIndex[] = {0,1,2,3};
	unsigned short wireRectIndex[] = {0,1,3,2};

	shadedRectangleIndicies.insert(shadedRectangleIndicies.end(), shadedRectIndex , &shadedRectIndex[4]);
	wireRectangleIndicies.insert(wireRectangleIndicies.end() , wireRectIndex , &wireRectIndex[4]);

	rectanglePoints.resize(4);
}




void rGraphicsDevice::SetBoxDrawPoints(const rAlignedBox3& b){
	boxPoints[0].Set(b.min.x , b.max.y , b.max.z);
	boxPoints[1] = b.max;
	boxPoints[2].Set(b.max.x , b.min.y , b.max.z);
	boxPoints[3].Set(b.min.x , b.min.y, b.max.z);

	boxPoints[4].Set(b.min.x , b.max.y , b.min.z);
	boxPoints[5].Set(b.max.x , b.max.y , b.min .z);
	boxPoints[6].Set(b.max.x , b.min.y , b.min.z);
	boxPoints[7] = b.min;
}