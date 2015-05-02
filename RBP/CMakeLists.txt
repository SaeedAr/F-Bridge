################################################################################
#
#  Project F-Bridge                 [project home-page]
#
#  File:
#        /RBP/CMakeLists.txt
#
#  Copyright notice:
#        Copyright (C) 2014, 2015 Project F-Bridge Group, CEIT Department,
#                       Amirkabir University of Technology (Tehran Polytechnic)
#
#  Author(s):
#	Parham Alvani (parham.alvani@gmail.com)
#
#  Description:
#	Cmake configuration file
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
cmake_minimum_required (VERSION 2.6)
project (RBP)

# Set porject imformation
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

subdirs (src)

# The version number
set (RBP_MAJOR_VERSION 1)
set (RBP_MINOR_VERSION 1)

# Add personal c flags
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0 -g -std=gnu11 ")
