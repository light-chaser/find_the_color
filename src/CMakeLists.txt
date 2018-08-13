include_directories(../include)

add_library(direction detection.cpp )
target_link_libraries(direction ${OpenCV_LIBS})


add_library(client SocketMatTransmissionClient.cpp)
add_library(server SocketMatTransmissionServer.cpp)

add_executable(tclient fish_server.cpp)
target_link_libraries(tclient direction)
target_link_libraries(tclient client)
target_link_libraries(tclient ${OpenCV_LIBS})


add_executable(tserver upper_computer.cpp)
target_link_libraries(tserver ${OpenCV_LIBS})
target_link_libraries(tserver server)
