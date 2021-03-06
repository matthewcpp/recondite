#ifndef R_DEFS_HPP
#define R_DEFS_HPP

enum class rContentError{
	None = 0,
	Error
};

enum class rAssetType{
	Texture,
	Model,
	Count
};

enum rAssetSource{
	rASSET_SOURCE_FILE,
	rASSET_SOURCE_RESOURCE,
	rASSET_SOURCE_INTERNAL
};

enum rDataType{
	rDATA_TYPE_INT,
	rDATA_TYPE_FLOAT,
	rDATA_TYPE_VEC3,
	rDATA_TYPE_MATRIX4,
	rDATA_TYPE_TEXTURE2D,
	rDATA_TYPE_COLOR,
	rDATA_TYPE_UNKNOWN
};

enum class rGeometryType{
	Triangles,
	Lines,
	LineLoop,
	Points
};

enum class rGeometryProfile : unsigned char{
	TexCoord,
	Primitive
};
enum class rRenderMode : unsigned char{
	Shaded, Wireframe, WireframeOnShaded
};

enum rButtonState {
	rBUTTON_STATE_UP,
	rBUTTON_STATE_DOWN,
	rBUTTON_STATE_NONE
};

enum class rSeekMode{
	Beginning,
	Current,
	End
};

#define rMAX_BONE_WEIGHTS_PER_VERTEX 4

#define rNO_COPY_CLASS(classname)								\
		public:													\
			classname(const classname&) = delete;				\
			classname& operator=(const classname&) = delete;	

#endif
