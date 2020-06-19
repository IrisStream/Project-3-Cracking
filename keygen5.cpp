#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

std::string dict = "QWERTYUIOPASDFGHJKLZXCVBNM1234567890";
std::vector<std::pair<unsigned int, std::string> > midfix;
std::vector<std::pair<unsigned int, std::string> > postfix;
std::string prefix[100];

char encrypt(char c, int i)
{
    char ans = c + i;
    if(c < 0x21)
    {
        c+= 0x21;
    }
    if(c > 0x7b)
    {
        c = c >> 1;
    }
    return ans;
}

char decrypt(char c, int i)
{
    if(c - i < 0x21)
    {
        return c*2 - i;
    }
    return c - i;
}

// void generateKey()
// {
//     std::ofstream keyFile("key5.txt");
//     int count = 0;
//     for(char first : dict)
//     {
//         for(char second : dict)
//         {
//             for(char third : dict)
//             {
//                 for(char fourth : dict)
//                 {
//                     unsigned int value =  (((fourth*256+third)*256 + second)*256 + first) % 100;
//                     if(prefix[value].size())
//                     {
//                         std::string key = "";
//                         key += prefix[value];
//                         key += decrypt(first, 14);
//                         key += decrypt(second, 13);
//                         key += decrypt(third, 12);
//                         key += decrypt(fourth, 11);
//                         keyFile << key << std::endl;
//                         count++;
//                         if(count == 100000)
//                             return;
//                     }
//                 }
//             }
//         }
//     }
//     keyFile.close();
// }
void generateKey2()
{

    std::ofstream keyFile("key5.txt");
    for(char first : dict)
    {
        for(char second : dict)
        {
            std::string encrypted;
            encrypted += encrypt(first, 14);
            encrypted += encrypt(second, 13);
            unsigned int value = (encrypted[0] + encrypted[1] * 256) % 100;
            encrypted = first;
            encrypted +=second;
            midfix.push_back(std::make_pair(value, encrypted));
        }
    }
    for(char third : dict)
    {
        for(char fourth : dict)
        {
            std::string encrypted;
            encrypted += encrypt(third, 12);
            encrypted += encrypt(fourth, 11);
            unsigned int value = (((encrypted[1]*256+encrypted[0])*256)*256) % 100;
            encrypted = third;
            encrypted += fourth;
            postfix.push_back(std::make_pair(value, encrypted));
        }
    }
    int count = 0;
    for(auto x : midfix)
    {
        for(auto y : postfix)
        {
            int value = (x.first+y.first) % 100;
            if(prefix[value].size())
            keyFile << prefix[value] << x.second << y.second << std::endl;
        }
    }
    std::cout << count;
    keyFile.close();
}

int main()
{
    for(char first : dict)
    {
        for(char second : dict)
        {
            char First = encrypt(first, 16);
            char Second = encrypt(second, 15);
            int value = (Second * 256 + First) - 0x1a1c;
            if ((value / 256) >= '0' && (value/256) <= '9' && (value % 256) >= '0' && (value % 256) <= '9')
                {
                    prefix[(value % 256 % 16) * 10 + (value / 256 % 16)] = first;
                    prefix[(value % 256 % 16) * 10 + (value / 256 % 16)] += second;
                }
        }
    }
    generateKey2();
    return 0;
}