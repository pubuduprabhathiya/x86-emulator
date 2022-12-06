cmake_minimum_required(VERSION 3.22)
project(x86-emulator VERSION 0.0.1 DESCRIPTION "decoder" LANGUAGES C)

file(GLOB SOURCES "./*" "**/*")

add_executable(main  ${SOURCES})