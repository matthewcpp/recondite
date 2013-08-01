SRC_FILES = 	../src/math/rMath.cpp \
		../src/math/rMathUtil.cpp \
		../src/math/rMatrix3.cpp \
		../src/math/rMatrix4.cpp \
		../src/math/rMatrixUtil.cpp \
		../src/math/rQuaternion.cpp \
		../src/math/rVector2.cpp \
		../src/math/rVector3.cpp \
		../src/math/rVector4.cpp \
		../src/geometry/rAlignedBox3.cpp \
		../src/geometry/rCircle2.cpp \
		../src/geometry/rCone3.cpp \
		../src/geometry/rFrustrum.cpp \
		../src/geometry/rGeometry3.cpp \
		../src/geometry/rIntersection2.cpp \
		../src/geometry/rIntersection3.cpp \
		../src/geometry/rLine2.cpp \
		../src/geometry/rLine3.cpp \
		../src/geometry/rPlane3.cpp \
		../src/geometry/rRectangle2.cpp \
		../src/geometry/rSphere3.cpp \
		../src/geometry/rTriangle2.cpp \
		../src/core/rActor3.cpp \
		../src/core/rCamera.cpp \
		../src/core/rColor.cpp \
		../src/core/rGameTime.cpp \
		../src/core/rPoint.cpp \
		../src/core/rRect.cpp \
		../src/core/rSize.cpp \
		../src/core/rViewport.cpp \
		../src/core/rContentManager.cpp \
		../src/core/rLog.cpp \
		../src/asset/rAsset.cpp \
		../src/asset/rMaterial.cpp \
		../src/asset/rTexture2D.cpp \
		../src/asset/rShader.cpp \
		../src/asset/rGeometry.cpp \
		../src/xml/rXMLDocument.cpp\
		../src/xml/rXMLDocumentLoader.cpp\
		../src/xml/rXMLWriter.cpp\
		../src/xml/rXMLReader.cpp\
		../src/xml/rXMLElement.cpp\
		../src/xml/rXMLAttributeList.cpp\
		../src/data/rTexture2DData.cpp \
		../src/data/rMaterialData.cpp \
		../src/data/rShaderData.cpp \
		../src/data/rAssetManifestData.cpp \
		../src/data/rGeometryData.cpp 

VPATH = ../src/math ../src/geometry ../src/core ../src/asset ../src/data ../src/xml

LIB_DIR = ../lib
DYNAMIC_LIB = librecondite

OUT = $(LIB_DIR)/$(DYNAMIC_LIB).so
BUILD_DIR = ../build/
COMPILER = gcc
INCLUDES = -I../include
CPPFLAGS = -Wall -g -fPIC
LDFLAGS =
OBJECTS = $(addprefix $(BUILD_DIR),$(notdir $(SRC_FILES:.cpp=.o)))

all:recondite

recondite: $(OBJECTS)
	gcc -shared -Wl,-soname,$(DYNAMIC_LIB) -o $(OUT) $(OBJECTS)
	

-include $(OBJECTS:.o=.d)

$(BUILD_DIR)%.o: %.cpp
	$(COMPILER) $(INCLUDES) $(CPPFLAGS) -c $< -o $@
	@$(COMPILER) -MM $(INCLUDES) $(CPPFLAGS) $< > $*.d
	@sed -i -e 's|.*:|$(BUILD_DIR)$*.o:|' $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d

clean:
	rm -f *.o
	rm -f *.d
	rm $(OUT)
