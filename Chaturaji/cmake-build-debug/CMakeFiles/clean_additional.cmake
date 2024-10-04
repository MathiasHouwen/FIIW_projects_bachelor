# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Chaturaji_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Chaturaji_autogen.dir\\ParseCache.txt"
  "Chaturaji_autogen"
  )
endif()
