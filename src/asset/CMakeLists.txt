set(asset_files)

add_rec_src(asset_files "rAsset")
add_rec_src(asset_files "rFont")
add_rec_src(asset_files "rFontGlyph")
add_rec_src(asset_files "rGeometry")
add_rec_src(asset_files "rMaterial")
add_rec_src(asset_files "rModel")
add_rec_src(asset_files "rShader")
add_rec_src(asset_files "rSkeleton")
add_rec_src(asset_files "rTexture2D")

set(recondite_files ${recondite_files} ${asset_files} PARENT_SCOPE)
set(asset_sources ${asset_files} PARENT_SCOPE)