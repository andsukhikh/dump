#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>


std::string readFile(const std::string& filename)
{
    std::ifstream ifstrm{filename.c_str()};
    std::string out;
    if(ifstrm.is_open())
    {
        while(!ifstrm.eof())
        {
            char c{};
            ifstrm.get(c);
            out += c;
        }
        ifstrm.close();
    }

    return out;
}

template <typename T>
void writeFile(const std::string& filename, const std::vector<T>& number)
{
    static int flag = 0;
    if(flag == 0)
    {
        std::ofstream ofstrm{filename.c_str()};
        if(ofstrm.is_open())
        {
            ofstrm << "keff     nu     mu     fi     teta" << "\n";
            for(const auto& val : number)
            {
                ofstrm << val << " ";
            }
            ofstrm << "\n";
        }
        ofstrm.close();
        flag++;
    }
    else
    {
        std::ofstream ofstrm{filename.c_str(), std::ios::app};
        if(ofstrm.is_open())
        {
            for(const auto& val : number)
            {
                ofstrm << val << " ";
            }
            ofstrm << "\n";
        }
        ofstrm.close();
    }   
}

template <typename T>
std::vector<T> String_To_Vector(const std::string& str)
{
    size_t start;
    size_t end = 0;
    char separator = ' ';
    std::vector<T> number;
    size_t iteration = 0;

    while((start = str.find_first_not_of(separator, end + 1)) != std::string::npos)
    {
        end = str.find(separator, start);
        number.push_back(stod(str.substr(start, end - 1)));
    }

    return number;
}

std::vector<std::string> SearchString(const std::string& str, const std::string& search)
{
    size_t start = 0;
    size_t end = 0;
    std::vector<std::string> vector_of_string;

    while((start = str.find(search, start)) != std::string::npos)
    {
        end = str.find('\n', start) + 1;
        start = end;
        end = str.find('\n', start);

        vector_of_string.push_back(str.substr(start, end - start));
        start = end + 1;
    }

    return vector_of_string;

}

template <typename T>
void printVector(const std::vector<T>& vec, const char modification = '\n')
{
    if(modification == ' ')
    {
        for (const auto& value : vec)
        {
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    } 
    else
    {
        for (const auto& value : vec)
        {
            std::cout << value << std::endl;;
        }
    }
}


int main()
{
    std::string global_flow = readFile("kan_bur.out");
    std::vector<std::string> string_vector = SearchString(global_flow, "    keff         nu           mu           fi           teta");
    std::vector<double> vector_of_number;

    system("getera.exe");

    for(const auto& str : string_vector)
    {
        vector_of_number = String_To_Vector<double>(str);
        writeFile("OUTPUT.txt", vector_of_number);
    }
}
