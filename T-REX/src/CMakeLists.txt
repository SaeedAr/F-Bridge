# In The Name Of God
# ========================================
# [] File Name : Makefile
#
# [] Creation Date : 08-04-2015
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
add_executable (T-REX.out main.c proxy.c)

find_package(PkgConfig)
pkg_check_modules(LIBSOUP REQUIRED libsoup-2.4>=2.48)
include_directories(${LIBSOUP_INCLUDE_DIRS})
link_directories(${LIBSOUP_LIBRARY_DIRS})
target_link_libraries(T-REX.out ${LIBSOUP_LIBRARIES})
