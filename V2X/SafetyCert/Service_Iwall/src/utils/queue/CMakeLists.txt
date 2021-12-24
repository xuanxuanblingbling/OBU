project(queue C)

aux_source_directory(. Q_SRC_FILES)

add_library(${PROJECT_NAME} STATIC ${Q_SRC_FILES})
