project(timer C)

aux_source_directory(. TIMER_SRC_FILES)

add_library(${PROJECT_NAME} STATIC ${TIMER_SRC_FILES})
