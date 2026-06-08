#include "FileReplacer.hpp"

int	main(int argc, char *argv[])
{
    if (argc != 4) {
        std::cerr << "Error. Needed 3 arguments: <filename> <string 1> <string 2>" << std::endl;
        return 1;
    }
    FileReplacer replacer(argv[1], argv[2], argv[3]);

    if(replacer.process() == false)
        return 1;
    return 0;
}
