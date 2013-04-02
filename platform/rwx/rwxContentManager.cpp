#include "rwxContentManager.hpp"

rwxContentManager::rwxContentManager(rOpenGLGraphicsDevice* graphicsDevice)
:rContentManager(graphicsDevice)
{}

void rwxContentManager::InitDefaultAssets(){
    
    rContentManager::InitDefaultAssets();
	#include "rOpenGLDefaultShaders.inl"
    rShaderData data;
    data.SetShaderData(texturedVertexShader, texturedFragmentShader);
    LoadShader(data, "default_textured");
}

rTexture2D* rwxContentManager::LoadWxImageToGraphicsDevice(wxImage& texture, const wxString& name){
	if (!texture.IsOk()){
		m_error = rCONTENT_ERROR_FILE_NOT_READABLE;
		return NULL;
	}
	
	//need to fix this...make it 1 call...
	texture = texture.Mirror(false);
	rwxUtils::MirrorWxImageInPlace(texture);
	
	wxSize size = texture.GetSize();
	int bpp = texture.HasAlpha() ? 4 : 3;
	
	rTexture2DData textureData;
	
	if (bpp == 4){
		rUnsigedByteArray data;
		rwxUtils::FormatWxImageDataForOpenGL(texture, data);
		textureData.SetImageData(size.x, size.y, bpp, &data[0]);
	}
	else
		textureData.SetImageData(size.x, size.y, bpp, texture.GetData());
	
	rString texName(name.c_str());
	return LoadTexture(textureData, texName);
}

rTexture2D* rwxContentManager::ImportTextureAssetFromFile(const wxString& path , const wxString& name){
	
	if (!wxFileExists(path)){
		m_error = rCONTENT_ERROR_FILE_NOT_FOUND;
		return NULL;
	}
	
	wxImage texture(path);
	if (texture.IsOk())
		wxLogMessage("Load Texture from File.");
	
	rTexture2D* tex = LoadWxImageToGraphicsDevice(texture, name);
	
	return tex;
}