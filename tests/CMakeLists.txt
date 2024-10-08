##
#  CMakeLists.txt
#
#  Copyright (C) 2016-2018 srcML, LLC. (www.srcML.org)
#
#  This file is part of the srcSAXEventDispatch.
#
#  The srcSAXEventDispatch is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  The srcSAXEventDispatch is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with the srcSAXEventDispatch; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

file( GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Test* )
include_directories(${DISPATCH_INCLUDE_DIR})
message(${SOURCES})

add_definitions("-std=c++11")

find_package(LibXml2 REQUIRED)

foreach( testsourcefile ${SOURCES} )
    string( REPLACE ".cpp" "" testname ${testsourcefile} )
    get_filename_component(file ${testsourcefile} NAME_WE)
    add_executable( ${file} EXCLUDE_FROM_ALL ${testsourcefile} )
    target_link_libraries( ${file} srcsaxeventdispatch srcsax_static srcml ${DISPATCH_LIBRARIES} LibXml2::LibXml2)
endforeach( testsourcefile ${SOURCES} )
