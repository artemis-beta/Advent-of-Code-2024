file(GLOB AOC24_SOLUTIONS ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

foreach(CXX_FILE ${AOC24_SOLUTIONS})
    get_filename_component(FILENAME ${CXX_FILE} NAME_WE)
    add_executable(${FILENAME} ${CXX_FILE})
    target_link_libraries(${FILENAME} ${PROJECT_NAME})
endforeach()