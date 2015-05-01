################################################################################
#
#  Project F-Bridge                 [project home-page]
#
#  File:
#        [/RBP/src/CMakeLists.txt]
#
#  Copyright notice:
#        Copyright (C) 2014, 2015 Project F-Bridge Group, CEIT Department,
#                       Amirkabir University of Technology (Tehran Polytechnic)
#
#  Author(s):
#	Parham Alvani (parham.alvani@gmail.com)
#
#  Description:
#	[Probably the most significant part of the header comment. A brief
#	description of file, including the module it belongs to, its relevance
#	to the project and other files or modules and the main tasks
#	it handles.]
#
#  Licence:
#        This file is part of the F-Bridge Project package.
#
#        This file is free code: you can redistribute it and/or modify it under
#        the terms of the GNU Lesser General Public License version 2.1 as
#        published by the Free Software Foundation.
#
#        This package is distributed in the hope that it will be useful, but
#        WITHOUT ANY WARRANTY; without even the implied warranty of
#        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#        Lesser General Public License for more details.
#
#        You should have received a copy of the GNU Lesser General Public
#        License along with the F-Bridge source package.  If not, see
#        http://www.gnu.org/licenses/.
#
#

add_executable (RBP.out main.c trap.c rest.c trex.c)

find_package(PkgConfig)
pkg_check_modules(LIBSOUP REQUIRED libsoup-2.4>=2.48)
include_directories(${LIBSOUP_INCLUDE_DIRS})
link_directories(${LIBSOUP_LIBRARY_DIRS})
target_link_libraries(RBP.out ${LIBSOUP_LIBRARIES})
