include_directories(${PROJECT_SOURCE_DIR}/include)
set(executable "run")
add_compile_options(-Wall -Wextra -Wconversion -pedantic -Wfatal-errors)
add_executable(${executable} main.cpp day1.cpp file.cpp)
