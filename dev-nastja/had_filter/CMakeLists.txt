cmake_minimum_required(VERSION 3.15)

project(smooth_filter)

set(CMAKE_CXX_STANDARD 11)

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)
set(BIN_DIR ${ROOT_DIR}/bin)
set(INC_DIR ${ROOT_DIR}/include)
set(LIB_DIR ${ROOT_DIR}/lib)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})

target_link_directories(${PROJECT_NAME} PUBLIC ${LIB_DIR})
			
target_link_libraries(${PROJECT_NAME} PUBLIC vshell)

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${BIN_DIR})

set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_custom_command (
	TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${BIN_DIR}
)
