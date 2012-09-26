#include "rwxUtils.hpp"

void rwxUtils::AdjustWxImageForOpenGL(wxImage& texture){
}

void rwxUtils::MirrorWxImageInPlace(wxImage& texture){
	unsigned char *data, *pTop, *pBottom;
	
	wxSize size = texture.GetSize();
	int top = 0;
	int bottom = size.y - 1;
	int middle = top / 2;
	int rowSize = size.x * 3;
	unsigned char* temp = new unsigned char[rowSize];
	
	data = texture.GetData();
	
	while (top != middle){
		pTop = data + (rowSize * top);
		pBottom = data + (rowSize * bottom);
		
		memcpy(temp, pTop , rowSize);
		memcpy(pTop, pBottom , rowSize);
		memcpy(pBottom, temp , rowSize);
		
		top++;
		bottom--;
	}
	
	data = texture.GetAlpha();
	if (data){
		top = 0;
		bottom = (size.x * size.y) - 1;
		
		while (top != middle){
			temp[0] = data[top];
			data[top] = data[bottom];
			data[bottom] = temp[0];
			
			top++;
			bottom--;
		}
	}
	
	delete temp;
}

void rwxUtils::FormatWxImageDataForOpenGL(wxImage& texture, rUnsigedByteArray& data){
	int index;
	wxSize size = texture.GetSize();
	int pixels = size.x * size.y;
	
	data.resize(pixels * 4);
	unsigned char* rgb = texture.GetData();
	unsigned char* alpha = texture.GetAlpha();
	
	for (int i =0; i < pixels; i++){
		index = i * 4;
		memcpy(&data[index], &rgb[index], 3);
		data[index + 3] = alpha[index + 3];
	}
}