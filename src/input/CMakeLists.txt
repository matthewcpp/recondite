set(input_files)

add_rec_src(xml_files "rController" "input")
add_rec_src(xml_files "rDPad" "input")
add_rec_src(xml_files "rDragGesture" "input")
add_rec_src(xml_files "rGestureTracker" "input")
add_rec_src(xml_files "rInputButton" "input")
add_rec_src(xml_files "rKeyboard" "input")
add_rec_src(xml_files "rMouse" "input")
add_rec_src(xml_files "rPinchGesture" "input")
add_rec_src(xml_files "rTouch" "input")

set(recondite_files ${recondite_files} ${xml_files} PARENT_SCOPE)
set(xml_sources ${xml_files} PARENT_SCOPE)
