#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cstring>

struct address
{
    std::string street;
    int house_number = 0;
    int flat_number = 0;
};

struct citizen
{
    std::string snp;
    address Address;
    std::string gender;
    int age = 0;
};

void print_address(address element)
{
    std::cout << element.street << " ";
    std::cout << element.house_number << " ";
    std::cout << element.flat_number << " ";
}

void print_citizen(citizen element)
{
    std::cout << element.snp << " ";
    print_address(element.Address);
    std::cout << " ";   
    std::cout << element.gender << " ";
    std::cout << element.age << "\n";
}

std::ostream& operator<<(std::ostream& outt1, const address& value)
{
    outt1 << value.street << " " << value.house_number << " " << value.flat_number;
    return outt1;
}

std::ostream& operator<<(std::ostream& outt, const citizen& value)
{
    outt << value.snp << " " << value.Address << " ";
    outt  << value.gender << " " << value.age << "\n";
    return outt;
}

std::istream& operator>>(std::istream& inn1, address& value)
{
    inn1 >> value.street >> value.house_number >> value.flat_number;
    return inn1;
}

std::istream& operator>>(std::istream& inn, citizen& value)
{
    inn >> value.snp >> value.Address >> value.gender >> value.age;
    return inn;
}

void Text_reading(int& n, std::string& str, std::string& SNP, std::string& Street, int& House_number, int& Flat_number, std::string& Gender, int& Age, std::vector<citizen>& utilities)
{
    std::ifstream infile("input.txt");
    while (!infile.eof())
    {
        for (int k = 0; k < 6 * n; k++)
        {
            std::getline(infile, str);
            if (k % 6 == 0)
            {
                SNP = str;
            }
            if (k % 6 == 1)
            {
                Street = str;
            }
            if (k % 6 == 2)
            {
                House_number = atoi(str.c_str());
            }
            if (k % 6 == 3)
            {
                Flat_number = atoi(str.c_str());
            }
            if (k % 6 == 4)
            {
                Gender = str;
            }
            if (k % 6 == 5)
            {
                Age = atoi(str.c_str());
                address Address = { Street, House_number, Flat_number };
                citizen Citizen = { SNP, Address, Gender, Age };
                utilities.push_back(Citizen);
            }
        }
    }
    infile.close();
}

void Text_writing(std::vector<citizen>& utilities)
{
    std::ofstream outfile("output.txt");
    for (citizen h : utilities)
    {
        outfile << h;
    }
    outfile.close();
}

void Bin_reading(std::vector<citizen>& utilities)
{
    std::ifstream infile("input2.txt", std::ios::binary);
    citizen Citizen;
    address Address;
    uint8_t string_size;
    while (infile.read(reinterpret_cast<char*> (&string_size), sizeof(uint8_t)))
    {
        Citizen.snp.resize(string_size);
        infile.read(Citizen.snp.data(), string_size);
        infile.read(reinterpret_cast<char*> (&string_size), sizeof(uint8_t));
        Citizen.Address.street.resize(string_size);
        infile.read(Citizen.Address.street.data(), string_size);
        infile.read(reinterpret_cast<char*> (&Citizen.Address.house_number), sizeof(uint8_t));
        infile.read(reinterpret_cast<char*> (&Citizen.Address.flat_number), sizeof(uint8_t));
        infile.read(reinterpret_cast<char*> (&string_size), sizeof(uint8_t));
        Citizen.gender.resize(string_size);
        infile.read(Citizen.gender.data(), string_size);
        infile.read(reinterpret_cast<char*> (&Citizen.age), sizeof(uint8_t));
        utilities.push_back(Citizen);
    }
    infile.close();
}

void Bin_writing(std::vector<citizen>& utilities)
{
    std::ofstream outfile("output2.txt", std::ios::binary);
    uint8_t string_size;
    for (int h = 0; h < utilities.size(); h++)
    {
        string_size = utilities[h].snp.length();
        outfile.write(reinterpret_cast<const char*> (&string_size), sizeof(uint8_t));
        outfile.write(utilities[h].snp.data(), string_size);
        string_size = utilities[h].Address.street.length();
        outfile.write(reinterpret_cast<char*> (&string_size), sizeof(uint8_t));
        outfile.write(utilities[h].Address.street.data(), string_size);
        outfile.write(reinterpret_cast<char*> (&utilities[h].Address.house_number), sizeof(uint8_t));
        outfile.write(reinterpret_cast<char*> (&utilities[h].Address.flat_number), sizeof(uint8_t));
        string_size = utilities[h].gender.length();
        outfile.write(reinterpret_cast<char*> (&string_size), sizeof(uint8_t));
        outfile.write(utilities[h].gender.data(), string_size);
        outfile.write(reinterpret_cast<char*> (&utilities[h].age), sizeof(uint8_t));
    }
    outfile.close();
}

int main()
{
    std::vector<citizen> utilities;
    std::cout << "Enter the number of citizens: ";
    int n;
    std::cin >> n;
    std::string str;
    std::string SNP;
    std::string Street;
    int House_number;
    int Flat_number;
    std::string Gender;
    int Age;
    //Text_reading (n, str, SNP, Street, House_number, Flat_number, Gender, Age, utilities);
    Bin_reading(utilities, n);
    std::cout << "\n";
    for (citizen h : utilities)
    {
        print_citizen(h);
    }
    std::cout << "\n";
    std::sort(utilities.begin(), utilities.end(), [](const citizen& lhs, const citizen& rhs) {return lhs.snp < rhs.snp; });
    for (citizen h : utilities)
    {
        print_citizen(h);
    }
    std::cout << "\n";
    std::cout << "Enter the street: ";
    std::string word;
    std::cin.ignore(10, '\n');
    std::getline(std::cin, word);
    int s = 0;
    std::vector<citizen> men;
    std::vector<citizen> women;
    for (citizen h : utilities)
    {
        if ((h.age > 80) && (h.Address.street == word))
        {
            s = s + 1;
            if (h.gender == "Man")
            {
                men.push_back(h);
            }
            else
            {
                women.push_back(h);
            }
        }
    }
    //Text_writing(utilities);
    Bin_writing(utilities);
    std::cout << "There are " << s << " people with age > 80 living on the " << word << " street.\n";
    if (s != 0)
    {
        std::cout << "Men:";
        if (men.size() == 0)
        {
            std::cout << "---";
        }
        for (citizen h : men)
        {
            std::cout << "\n";
            print_citizen(h);
        }
        std::cout << "Women:\n";
        if (women.size() == 0)
        {
            std::cout << "---";
        }
        for (citizen h : women)
        {
            std::cout << "\n";
            print_citizen(h);
        }
    }
    std::cout << "\n";
    return 0;
}
