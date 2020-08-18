find_package( OpenCV REQUIRED )
add_executable(bin_main main.cpp)
target_link_libraries( bin_main ${OpenCV_LIBS} )