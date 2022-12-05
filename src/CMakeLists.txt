include_directories(${PROJECT_SOURCE_DIR}/include)
set(executable "run")
add_compile_options(-Wall -Wextra -Wconversion -pedantic -Wfatal-errors)
add_executable(${executable} main.cpp day1.cpp day2.cpp day3.cpp
  day4.cpp day5.cpp
  file.cpp)
