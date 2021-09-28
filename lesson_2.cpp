#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <string>
#include <chrono>

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::string m_name;
    std::chrono::time_point<clock_t> m_beg;
    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }

public:
    Timer() : m_beg(clock_t::now()) { }
    Timer(std::string name) : m_name(name), m_beg(clock_t::now()) { }

    void start(std::string name) {
        m_name = name;
        m_beg = clock_t::now();
    }
    void print() const {
        std::cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
    }
};


template<typename T1, typename T2>

void Swap(T1 *a, T2 *b)
{
    T1 c = *a;
    *a = *b;
    *b = c;   
}
template<typename T1>

void SortPointers(std::vector<T1*>& vect)
{
    std::sort(vect.begin(), vect.end(), [](const T1* a, const T1* b)
        {return *a < *b;   });
}


//------------ count_if и find------------

bool my_find(char a)
{
    return a == 'A' || a == 'a' || a == 'E' || a == 'e' || a == 'I' || a == 'i' || a == 'O' || a == 'o' || a == 'U' || a == 'u' || a == 'Y' || a == 'y';
}

void count_if_(std::vector<char>& vect)
{
    Timer timer("count_if_");

    int my_count = count_if(vect.begin(), vect.end(), my_find);
    std::cout << my_count << " ";
    timer.print();
}

bool my_find_2(char a)
{
    std::vector<char> vec{ 'A','a','E','e','I','i','O','o','U','u','Y','y' };
    std::vector<char>::iterator it;
    it = find(vec.begin(), vec.end(), a);
    if (it != vec.end())
    {
        return true;
    }
   
}

void count_if_find(std::vector<char>& vect)
{
    Timer timer("count_if_");

    int my_count = count_if(vect.begin(), vect.end(), my_find_2);
    std::cout << my_count << " ";
    timer.print();
}




//------------count_if и цикл for------------
bool my_find_3(char a)
{
    char arr[] = { 'A','a','E','e','I','i','O','o','U','u','Y','y' };
    for (int i = 0; i < 12; ++i)
    {
        if (a == arr[i])
        {
            return true;
        }
    }
}

void count_if_for(std::vector<char>& vect)
{
    Timer timer("count_if_for");

    int my_count = count_if(vect.begin(), vect.end(), my_find_3);
    std::cout << my_count << " ";
    timer.print();
}


//------------цикл for и find------------
bool my_find_4(char a)
{
    std::vector<char> vec{ 'A','a','E','e','I','i','O','o','U','u','Y','y' };
    std::vector<char>::iterator it;
    it = find(vec.begin(), vec.end(), a);
    if (it != vec.end())
    {
        return true;
    }
}

void for_find(std::vector<char>& vect)
{
    
    Timer timer("for_find");
    int count = 0; 
    for (auto i : vect)
    {
        //bool res = false;
        bool res = my_find_4(i);
        if (res)
        {
            count++;
        }
    }
    std::cout << count;

    timer.print();
    
}

void for_for(std::vector<char>& vect)
{
    Timer timer("for_for");
    int count = 0;
    char arr [] = { 'A','a','E','e','I','i','O','o','U','u','Y','y' };
    for (auto i : vect)
    {
        for (int j = 0; j < 12; ++j)
        {
            if (i == arr[j])
            {
                count++;
            }
        }
    }
    std::cout << count << " ";
    timer.print();
}

int main()
{
    {
        //---------------EX_1--------------- Или я что-то не так понял или слишком простое задание 
        std::cout << "---------------EX_1---------------\n";
        size_t a = 45;
        size_t b = 10;

        std::cout << "A = " << a << '\n' << "B = " << b << std::endl;

        Swap(&a, &b);

        std::cout << "A = " << a << '\n' << "B = " << b << std::endl;

        //---------------EX_2--------------- 
        std::cout << "\n---------------EX_2---------------\n";
        int a_2 = 45;
        int b_2 = 37;
        int c_2 = 12;
        int d_2 = 10;
        int e_2 = 4;

        std::vector<int*> vec;

        vec.push_back(&a_2);
        vec.push_back(&b_2);
        vec.push_back(&c_2);
        vec.push_back(&d_2);
        vec.push_back(&e_2);

        for (auto i : vec)
        {
            std::cout << *i << " ";
        }
        std::cout << std::endl;

        SortPointers(vec);

        std::cout << std::endl;

        for (auto i : vec)
        {
            std::cout << *i << " ";
        }
    }
    //---------------EX_3--------------- 
    std::cout << "\n\n---------------EX_3---------------\n";
    std::vector<char> str_vec;
    std::ifstream text("War_and_peace.txt");
    std::string str;
    
    if (!text.is_open())
    {
        std::cout << "ERROR: File not found!" << std::endl;
    }
    else
    {
        char ch;
        while (text.get(ch))
        {
            str_vec.push_back(ch);
        }
        
    }
   
    std::cout << "Only count_if: ";
    count_if_(str_vec);

    std::cout << "count_if_find: ";
    count_if_find(str_vec);

    std::cout << "Count_if_for: ";
    count_if_for(str_vec);
   
    std::cout << "for_find: ";
    for_find(str_vec);
    
    std::cout << "for_for: ";
    for_for(str_vec);
    
   
    text.close();

}
