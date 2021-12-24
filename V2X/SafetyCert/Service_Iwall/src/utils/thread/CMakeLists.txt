project(thread C)

aux_source_directory(. T_SRC_FILES)

link_libraries(pthread)

add_library(${PROJECT_NAME} STATIC ${T_SRC_FILES})
