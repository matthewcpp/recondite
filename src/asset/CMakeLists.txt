set(asset_files)

add_rec_src(asset_files "rTexture" "asset")
add_rec_src(asset_files "rTextureManager" "asset")
add_rec_src(asset_files "rTextureData" "asset")

add_rec_src(asset_files "rTextureAtlasData" "asset")

add_rec_src(asset_files "rShader" "asset")
add_rec_src(asset_files "rShaderManager" "asset")

add_rec_src(asset_files "rGeometry" "asset")
add_rec_src(asset_files "rGeometryData" "asset")
add_rec_src(asset_files "rTexCoordGeometryData" "asset")
add_rec_src(asset_files "rPrimitiveGeometryData" "asset")

add_rec_src(asset_files "rMaterial" "asset")

add_rec_src(asset_files "rModel" "asset")
add_rec_src(asset_files "rModelManager" "asset")
add_rec_src(asset_files "rModelData" "asset")


add_rec_src(asset_files "rFont" "asset")
add_rec_src(asset_files "rFontManager" "asset")

add_rec_src(asset_files "rSkeleton")

list(APPEND asset_files ${CMAKE_CURRENT_SOURCE_DIR}/../../include/asset/rAssetManager.hpp)

set(recondite_files ${recondite_files} ${asset_files} PARENT_SCOPE)
set(asset_sources ${asset_files} PARENT_SCOPE)