cmake_minimum_required(VERSION 3.5)

project(scmf C)

if(build_type)
    if((${build_type} STREQUAL "imx6") OR (${build_type} STREQUAL "imx8"))
        message(STATUS "build type is '${build_type}'")
    else()
        message(FATAL_ERROR "wrong build type, only support 'imx6' and 'imx8'")
        return()
    endif()
endif()

include_directories(./log/if)

add_subdirectory(log)
aux_source_directory(. SRC_FILES)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} log)

if((${build_type} STREQUAL "imx8"))
    target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/xdja/${build_type}/libxdjakey.so)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/xdja/${build_type}/libssf.so)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/xdja/${build_type}/libscmf.so)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/xdja/${build_type}/libcurl.so)
elseif((${build_type} STREQUAL "imx6"))
    target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/xdja/${build_type}/libxdjakey.so)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/xdja/${build_type}/libssf.so)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/xdja/${build_type}/libssl.so)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/xdja/${build_type}/libscmf.so)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/xdja/${build_type}/libcurl.so)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/xdja/${build_type}/libcrypto.so)
else()
    message(FATAL_ERROR "wrong build type, only support 'imx6' and 'imx8'")
    return()
endif()

target_link_libraries(${PROJECT_NAME} glib-2.0.so)


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/include)



