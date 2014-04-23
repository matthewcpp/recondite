set(input_files)

add_rec_src(input_files "rController" "input")
add_rec_src(input_files "rDPad" "input")
add_rec_src(input_files "rDragGesture" "input")
add_rec_src(input_files "rGestureTracker" "input")
add_rec_src(input_files "rInputButton" "input")
add_rec_src(input_files "rKeyboard" "input")
add_rec_src(input_files "rMouse" "input")
add_rec_src(input_files "rPinchGesture" "input")
add_rec_src(input_files "rTouch" "input")

set(recondite_files ${recondite_files} ${input_files} PARENT_SCOPE)
set(input_sources ${input_files} PARENT_SCOPE)
