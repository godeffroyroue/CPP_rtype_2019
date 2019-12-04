cmake_minimum_required(VERSION 3.14.4)

macro(SUBDIRLIST result curdir)  
  file(GLOB children ${curdir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY  ${child})
        list(APPEND dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

SUBDIRLIST(SUBDIRS ./Entities)

foreach(subdir ${SUBDIRS})
    ADD_SUBDIRECTORY(${subdir})
endforeach()
