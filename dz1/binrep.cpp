#include <iostream>
#include <fstream>
#include <iomanip>

void binaryRepresentation(std::string&& format, std::string&& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "File can't be opened.\n";
        return;
    }
    
    file.seekg(0, file.end);
    auto const fsize = file.tellg();
    char* buffer = new char[fsize];
    file.seekg(0, file.beg);
    if (!file.read(buffer, fsize)) {
        std::cerr << "File can't be read.\n";
        return;
    }

    if (format == "hex8") {
        for (size_t i = 0; i < fsize; ++i) {
            std::cout
                << std::setw(2)
                << std::setfill('0')
                << std::hex
                << static_cast<int>(buffer[i]) << " ";
        }
    }
    if (format == "dec8") {
        for (size_t i = 0; i < fsize; ++i) {
            std::cout
                << std::setw(3)
                << std::setfill('0')
                << std::dec
                << static_cast<int>(buffer[i]) << " ";
        }
    }
    if (format == "hex16") {
        for (size_t i = 0; i < fsize-1; i+=2) {
            char16_t t = buffer[i];
            std::cout
                << std::setw(4)
                << std::setfill('0')
                << std::hex
                << static_cast<int>((t << 8) | buffer[i+1])
                << " ";
        }
    }
    if (format == "dec16") {
        for (size_t i = 0; i < fsize-1; i+=2) {
            char16_t t = buffer[i];
            std::cout
                << std::setw(5)
                << std::setfill('0')
                << std::dec
                << static_cast<int>((t << 8) | buffer[i+1])
                << " ";
        }
    }
    if (format == "hex32") {
        for (size_t i = 0; i < fsize-3; i+=4) {
            char32_t t1 = buffer[i];
            char32_t t2 = buffer[i+1];
            char16_t t3 = buffer[i+2];
            std::cout
                << std::setw(8)
                << std::setfill('0')
                << std::hex
                << static_cast<int>((t1 << 24) | (t2 << 16) | (t3 << 8) | buffer[i+3])
                << " ";
        }
    }

    std::cout << std::endl;
    delete[] buffer;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "There must be exactly 3 arguments\n";
        return EXIT_FAILURE;
    }

    binaryRepresentation(argv[1], argv[2]);
#ifdef DEBUG
    binaryRepresentation("hex8", "test_case.txt");
    binaryRepresentation("dec8", "test_case.txt");
    binaryRepresentation("hex16", "test_case.txt");
    binaryRepresentation("dec16", "test_case.txt");
    binaryRepresentation("hex32", "test_case.txt");
#endif

    return EXIT_SUCCESS;
}
