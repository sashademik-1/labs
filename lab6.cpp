#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <ostream>
#include <cstring>
//while(is){for{Citizen считывать потом создавать нового и добавлять в вектор}
struct Citizen
{
    std::string FCs;
    struct Adress
    {
        std::string street;
        int housenumber;
        int flatnumber;
    } way;
    std::string gender;
    int age;
};
std::ostream &operator<<(std::ostream &os, const std::vector<Citizen> &Person) // Запись
{
    os << "Citizen in file " << Person.size()<<"\n";
    for (Citizen Person : Person)
        os << "FCs: " << Person.FCs << "\n"
           << "Street: " << Person.way.street << "\n"
           << "house: " << Person.way.housenumber << "\n"
           << "flat: " << Person.way.flatnumber << "\n"
           << "Gender: " << Person.gender << "\n"
           << "age: " << Person.age << "\n";

    return os;
}
std::istream &operator>>(std::istream &is, std::vector<Citizen> &Person) // Чтение

{
    is.ignore(16);
    std::string str;
    std::getline(is, str);
    int i = std::stoi(str);
    Person.resize(i);
    for (Citizen &Person : Person)
    {
        is.ignore(5);
        std::getline(is, Person.FCs);
        is.ignore(8);
        std::getline(is, Person.way.street);
        is.ignore(7);
        std::getline(is, str);
        Person.way.housenumber = std::stoi(str);
        is.ignore(6);
        std::getline(is, str);
        Person.way.flatnumber = std::stoi(str);
        is.ignore(8);
        std::getline(is, Person.gender);
        is.ignore(5);
        std::getline(is, str);
        Person.age = std::stoi(str);
    }
    return is;
}
void ost(const std::vector<Citizen> &Person, std::ofstream &outfile)
{
    size_t length = Person.size();
    outfile.write(reinterpret_cast<char *>(&length), sizeof(size_t));
    for (Citizen Person : Person)
    {
         length = Person.FCs.length();
        outfile.write(reinterpret_cast<char *>(&length), sizeof(size_t));
        outfile.write(reinterpret_cast<char *>(&Person.FCs), length);
        length = Person.way.street.length();
        outfile.write(reinterpret_cast<char *>(&length), sizeof(size_t));
        outfile.write(reinterpret_cast<char *>(&Person.way.street), length);
        outfile.write(reinterpret_cast<char *>(&Person.way.housenumber), sizeof(int));
        outfile.write(reinterpret_cast<char *>(&Person.way.flatnumber), sizeof(int));
        length = Person.gender.length();
        outfile.write(reinterpret_cast<char *>(&length), sizeof(size_t));
        outfile.write(reinterpret_cast<char *>(&Person.gender), length);
        outfile.write(reinterpret_cast<char *>(&Person.age), sizeof(int));
    }
}
void ifs(std::vector<Citizen> &Person, std::ifstream &infile)
{
    size_t length = 0;
    infile.read(reinterpret_cast<char *>(&length), sizeof(size_t));
    Person.resize(length);
    for (Citizen &Person : Person)
    {
        infile.read(reinterpret_cast<char *>(&length), sizeof(size_t));
        Person.FCs.resize(length);
        infile.read(&Person.FCs[length], length);

        infile.read(reinterpret_cast<char *>(&length), sizeof(size_t));
        Person.way.street.resize(length);
        infile.read(&Person.way.street[length], length);

        infile.read(reinterpret_cast<char *>(&Person.way.housenumber), sizeof(int));
        infile.read(reinterpret_cast<char *>(&Person.way.flatnumber), sizeof(int));

        infile.read(reinterpret_cast<char *>(&length), sizeof(size_t));
        Person.gender.resize(length);
        infile.read(&Person.gender[length], length);
        infile.read(reinterpret_cast<char *>(&Person.age), sizeof(int));
    }
}
int main()
{
    std::cout << "Kol-vo citizen" << std::endl;
    int Kolvo = 0;
    std::cin >> Kolvo;
    std::vector<Citizen> Person(Kolvo);
   std::cin.ignore();
    for (Citizen &Person : Person)
    {
        std::cout << " FCs " << std::endl;
        std::getline(std::cin, Person.FCs);
        std::cout << " street" << std::endl;
        std::getline(std::cin, Person.way.street);
        std::cout << " house" << std::endl;
        std::cin >> Person.way.housenumber;
        std::cout << "Flat " << std::endl;
        std::cin >> Person.way.flatnumber;
        std::cout << "gender " << std::endl;
        std::cin >> Person.gender;
        std::cout << "age " << std::endl;
        std::cin >> Person.age;
        std::cin.ignore();
    }
    std::sort(Person.begin(), Person.end(), [](const Citizen &Person, const Citizen &Person1) { return Person.FCs < Person1.FCs; });
    for (Citizen Person : Person)
    {
        std::cout << Person.FCs << std::endl;
    }
    std::string Street;
    std::getline(std::cin, Street);
    std::cout << "male <50  " << std::count_if(Person.begin(), Person.end(), [Street](Citizen Person) mutable { return (Person.gender == "male") && (Person.age < 50) && Person.way.street == Street; }) << "\n";
    for (Citizen Person : Person)
    {
        if (Person.gender == "male" && Person.age < 50 && Person.way.street == Street)
            std::cout << Person.FCs << ", " << std::endl;
    }
    std::cout << "female  <50  " << std::count_if(Person.begin(), Person.end(), [Street](Citizen Person) mutable { return (Person.gender == "female") && (Person.age < 50) && Person.way.street == Street; }) << "\n ";
    for (Citizen &Person : Person)
    {
        if (Person.gender == "female" && Person.age < 50 && Person.way.street == Street)
            std::cout << Person.FCs << ", " << std::endl;
    }
    std::cout << "---------------" << std::endl;
    for (Citizen &Person : Person)
    {
        std::cout << Person.FCs << std::endl;
    }
    std::ofstream out("text.txt");
    out << Person << std::endl;
    std::ifstream in("text.txt");
    in >> Person;
    std::ofstream out2("text2", std::ios::binary);
    ost(Person, out2);
    out2.close();
    std::ifstream in2("text2", std::ios::binary);
    ifs(Person, in2);
    for (Citizen &Person : Person)
    {
        std::cout << Person.FCs << std::endl;
        std::cout << Person.way.street <<  std::endl;
        std::cout << Person.way.housenumber << std::endl;
        std::cout << Person.way.flatnumber << std::endl;
        std::cout << Person.gender <<  std::endl;
        std::cout << Person.age << std::endl;
    }
    in2.close();
    return 0;
}
