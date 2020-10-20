include(AMXConfig)
include(AddSAMPPlugin)

set(SAMP_SDK_ROOT "${PROJECT_SOURCE_DIR}/lib/samp-plugin-sdk")
find_package(SAMPSDK REQUIRED)

include_directories(
	${SAMPSDK_INCLUDE_DIR}
)

add_samp_plugin(fsutil 
	${SAMPSDK_DIR}/amx/getch.c
	${SAMPSDK_DIR}/amxplugin.cpp
	${SAMPSDK_DIR}/amxplugin2.cpp
	EFileType.hpp
	common.hpp
	main.cpp
	natives.cpp
	natives.hpp
	plugin.def
)
target_link_libraries(fsutil)
