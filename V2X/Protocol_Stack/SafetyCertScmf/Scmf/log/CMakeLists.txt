project(log)

include_directories(./if ./inc)

aux_source_directory(src LOG_SRC_FILES)

link_libraries(pthread)
add_library(${PROJECT_NAME} STATIC ${LOG_SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/if)
