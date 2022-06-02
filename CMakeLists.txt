cmake_minimum_required(VERSION 2.8)                            
PROJECT(screen_capture)                                         

FIND_PACKAGE( OpenCV REQUIRED )

INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(screen_capture "main.cpp" "videoWriter.cpp" "hwndToMat.cpp")                         
TARGET_LINK_LIBRARIES (screen_capture ${OpenCV_LIBS})    




