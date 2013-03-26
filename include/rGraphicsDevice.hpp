#ifndef R_GRAPHICSDEVICE_HPP
#define R_GRAPHICSDEVICE_HPP

#include <cmath>
#include <vector>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rVector2.hpp"
#include "rRectangle2.hpp"
#include "rCircle2.hpp"
#include "rTriangle2.hpp"

#include "rMaterial.hpp"

#include "rVector3.hpp"
#include "rCone3.hpp"
#include "rAlignedBox3.hpp"
#include "rSphere3.hpp"
#include "rMatrix4.hpp"

class rViewport;

typedef rVector2Array rVertex2Array;
typedef rVector3Array  rVertex3Array;
typedef std::vector<unsigned short> rIndexArray;

#define rqtCIRCLE_SEGMENTS  30

#define rqtSPHERE_STACKS 12
#define rqtSPHERE_SEGMENTS 12

#define rqtCONE_SEGMENTS 30

class rGraphicsDevice{
public:
	rGraphicsDevice();
	virtual ~rGraphicsDevice();

	virtual bool Init() = 0;
	virtual bool IsInit() const = 0;
        virtual bool HasCalledInit() const = 0;
	virtual void Uninit()  = 0;
	virtual void Clear()  = 0;
	
	virtual unsigned int GenerateTextureID() = 0;
	virtual unsigned int CreateTexture(int width, int height, int bpp , const unsigned char* data) = 0;
	virtual void UnregisterTexture(int textureID) = 0;
	virtual void BindTexture2D(unsigned int textureID) = 0;
	
	virtual void SetActiveViewport(rViewport& viewport) = 0;
	virtual int Unproject(const rVector3& v, rVector3& world) = 0;

	virtual void DrawLines3(const rVertex3Array& lines , const rColor& color) = 0;
	virtual void DrawPoints3(const rVertex3Array& points , const rColor& color) = 0;

	virtual void DrawWireBox(const rAlignedBox3& b, const rColor& color) = 0;
	
	virtual void DrawMesh(rVertex3Array& verticies, rVector2Array& texCoords, rIndexArray& indicies, rMaterial* material) = 0;
	
	virtual unsigned int CreateShaderProgram(const rString& vertex, const rString& fragment) = 0;
	virtual void DeleteShaderProgram(unsigned int shaderId) = 0;
	
        rString GetLastErrorMessage() const;
        
protected:
	void InitRectangle();
	void InitBox();
	
	void SetBoxDrawPoints(const rAlignedBox3& b);


protected:

	rVertex2Array rectanglePoints;
	rIndexArray wireRectangleIndicies;
	rIndexArray shadedRectangleIndicies;

	rVertex3Array boxPoints;
	rIndexArray wireBoxIndicies;
        rString m_lastError;
};

#endif