cmake_minimum_required(VERSION 2.6)
project(AacEncode)


#Linux环境C++11编译
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/project/sdk/faac/include)

#引用动态库
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/project/sdk/faac/lib)

SET(CMAKE_CXX_FLAGS         "-g3 -Wall -lfaac -Wl,-rpath,lib -std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG   "-g3 -Wall -lfaac -Wl,-rpath,lib -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "-o2 -Wall -lfaac -Wl,-rpath,lib -DNDEBUG -std=c++11")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


aux_source_directory(project/src/Startup/ FILE)
aux_source_directory(project/src/Public/ FILE)
aux_source_directory(project/src/Codec/ FILE)
aux_source_directory(project/src/Codec/AAC FILE)


ADD_EXECUTABLE(AacEncode ${FILE})

#引用静态库
#TARGET_LINK_LIBRARIES(AccEncode
#        ${PROJECT_SOURCE_DIR}/sdk/faac/lib/libfaac.a)