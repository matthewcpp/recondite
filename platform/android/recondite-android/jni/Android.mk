# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := recondite-android

LOCAL_C_INCLUDES += ../../../include
LOCAL_C_INCLUDES += ../../../platform/rgl

LOCAL_SRC_FILES := main.cpp
LOCAL_SRC_FILES += rAndroidContentManager.cpp

LOCAL_SRC_FILES += ../../../../platform/rgl/rOpenGLGraphicsDevice.cpp

LOCAL_SRC_FILES += ../../../../src/math/rMath.cpp
LOCAL_SRC_FILES += ../../../../src/math/rMathUtil.cpp
LOCAL_SRC_FILES += ../../../../src/math/rMatrix3.cpp
LOCAL_SRC_FILES += ../../../../src/math/rMatrix4.cpp
LOCAL_SRC_FILES += ../../../../src/math/rMatrixUtil.cpp
LOCAL_SRC_FILES += ../../../../src/math/rQuaternion.cpp
LOCAL_SRC_FILES += ../../../../src/math/rVector2.cpp
LOCAL_SRC_FILES += ../../../../src/math/rVector3.cpp
LOCAL_SRC_FILES += ../../../../src/math/rVector4.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rAlignedBox3.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rCircle2.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rCone3.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rFrustrum.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rGeometry3.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rIntersection2.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rIntersection3.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rLine2.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rLine3.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rPlane3.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rRectangle2.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rSphere3.cpp
LOCAL_SRC_FILES += ../../../../src/geometry/rTriangle2.cpp
LOCAL_SRC_FILES += ../../../../src/core/rActor3.cpp
LOCAL_SRC_FILES += ../../../../src/core/rCamera.cpp
LOCAL_SRC_FILES += ../../../../src/core/rColor.cpp
LOCAL_SRC_FILES += ../../../../src/core/rGameTime.cpp
LOCAL_SRC_FILES += ../../../../src/core/rPoint.cpp
LOCAL_SRC_FILES += ../../../../src/core/rRect.cpp
LOCAL_SRC_FILES += ../../../../src/core/rSize.cpp
LOCAL_SRC_FILES += ../../../../src/core/rViewport.cpp
LOCAL_SRC_FILES += ../../../../src/core/rContentManager.cpp
LOCAL_SRC_FILES += ../../../../src/asset/rAsset.cpp
LOCAL_SRC_FILES += ../../../../src/asset/rMaterial.cpp
LOCAL_SRC_FILES += ../../../../src/asset/rTexture2D.cpp
LOCAL_SRC_FILES += ../../../../src/asset/rShader.cpp
LOCAL_SRC_FILES += ../../../../src/xml/rXMLDocument.cpp
LOCAL_SRC_FILES += ../../../../src/xml/rXMLDocumentLoader.cpp
LOCAL_SRC_FILES += ../../../../src/xml/rXMLWriter.cpp
LOCAL_SRC_FILES += ../../../../src/xml/rXMLReader.cpp
LOCAL_SRC_FILES += ../../../../src/xml/rXMLElement.cpp
LOCAL_SRC_FILES += ../../../../src/xml/rXMLAttributeList.cpp
LOCAL_SRC_FILES += ../../../../src/data/rTexture2DData.cpp
LOCAL_SRC_FILES += ../../../../src/data/rMaterialData.cpp
LOCAL_SRC_FILES += ../../../../src/data/rShaderData.cpp

LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
