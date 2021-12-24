project(json C)

aux_source_directory(. JSON_SRC_FILES)

add_library(${PROJECT_NAME} STATIC ${JSON_SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC .)
