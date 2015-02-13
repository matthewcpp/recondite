set(xml_files)

add_rec_src(xml_files "rXMLAttributeList" "xml")
add_rec_src(xml_files "rXMLDocument" "xml")
add_rec_src(xml_files "rXMLDocumentLoader" "xml")
add_rec_src(xml_files "rXMLElement" "xml")
add_rec_src(xml_files "rXMLReader" "xml")
add_rec_src(xml_files "rXMLSerialization" "xml")
add_rec_src(xml_files "rXMLUtil" "xml")
add_rec_src(xml_files "rXMLWriter" "xml")

set(recondite_files ${recondite_files} ${xml_files} PARENT_SCOPE)
set(xml_sources ${xml_files} PARENT_SCOPE)
