#include <iostream>
#include <filesystem>
#include <string>
int main() {
    bool b = true;
    int action = 0;
    while (b) {
        std::filesystem::path path1 = std::filesystem::current_path();
        std::cout << path1 << std::endl;
        for (int i = 1; auto file: std::filesystem::directory_iterator(path1)) {//2
            std::cout << i << ". " << file.path().filename() << std::endl;
            i++;
        }
        std::cout << "Choose the action" << std::endl;
        std::cin >> action;
        switch (action) {// кол-во файлов в дирректории
            case 1: {//3
                std::string filename;
                std::cout << "Enter a filename" << std::endl;
                std::cin.ignore();
                std::getline(std::cin, filename);
                path1.append(filename);
                if (!std::filesystem::exists(path1)) {
                    std::filesystem::create_directories(path1);
                } else {
                    std::cout << "The name is busy" << std::endl;
                }
                break;
            }
            case 2: {//4
                std::cout << "Choose file" << std::endl;
                std::cin >> action;
                auto p = std::filesystem::directory_iterator(path1);
                for (int fileorder = 1; fileorder != action; fileorder++) {
                    p++;
                }
                std::cout << p->path().filename() << " size is " << std::filesystem::file_size(p->path()) << std::endl;
            }
                break;
            case 3: {//5

                std::cout << "Choose file for copy" << std::endl;
                std::cin >> action;
                auto p = std::filesystem::directory_iterator(path1);
                for (int fileorder = 1; fileorder != action; fileorder++) {
                    p++;
                }
                std::cout << "write the name of file" << std::endl;
                std::string nameoffile;
                std::cin.ignore();
                getline(std::cin, nameoffile);
                std::filesystem::copy_file(p->path().filename(), nameoffile);
            }
                break;
            case 4: {//6 проверить с вложенным каталогом
                std::cout << "Choose file for delete" << std::endl;
                std::cin >> action;
                auto p = std::filesystem::directory_iterator(path1);
                for (int fileorder = 1; fileorder != action; fileorder++) {
                    p++;
                }
                std::filesystem::remove(p->path().filename());
            }
                break;
            case 5: {//7
                std::cout << "Choose path for delete" << std::endl;
                std::cin >> action;
                auto p = std::filesystem::directory_iterator(path1);
                for (int fileorder = 1; fileorder != action; fileorder++) {
                    p++;
                }
                std::filesystem::remove_all(p->path().filename());
            }
                break;
            case 6: {//8
                std::cout << "Choose up or down" << std::endl;
                std::string way;
                std::cin.ignore();
                std::getline(std::cin, way);
                if (way == "up") {
                    std::filesystem::current_path(path1.parent_path());
                } else if (way == "down") {
                    std::cout << "Choose path" << std::endl;
                    std::cin >> action;
                    auto p = std::filesystem::directory_iterator(path1);
                    for (int fileorder = 1; fileorder != action; fileorder++) {
                        p++;
                    }
                    std::filesystem::current_path(p->path());
                }
            }
                break;
            case 7: {//9
                std::cout << "Choose a file for rename" << std::endl;
                std::cin >> action;
                auto p = std::filesystem::directory_iterator(path1);
                for (int fileorder = 1; fileorder != action; fileorder++) {
                    p++;
                }
                std::string newname;
                std::cin.ignore();
                std::getline(std::cin, newname);
                std::filesystem::rename(p->path().filename(), newname);

            }
                break;
            case 8: {//10
                std::cout << "Choose a file or directory for move" << std::endl;
                std::cin >> action;
                auto p = std::filesystem::directory_iterator(path1);
                for (int fileorder = 1; fileorder != action; fileorder++) {
                    p++;
                }
                std::string newpath;
                std::cin.ignore();
                std::getline(std::cin, newpath);
                std::filesystem::rename(p->path(), newpath);
            }
                break;
            case 9:
                b = false;
                break;
        }
    }
    return 0;
}
