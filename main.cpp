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
    int house_number;
    int flat_number;
};

struct citizen
{
    std::string snp;
    address Address;
    bool gender;
    int age;
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
    if (element.gender == 1)
    {
        std::cout << "Man ";
    }
    if (element.gender == 0)
    {
        std::cout << "Woman ";
    }
    std::cout << element.age << "\n";
}

std::ostream& operator<<(std::ostream &outt1, const address &value)
{
    outt1 << value.street << " " << value.house_number << " " << value.flat_number;
    return outt1;
}

std::ostream& operator<<(std::ostream &outt, const citizen &value)
{
    outt << value.snp << " " << value.Address <<  " ";
    if (value.gender == 1)
    {
        outt << "Man ";
    }
    if (value.gender == 0)
    {
        outt << "Woman ";
    }
    outt << " " << value.age << "\n";
    return outt;
}

std::istream& operator>>(std::istream &inn1, address &value)
{
    inn1 >> value.street >> value.house_number >> value.flat_number;
    return inn1;
}

std::istream& operator>>(std::istream &inn, citizen &value)
{
    inn >> value.snp >> value.Address >> value.gender >> value.age;
    return inn;
}

int main()
{
    std::vector<citizen> utilities;
    std::cout << "Enter the number of citizens: ";
    int n;
    std::cin >> n;
    /*
    for (int h=0; h<n; h++)
    {
        std::cout << "Enter surname, name and patronymic of " << h+1 << " citizen: ";
        std::string SNP;
        std::cin.ignore(10, '\n');
        std::getline(std::cin, SNP);
        std::cout << "Enter street of " << h+1 << " citizen: ";
        std::string Street;
        std::getline(std::cin, Street);
        std::cout << "Enter number of house of " << h+1 << " citizen: ";
        int House_number;
        std::cin >> House_number;
        std::cout << "Enter number of flat of " << h+1 << " citizen: ";
        int Flat_number;
        std::cin >> Flat_number;
        std::cout << "Enter gender (Man - 1 or woman - 0) of " << h+1 << " citizen: ";
        bool Gender;
        std::cin >> Gender;
        std::cout << "Enter age of " << h+1 << " citizen: ";
        int Age;
        std::cin >> Age;
        address Address = {Street, House_number, Flat_number};
        citizen Citizen = {SNP, Address, Gender, Age};
        utilities.push_back(Citizen);
    }
    */
    std::ifstream infile("input.txt");
    std::string str;
    std::string SNP;
    std::string Street;
    int House_number;
    int Flat_number;
    bool Gender;
    int Age;
    while (!infile.eof())
    {
        for (int k=0; k<6*n; k++)
        {
            std::getline(infile, str);
            if (k%6==0)
            {
                SNP = str;
            }
            if (k%6==1)
            {
                Street = str;
            }
            if (k%6==2)
            {
                House_number = atoi(str.c_str());
            }
            if (k%6==3)
            {
                Flat_number = atoi(str.c_str());
            }
            if (k%6==4)
            {
                if (str == "Man")
                {
                    Gender = 1;
                }
                if (str == "Woman")
                {
                    Gender = 0;
                }
            }
            if (k%6==5)
            {
                Age = atoi(str.c_str());
                address Address = {Street, House_number, Flat_number};
                citizen Citizen = {SNP, Address, Gender, Age};
                utilities.push_back(Citizen);
            }
        }
    }
    infile.close();
    std::cout << "\n";
    for (citizen h: utilities)
    {
        print_citizen(h);
    }
    std::cout << "\n";
    std::sort(utilities.begin(), utilities.end(), [](const citizen& lhs, const citizen& rhs) {return lhs.snp < rhs.snp;});
    for (citizen h: utilities)
    {
        print_citizen(h);
    }
    std::cout << "Enter the street: ";
    std::string word;
    std::cin.ignore(10, '\n');
    std::getline(std::cin, word);
    int s=0;
    for (citizen h: utilities)
    {
        if ((h.age>80) && (h.Address.street == word))
        {
            s=s+1;
        }
    }
    std::ofstream outfile("output.txt");
    for (citizen h: utilities)
    {
        outfile << h;
    }
    std::cout << "There are " << s << " people with age > 80 living on the " << word << " street";
    outfile << "There are " << s << " people with age > 80 living on the " << word << " street";
    outfile.close();
    return 0;
}
