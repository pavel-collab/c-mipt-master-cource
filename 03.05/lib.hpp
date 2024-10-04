#ifndef LIB_h
#define LIB_h

struct Filler {  // нужен, чтобы указатель на дочерний класс (в нашем случае IOFile) не совпадал ни с одним указателем на прямых родителей в виртуальной таблице
    int x, y;
    virtual void filler() = 0; 
    virtual ~Filler() {}
};

struct InputFile{
    int b;
    InputFile(int b) : b{b} {}
    virtual ~InputFile() {}
};

struct OutputFile{
    int c;
    OutputFile(int c) : c{c} {}
    virtual ~OutputFile() {}
};

struct IOFile : public Filler, public InputFile, public OutputFile{
    int d;
    void filler() override {}
    IOFile(int d) : InputFile(d * 2), OutputFile(d *3), d{d} {}
};

#endif //LIB_h