/*
 * КДЗ-1 по дисциплине Алгоритмы и структуры данных
 * Мариносян Никита Арамович, БПИ151, 01.12.2016
 * Среда разработки: CLion
 *
 * Состав проекта:
 * main.cpp - главный файл;
 * huffman.cpp,  huffman.h - реализация алгоритма Хаффмана
 * shannon-fano.cpp, shannon-fano.h - реализация алгоритма Шеннона-Фано
 * utilities.cpp, utilities.h - универсальные функции: архивация, разархивация, подсчет частоты)
 *
 * Сделано:
 * 1. Реализованы алгоритмы кодировок Хаффмана и Шеннона-Фано
 * 2. Реализована архивация и разархивация файлов с помощью данных алгоритмов
 * 3. Произведена оценка количества элементарных операций каждого алгоритма
 * 4. Составлен отчет о проделанной работе (см. Marinosyan_Report.pdf)
 */

#include <cstdlib>
#include "huffman.h"
#include "shannon-fano.h"

/*
 * Method to do the compression
 * using Huffman algorithm
 */
void compress_H(string ipath) {

    // Create output file path
    string opath = ipath.substr(0, ipath.length() - 3) + "haff";

    // Do compression
    huffman_compression(ipath, opath);
}

/*
 * Method to do the decompression
 * using Huffman algorithm
 */
void decompress_H(string ipath) {

    // Create output file path
    string opath = ipath.substr(0, ipath.length() - 5) + "-unz-h.txt";

    // Do decompression
    decompressFile(ipath, opath);
}

/*
 * Method to do the compression
 * using Shannon-Fano algorithm
 */
void compress_SF(string ipath) {

    // Create output file path
    string opath = ipath.substr(0, ipath.length() - 3) + "shan";

    // Do compression
    sf_compression(ipath, opath);
}

/*
 * Method to do the decompression
 * using Shannon-Fano algorithm
 */
void decompress_SF(string ipath) {

    // Create output file path
    string opath = ipath.substr(0, ipath.length() - 5) + "-unz-s.txt";

    // Do decompression
    decompressFile(ipath, opath);
}

int main(int argc, char* argv[]) {

    // Check if the call was
    // made properly
    if (argc != 3) {
        cout << "Incorrect number of arguments!" << endl;
        return 0;
    }

    // Check if the file exists
    std::ifstream file(argv[1]);
    if (!file.good()) {
        // File does not exist
        cout << "File does not exist!" << endl;
        return 0;
    }
    file.close();

    // Call the method
    // selected by user
    if (atoi(argv[2]) == 1) { // Huffman compression

        // Check if the file
        // has proper extension
        string ipath = argv[1];
        if (ipath.substr(ipath.length() - 4, ipath.length() - 1) != ".txt") {
            cout << "Incorrect file extension! It must be .txt" << endl;
            return 0;
        }

        // Do compression
        compress_H(argv[1]);
    }
    else if (atoi(argv[2]) == 2) { // Huffman decompression

        // Check if the file
        // has proper extension
        string ipath = argv[1];
        if (ipath.substr(ipath.length() - 5, ipath.length() - 1) != ".haff") {
            cout << "Incorrect file extension! It must be .haff" << endl;
            return 0;
        }

        // Do decompression
        decompress_H(argv[1]);
    }
    else if (atoi(argv[2]) == 3) { // Shannon-Fano compression

        // Check if the file
        // has proper extension
        string ipath = argv[1];
        if (ipath.substr(ipath.length() - 4, ipath.length() - 1) != ".txt") {
            cout << "Incorrect file extension! It must be .txt" << endl;
            return 0;
        }

        // Do compression
        compress_SF(argv[1]);
    }
    else if (atoi(argv[2]) == 4) { // Shannon-Fano decompression

        // Check if the file
        // has proper extension
        string ipath = argv[1];
        if (ipath.substr(ipath.length() - 5, ipath.length() - 1) != ".shan") {
            cout << "Incorrect file extension! It must be .shan" << endl;
            return 0;
        }

        // Do decompression
        decompress_SF(argv[1]);
    }
    else { // Invalid flag
        cout << "No method for this flag found. Flag value must in range [1,4]." << endl;
        return 0;
    }
    cout << "operations: "<< operations;
    return 0;
}