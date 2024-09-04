#include <string>
#include <iostream>
#include <sstream>

#include "m_exceptions.h"
#include "parser.h"
#include "cmd_reader.h"



size_t Treat_Arguments(int& argc, char** argv)
{
    if (argc > 2)
    {
        throw TooManyArguments("Too many arguments. Enter only one integer when you run the program.");
    }
    else if (argc == 1)
    {
        throw NoArguments("No arguments have been entered. The default value N = 3 is used.");
    }

    return std::stoi(argv[1]);    
}

void Start(size_t N, std::istream& input, std::ostream& output)
{
    CommandReader reader{N};
    Parser parser{output};

    reader.Attach(&parser);

    while (!reader.IsEof())
    {
        try
        {
            reader.Read(input);            
        }
        catch (const UnknownCommand& ex)
        {
            std::cerr << "Error: " << ex.what() << std::endl;
            continue;
        }
        catch (const std::ios_base::failure& ex)
        {
            std::cerr << "Error: " << ex.what() << std::endl;
            continue;
        }
        catch (const std::exception& ex)
        {
            std::cerr << "Error: " << ex.what() << std::endl;
            break;
        }   
    }
}

int main(int argc, char* argv[])
{
    size_t N{};

    try
    {
        N = Treat_Arguments(argc, argv);
    }
    catch (const TooManyArguments& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    catch (const NoArguments& ex)
    {
        std::cerr << ex.what() << std::endl;
        N = 3; //default value
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    
    std::istringstream static_test(std::string{"cmd1\ncmd2\ncmd3\ncmd4\ncmd5\n"});
    std::istringstream dynamic_test(std::string{"cmd1\ncmd2\n{\ncmd3\ncmd4\n}\n{\ncmd5\ncmd6\n{\ncmd7\ncmd8\n}\ncmd9\n}\n{\ncmd10\ncmd11\n"});

    std::cout << "\t***   static_test   ***" << std::endl;
    Start(N, static_test, std::cout);

    std::cout << "\n\t***   dynamic_test   ***" << std::endl;
    Start(N, dynamic_test, std::cout);

    return 0;
}

