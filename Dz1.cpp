#include <iostream>
#include <cstdint>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <chrono>

struct Block {
    uint64_t shortstr = 0;
};

Block operator^(Block &block, uint64_t key) {
    block.shortstr = block.shortstr ^ key;
    return block;
}

Block operator|(Block &block1, Block &block2) {
    block1.shortstr = block1.shortstr | block2.shortstr;
    return block1;
}

void operator>>(Block &block, unsigned int sdvig) {
    block.shortstr = (block.shortstr >> sdvig) | (block.shortstr << (64 - sdvig));
}

void operator<<(Block &block, unsigned int sdvig) {
    block.shortstr = (block.shortstr << sdvig) | (block.shortstr >> (64 - sdvig));
}


void Code(std::string ifs, std::string ofs) {
    std::ifstream in(ifs, std::ios::binary);
    std::string text;
    in.seekg(0, std::ios::end);
    size_t sizebytes = in.tellg();
    in.seekg(0, std::ios::beg);
    in.read(text.data(), sizebytes);
    in.close();
    Block block;
    uint8_t sizeprob = 0;
    while (sizebytes % 8 != 0) {
        sizebytes++;
        sizeprob++;
        text.data()[sizebytes - 1] = 68;// рандомные буквы
        text.data()[sizebytes] = 0;
    }
    block.shortstr = 0;
    std::ofstream out(ofs, std::ios::binary);
    for (int i = 0; i < sizebytes; i++) {
        block.shortstr = block.shortstr + text.data()[i];
        block >> 8;
        if (i % 8 == 7 || i == sizebytes - 1) {
            uint64_t shfr = 0;
            for (int i = 0; i < 4; i++) {
                shfr += rand();
                shfr = shfr << 16;
            }
            block ^ shfr;
            block >> 5;
            out.write(reinterpret_cast<char *>(&block.shortstr), sizeof(uint64_t));
            block.shortstr = 0;
        }
    }
    out.write(reinterpret_cast<char *>(&sizeprob), sizeof(uint8_t));
    out.close();
}

void Decode(std::string ifs, std::string ofs) {
    std::ifstream in(ifs, std::ios::binary);
    std::ofstream out(ofs, std::ios::binary);
    Block block;
    uint8_t sizeprobe = 0;
    while (in.read(reinterpret_cast<char *>(&block.shortstr), sizeof(uint64_t))) {
        uint64_t shfr = 0;
        for (int b = 0; b < 4; b++) {
            shfr += rand();
            shfr = shfr << 16;
        }
        block << 5;
        block ^ shfr;
        sizeprobe = 0;
        if (!in.read(reinterpret_cast<char *>(&sizeprobe), sizeof(uint8_t))) {
            block.shortstr = block.shortstr << 8 * sizeprobe;
            out.write(reinterpret_cast<char *>(&block.shortstr), sizeof(uint64_t));
            continue;
        }
        out.write(reinterpret_cast<char *>(&block.shortstr), sizeof(uint64_t));
        block.shortstr = 0;
    }
    in.close();
    out.close();
}

int main(int argc, char* argv[]) {
//    auto start1 = std::chrono::system_clock::now();
//    //  Code("text.txt", "textout.txt");
//    Decode("textout.txt", "decode.txt");
//    auto end1 = std::chrono::system_clock::now();
//    auto time1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);
//    std::cout << "The time " << time1.count() << std::endl;
    std::string mode=argv[1];
    std::string vectorin=argv[2];
    if(mode=="code"){
        Code(argv[3],argv[4]);
    }

    if(mode=="decode"){
        Decode(argv[3],argv[4]);
    }
    return 0;
}