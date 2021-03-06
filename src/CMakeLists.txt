#Build the core Favor library

find_package(Threads REQUIRED)

set(compilation_files favor.cpp processor.cpp reader.cpp worker.cpp accountmanager.cpp message.cpp contact.cpp logger.cpp) #Core files
LIST(APPEND compilation_files ${favor_SOURCE_DIR}/src/lib/sqlite/sqlite3.c) #Sqlite
add_definitions(-DSQLITE_THREADSAFE=2)
LIST(APPEND compilation_files ${favor_SOURCE_DIR}/src/lib/pugixml/pugixml.cpp)

set(compilation_libraries ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS}) #-pthread and #-ldl

OPTION(FAVOR_DEBUG "Favor's debug and test settings" ON)
IF(FAVOR_DEBUG)
  add_definitions(-DDEBUG)
  set(CMAKE_BUILD_TYPE Debug)
ENDIF()

SET(CMAKE_CXX_FLAGS "-std=c++11")


# Include Email
OPTION(FAVOR_EMAIL_MANAGER "Include the MessageManager for Email" ON)
IF(FAVOR_EMAIL_MANAGER)
  LIST(APPEND compilation_files ${favor_SOURCE_DIR}/src/managers/emailmanager.cpp)
  add_definitions(-DFAVOR_EMAIL_MANAGER)
  
  #VMIME
  LIST(APPEND compilation_libraries ${favor_SOURCE_DIR}/src/lib/vmime/lib/libvmime.a)
  #OpenSSL, which must come after Vmime:
  #A library containing the definition of a function should appear
  #after any source files or object files which use it.
  find_package(OpenSSL REQUIRED)
  include_directories(${OPENSSL_INCLUDE_DIR})
  LIST(APPEND compilation_libraries ${OPENSSL_LIBRARIES})

  
  #TIDY
  list(APPEND compilation_libraries ${favor_SOURCE_DIR}/src/lib/tidy-html5/libtidys.a)
ENDIF()

# Include Line
OPTION(FAVOR_LINE_MANAGER "Include the MessageManager for Line messaging client" ON)
IF(FAVOR_LINE_MANAGER)
  add_definitions(-DFAVOR_LINE_MANAGER)
  LIST(APPEND compilation_files ${favor_SOURCE_DIR}/src/managers/linemanager.cpp)
ENDIF()

#Include Skype
OPTION(FAVOR_SKYPE_MANAGER "Include the MessageManager for Skype" ON)
IF(FAVOR_SKYPE_MANAGER)
  add_definitions(-DFAVOR_SKYPE_MANAGER)
  LIST(APPEND compilation_files ${favor_SOURCE_DIR}/src/managers/skypemanager.cpp)
ENDIF()


add_library(favor SHARED ${compilation_files})
target_compile_options(favor PUBLIC -std=c++11)

add_library(favor_test SHARED ${compilation_files})
target_compile_options(favor_test PUBLIC -std=c++11 -O0 -g)
target_compile_definitions(favor_test PUBLIC TESTING)

set(incl_dirs lib/vmime/include lib/gtest/include managers lib .) #Last . is so managers can get at core files

IF(TARGET favor_test) #TODO: It seems like this being run regardless, but there's no harm in building it in normal builds
  ADD_SUBDIRECTORY(lib/gtest)
ENDIF()

target_include_directories(favor PUBLIC ${incl_dirs})
target_include_directories(favor_test PUBLIC ${incl_dirs} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(favor ${compilation_libraries})
target_link_libraries(favor_test ${compilation_libraries})