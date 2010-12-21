#Config file
include(../config.cmake)

set(LINUX_CONFIG_FILE ConfigLinux)
configure_file(${LINUX_CONFIG_FILE} ${LINUX_CONFIG_FILE})
