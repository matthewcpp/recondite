#include "ImageImporter.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "3rdParty/stb_image.h"

namespace recondite { namespace import {
	int ImageImporter::ImportImage(const rString& path, rTextureData& data) {
		data.Clear();

		int width, height, bpp;

		unsigned char *imageData = stbi_load(path.c_str(), &width, &height, &bpp, 0);

		if (imageData) {
			data.SetImageData(width, height, bpp, imageData);

			stbi_image_free(imageData);

			return 0;
		}
		else {
			return 1;
		}
	}
}}