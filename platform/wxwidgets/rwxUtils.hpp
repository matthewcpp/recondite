#ifndef RWX_UTILS_HPP
#define RWX_UTILS_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "wx/wx.h"

namespace rwxUtils {
	void FormatWxImageDataForOpenGL(wxImage& texture, rUnsigedByteArray& data);
	void MirrorWxImageInPlace(wxImage& texture);
	void AdjustWxImageForOpenGL(wxImage& texture);
}

#endif