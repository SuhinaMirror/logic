cmake_minimum_required(VERSION 2.8)
project(mirrorbackend)

include_directories(src/hiberlite)
add_definitions(-std=c++11)
add_executable(mirrorbackend

src/hiberlite/BeanLoader.cpp 
src/hiberlite/BeanUpdater.cpp 
src/hiberlite/ChildKiller.cpp
src/hiberlite/CppModel.cpp
src/hiberlite/Database.cpp
src/hiberlite/ModelExtractor.cpp
src/hiberlite/Registry.cpp
src/hiberlite/shared_res.cpp
src/hiberlite/SQLiteStmt.cpp
src/hiberlite/Visitor.cpp 
src/main.cpp
)

target_link_libraries(mirrorbackend
    pthread
    ssl
    crypto
    sqlite3
    boost_system
    boost_regex
)
