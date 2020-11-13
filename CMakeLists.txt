cmake_minimum_required(VERSION 3.15)
project(Nurtdinov_KDZ_compressor)

set(CMAKE_CXX_STANDARD 14)

add_executable(compressor src/main.cpp src/ShannonFano.cpp src/ShannonFano.h src/Converter.cpp src/Converter.h src/ShannonPacker.cpp src/ShannonPacker.h src/ShannonUnpacker.cpp src/ShannonUnpacker.h src/Lz77Packer.cpp src/Lz77Packer.h src/Lz77Unpacker.cpp src/Lz77Unpacker.h src/LzwPacker.cpp src/LzwPacker.h src/LzwUnpacker.cpp src/LzwUnpacker.h)