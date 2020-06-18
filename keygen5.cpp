#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::string dict = "`1234567890-=!@#$%^&*()_+qwertyuiop[]asdfghl;'zxcvbnm,./<>?:\"{\\|QWERTYUIOPASDFGHJKLZXCVBNM";
std::string prefix[100];
std::string postfix[100];
bool check[100];

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

void generateKey()
{
    std::ofstream keyFile("key5.txt");
    int count = 0;
    for(char first : dict)
    {
        for(char second : dict)
        {
            for(char third : dict)
            {
                for(char fourth : dict)
                {
                    unsigned int value =  (((fourth*256+third)*256 + second)*256 + first);
                    if(check[value % 100])
                    {
                        std::string key = "";
                        key += prefix[value % 100];
                        key += decrypt(first, 14);
                        key += decrypt(second, 13);
                        key += decrypt(third, 12);
                        key += decrypt(fourth, 11);
                        keyFile << key << std::endl;
                        // count++;
                        // if(count == 1000000)
                        //     return;
                    }
                }
            }
        }
    }
    keyFile.close();
}
void generateKey2()
{

    std::ofstream keyFile("key5.txt");
    int count = 0;
    for(char third : dict)
    {
        for(char fourth : dict)
        {
            int value =  ((fourth*256+third)*256)*256;
            p
        }
    }
    keyFile.close();
}

int main()
{
    for(int i = 0;i<100;i++)
        check[i] = false;
    for(char first : dict)
    {
        for(char second : dict)
        {
            char First = encrypt(first, 16);
            char Second = encrypt(second, 15);
            int value = (Second * 256 + First) - 0x1a1c;
            if ((value / 256) >= '0' && (value/256) <= '9' && (value % 256) >= '0' && (value % 256) <= '9')
                {
                    check[(value % 256 % 16) * 10 + (value / 256 % 16)] = true;
                    prefix[(value % 256 % 16) * 10 + (value / 256 % 16)] = first;
                    prefix[(value % 256 % 16) * 10 + (value / 256 % 16)] += second;
                }
        }
    }
    //generateKey();
    return 0;
}