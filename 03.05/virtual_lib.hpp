#ifndef VIRTUAL_LIB_h
#define VIRTUAL_LIB_h

#include <iostream>

struct File {
    int a;
    File(int a) : a{a} {}
    virtual ~File() {}
};

struct InputFile : public virtual File 
{
    int b;
    InputFile(int b) : File(b*2), b{b} {}
    virtual ~InputFile() {}
};

struct OutputFile : public virtual File
{
    int c;
    OutputFile(int c) : File(c*3), c{c} {}
    virtual ~OutputFile() {}
};

struct IOFile : public InputFile, public OutputFile{
    int d;
    IOFile(int d) : File(d), InputFile(d * 5), OutputFile(d *7) {}
};

// little simple example of using dynamic_cast 
void DescoverFileType(File* file) {
    if (dynamic_cast<InputFile*>(file)) {
        std::cout << "InputFile" << std::endl;
    }

    if (dynamic_cast<OutputFile*>(file)) {
        std::cout << "OutputFile" << std::endl;
    }

    if (dynamic_cast<IOFile*>(file)) {
        std::cout << "IOFile" << std::endl;
    }
}

#endif //VIRTUAL_LIB_h