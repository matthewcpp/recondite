#ifndef R_DEFS_HPP
#define R_DEFS_HPP

enum rContentError{
	rCONTENT_ERROR_NONE = 0,
	rCONTENT_ERROR_FILE_NOT_FOUND,
	rCONTENT_ERROR_FILE_NOT_READABLE,
        rCONTENT_ERROR_FILE_NOT_WRITABLE,
	
	rCONTENT_ERROR_ASSET_NOT_PRESENT,
	rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT,
	rCONTENT_ERROR_ASSET_IN_USE,
	rCONTENT_ERROR_UNABLE_TO_LOAD_DEPENDENCY,
	
	rCONTENT_ERROR_PARSE_ERROR,
	rCONTENT_ERROR_UNKNOWN_ASSET_TYPE,
	rCONTENT_ERROR_STREAM_ERROR
};

enum rAssetType{
	rASSET_TEXTURE2D = 0,
	rASSET_SHADER,
	rASSET_MATERIAL,
	rASSET_GEOMETRY,
	rASSET_FONT,
	rASSET_MODEL,
	rASSET_SOUND,
	rASSET_NUM_TYPES,
	rASSET_UNKNOWN
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
	VertexColor,
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

#if __cplusplus <= 199711L
	#define rNO_COPY_CLASS(classname)				\
		private:                                    \
			classname(const classname&);            \
			classname& operator=(const classname&);

#else
	#define rNO_COPY_CLASS(classname)							\
		public:													\
			classname(const classname&) = delete;				\
			classname& operator=(const classname&) = delete;
#endif

#endif
