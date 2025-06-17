# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Tic_Tac_Toe_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Tic_Tac_Toe_autogen.dir\\ParseCache.txt"
  "Tic_Tac_Toe_autogen"
  )
endif()
