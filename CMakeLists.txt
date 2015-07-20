# project

cmake_minimum_required (VERSION 2.8)

# -- Set project name
set(PROJ_NAME msrv)

project (${PROJ_NAME})

# -- Set install dirs
if (DEFINED ENV{INSTALL_BASE_DIR})
  set(PROJ_INSTALL_DIR $ENV{INSTALL_BASE_DIR})
else()
  set(PROJ_INSTALL_DIR ${CMAKE_SOURCE_DIR}/install)
endif()

set(CPACK_PACKAGE_VERSION "0.1.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_CONTACT )

set(PROJ_LICENSE_FILE COPYING)
set(PROJ_README_FILE  README.txt)

# -- Include the tests in the bin folder?
set(INCLUDE_TEST_IN_BIN FALSE)

# -- Include the magic ProjTools
include("cmake/ProjTools.cmake")
#######################################
# TARGETS                             #
#######################################

# -- Add the library target
set(PUB_HDR
    msrv_sym.h
    msrv.h;
    msrv_alloc.h)

set(INT_HDR
    msrv_internal.h)

set(LIB_SRC 
    msrv_alloc.c
    msrv.c)

# Lib version
set(MSRV_VERSION_MAJOR 0.1)
set(MSRV_VERSION_MINOR 1)
set(MSRV_VERSION ${MSRV_VERSION_MAJOR}.${MSRV_VERSION_MINOR})

# -- Add the msrv library
add_lib(msrv SHARED ${PUB_HDR} ${INT_HDR} ${LIB_SRC})
add_lib_build_def(msrv MSRV_BUILD)
add_lib_build_def(msrv "MSRV_LIB_VERSION=\"${MSRV_VERSION}\"")
link_libs(msrv )
set_tgt_ver(msrv ${MSRV_VERSION} ${MSRV_VERSION_MAJOR})


add_hdrs_tgt_ide(public ${PUB_HDR})
add_hdrs_tgt_ide(internal ${INT_HDR})
add_hdrs_tgt_ide(all ${PUB_HDR} ${INT_HDR})

# -- Install targets
install_hdr(${PUB_HDR})
install_tgt(msrv)
# install(FILES README.md DESTINATION .)

#######################################
# -- Add the subdirectories
set(PROJ_SUBDIRS  unittest; doc; tools; test)

# add all subdirs
foreach(subdir ${PROJ_SUBDIRS})
  add_subdirectory(${subdir})
endforeach(subdir)

