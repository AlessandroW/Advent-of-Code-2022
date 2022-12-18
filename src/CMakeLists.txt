include_directories(${PROJECT_SOURCE_DIR}/include)
set(executable "run")
add_compile_options(-Wall -Wextra -Wconversion -pedantic -Wfatal-errors)
add_executable(${executable} main.cpp day1.cpp day2.cpp day3.cpp
  day4.cpp day5.cpp day6.cpp day7.cpp day8.cpp day9.cpp day10.cpp day11.cpp
  day17.cpp day18.cpp
  file.cpp)
