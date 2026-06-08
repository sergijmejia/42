#include "FileReplacer.hpp"

int	main(int argc, char *argv[])
{
	std::string	s1;

    if (argc != 4) {
        std::cerr << "Error. Needed 3 arguments: <filename> <string 1> <string 2>" << std::endl;
        return 1;
    }

	s1 = argv[2];
	if (s1.empty()) {
		std::cerr << "Error. <string 1> can't be empty" << std::endl;
		return 1;
	}

    FileReplacer replacer(argv[1], argv[2], argv[3]);

    if(replacer.process() == false)
        return 1;
    return 0;
}
