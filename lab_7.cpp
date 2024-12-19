#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

enum Mode {under = -1, current = 0, over = + 1};
static int flag = 0;

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
    if(flag == 0)
    {
        std::ofstream ofstrm{filename.c_str(), std::ios::trunc};
        if(ofstrm.is_open())
        {
            for(const auto& val : number)
            {
                ofstrm << val << " ";
            }
            // ofstrm << "\n";
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
            // ofstrm << "\n";
        }
        ofstrm.close();
    }   
}

void pasteSymbol(const std::string& filename, const std::string& symbol)
{
    if(flag == 0)
    {
        std::ofstream ofstrm{filename.c_str()};
        if(ofstrm.is_open())
        {
            ofstrm << symbol;
            ofstrm.close();
            ++flag;
        }
    }
    else
    {
        std::ofstream ofstrm{filename.c_str(), std::ios::app};
        if(ofstrm.is_open())
        {
            ofstrm << symbol;
            ofstrm.close();
        }
    }
}

template <typename T>
std::vector<T> String_To_Number(const std::string& str, const std::string& separator, const size_t amount_of_number = std::string::npos)
{
    size_t start;
    size_t end = 0;
    std::vector<T> number;
    size_t iteration = 0;

    while(((start = str.find_first_of(separator, end)) != std::string::npos) && iteration != amount_of_number)
    {
        end = str.find(separator, start);
        number.push_back(stod(str.substr(start, end - 1)));
        ++iteration;
    }

    return number;
}

std::vector<std::string> SearchString(const std::string& str, const std::string& search, Mode mode)
{
    size_t start = 0;
    size_t end = 0;
    std::vector<std::string> vector_of_string;

    switch(mode)
    {
        case under:
            while((start = str.find(search, start)) != std::string::npos)
            {
                end = str.find('\n', start) + 1;
                start = end;
                end = str.find('\n', start);

                vector_of_string.push_back(str.substr(start, end - start));
                start = end + 1;
            }

        case current:
            size_t fixed_pos = search.size();
            while((start = str.find(search, start)) != std::string::npos)
            {
                start += fixed_pos; 
                end = str.find('\n', start);
                vector_of_string.push_back(str.substr(start, end - start));
                start = end;
            }
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

//  testing 2
void writeStringInFile(const std::string& filename, const std::string& writeable_str)
{
    std::ofstream ofstr{filename.c_str()};
    if (ofstr.is_open())
    {   
        ofstr << writeable_str;
        ofstr.close();
    }
}

void setConfig(std::string& config, std::string namefile)
{
    size_t end = config.size();
    config = config + "INGET:" + namefile + ".dat\n";
    config = config + "OUTGET:" + namefile + ".out\n";
}

int main()
{

    std::string config{"EDIT:cons.dat\nEDIT0:..\\bin\\cons0.dat\nBETA:..\\bin\\beta.get\nBNAB.BIN:..\\bin\\Bnab90.lib\nBNABMLT.BIN:..\\bin\\Bnabmlt.lib\nBNABTHM.BIN:..\\bin\\BNABTHM.lib\nBNAB:..\\bin\\XE35.MLT\nF11:..\\bin\\f11\n"};
    int key;
    std::string output_GETERA_file;
    std::cout << "korp_but.dat is 0\n" << "kan_bur.dat is 1" << std::endl;
    std::cin >> key; 

    if (key == 0) {
        setConfig(config, "korp_bur");
        writeStringInFile("CONFIG.DRV", config);
        system("getera.exe");
        output_GETERA_file = readFile("korp_bur.out");
    } else {
        setConfig(config, "kan_bur");
        writeStringInFile("CONFIG.DRV", config);
        system("getera.exe");
        output_GETERA_file = readFile("kan_bur.out");
    }


    std::vector<std::string> string_K_eff = SearchString(output_GETERA_file, "    keff         nu           mu           fi           teta", under);
    std::vector<std::string> string_B = SearchString(output_GETERA_file, "average burn up", current);
    std::vector<std::string> string_pu40 = SearchString(output_GETERA_file, " pu40     ", current);
    std::vector<std::string> string_pu39 = SearchString(output_GETERA_file, " pu39     ", current);
    std::vector<std::string> string_u235 = SearchString(output_GETERA_file, " u235    ", current);

    std::vector<double> number_B;
    std::vector<double> number_k_eff;
    std::vector<double> number_pu40;
    std::vector<double> number_pu39;
    std::vector<double> number_u235;
    
    pasteSymbol("OUTPUT.txt", "\nK_eff :\n");
    for(const auto& str : string_K_eff)
    {
        number_k_eff = String_To_Number<double>(str, "0123456789", 1);  
        writeFile("OUTPUT.txt", number_k_eff);
        pasteSymbol("OUTPUT.txt", "\n");
    }

    pasteSymbol("OUTPUT.txt", "\nB :\n");
    pasteSymbol("OUTPUT.txt", std::to_string(0.0) + "\n");
    for(const auto& str : string_B)
    {
        number_B = String_To_Number<double>(str, "0123456789", 1);  
        writeFile("OUTPUT.txt", number_B);
        pasteSymbol("OUTPUT.txt", "\n");
    }

    pasteSymbol("OUTPUT.txt", "\nPu-240 :\n");
    pasteSymbol("OUTPUT.txt", std::to_string(0.0) + "\n");
    for(const auto& str : string_pu40)
    {
        number_pu40 = String_To_Number<double>(str, "0123456789", 1);  
        writeFile("OUTPUT.txt", number_pu40);
        pasteSymbol("OUTPUT.txt", "\n");
    }
    
    pasteSymbol("OUTPUT.txt", "\nPu-239 :\n");
    pasteSymbol("OUTPUT.txt", std::to_string(0.0) + "\n");
    for(const auto& str : string_pu39)
    {
        number_pu39 = String_To_Number<double>(str, "0123456789", 1);  
        writeFile("OUTPUT.txt", number_pu39);
        pasteSymbol("OUTPUT.txt", "\n");
    }

    pasteSymbol("OUTPUT.txt", "\nU-235 :\n");
    for(const auto& str : string_u235)
    {
        number_u235 = String_To_Number<double>(str, "0123456789", 1);  
        writeFile("OUTPUT.txt", number_u235);
        pasteSymbol("OUTPUT.txt", "\n");
    }

}
