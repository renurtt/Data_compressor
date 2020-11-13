// КДЗ по дисциплине Алгоритмы и структуры данных, 2019-2020 уч.год
// Нуртдинов Ренат Айратович, группа БПИ-184, 03.04.2020
// Среда разработки: CLion
// Состав проекта:
//        Converter.cpp
//        Converter.h
//        Lz77Packer.cpp
//        Lz77Packer.h
//        Lz77Unpacker.cpp
//        Lz77Unpacker.h
//        ShannonFano.cpp
//        ShannonFano.h
//        ShannonPacker.cpp
//        ShannonPacker.h
//        ShannonUnpacker.cpp
//        ShannonUnpacker.h
// Что сделано:
//        сжатие и распаковка методом Шеннона - Фано
//        сжатие и распаковка методом LZ77
//        проведен вычислительный эксперимент
//        для измерения времени выполнения использовалась библиотека std::chrono, steady_clock
//        построены таблицы и графики
//        оформлен отчет
//        сжатие и распаковка методом LZW
// Что не сделано:
//        -

#include "Converter.h"
#include "ShannonPacker.h"
#include "ShannonUnpacker.h"
#include "Lz77Packer.h"
#include "Lz77Unpacker.h"
#include "LzwPacker.h"
#include "LzwUnpacker.h"


int main()
{
    string name_with_ext = "simple.txt";
    string original_filename = "DATA/" + name_with_ext;

    string compressed_filename;

    compressed_filename = Lz77Packer::pack(original_filename, 5);
    Lz77Unpacker::unpack(compressed_filename);

    return 0;
}