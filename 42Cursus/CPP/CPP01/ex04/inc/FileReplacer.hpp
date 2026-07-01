#ifndef FILEREPLACER_HPP
# define FILEREPLACER_HPP

# include <iostream>
# include <string>
# include <cctype>

class FileReplacer {
    private:
        std::string _inFile;
        std::string _outFile;
        std::string _s1;
        std::string _s2;
    
    public:
        FileReplacer(void);
        FileReplacer(const std::string& fileName, const std::string& replaceFrom, const std::string& replaceTo);

        ~FileReplacer(void);

        void setInFile (const std::string& fileName);
        void setOutFile (const std::string& filenName);
        void setS1 (const std::string& str1);
        void setS2 (const std::string str2);

        const std::string& getInFile(void) const;
        const std::string& getOutFile(void) const;
        const std::string& getS1(void) const;
        const std::string& getS2(void) const;

        bool process(void);

};

#endif