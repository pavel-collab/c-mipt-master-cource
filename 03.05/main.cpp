
#if STATIC_CAST_TEST==1
#include "lib.hpp"
#endif

#if STATIC_CAST_VIRTUAL==1 || DYNAMIC_CAST_EXAMPLE==1 || DYNAMIC_CAST_TEST==1
#include "virtual_lib.hpp"
#endif

#include <iostream>
#include <cassert>

/* 
 * ДЛЯ ПРОВЕРЯЮЩЕГО:
 * так как в теме кастов я разбираюсь плохо, я выписал тут для себя некоторые
 * христоматийные примеры для лучшего понимания. Само решение задачи начинается с 
 * макроса DYNAMIC_CAST_TEST. Но если оставите комментарии и по поводу всего
 * остального -- будет здорово. 
 */

/*
 * When we work with regular parent/chaild classes (with one parent)
 * we can use static_cast without any troubles. We can cast from child to parent (up)
 * and also from parent to child (down). Actually in this case we even don't need a static_cast,
 * cz we can use implicit (child is a parent).
 * 
 * When we have a multiple VIRTUAL parents, we have a problems when we try to case object up from child class
 * to one of the parents. 
 */

/*
 * Little offtop: how the static_cast works. When we derive one object from enother we get a virtual table with
 * pointer to the parent class and pointer to the derived class. And static_cast move this pointer. 
 * 
 * Почему статик каст не работает с виртуальным наследованием: при касте вверх даже при наличии нескольких родительских
 * классов static_cast еще догадывается в каком случае сколько прибавлять к указателю. Но когда мы пытаемся скастовать
 * объект к вышестощему, к которому ведут несколько путей (ромбовидная схема), это уже неподъемно для static_cast.
 */

int main() {

    /*
     * Note: if instead of the pointers we will use actual objects itself
     * and try to check the class fields values, it will work similar.
     */

#if STATIC_CAST_TEST==1
    IOFile* io_file_ptr = new IOFile(5); // d = 5
    std::cout << std::hex << "addres of io_file is " << io_file_ptr;
    std::cout << std::dec << " d = " << io_file_ptr->d << std::endl;

    /* Let's try to static_cast down */
    InputFile* input_file_ptr = static_cast<InputFile*>(io_file_ptr);
    std::cout << std::hex << "addres of input_file is " << input_file_ptr;
    std::cout << std::dec << " b = " << input_file_ptr->b << std::endl; // expected b = 10, cz we cast it from the io file with d = 5

    OutputFile* output_file_ptr = static_cast<OutputFile*>(io_file_ptr);
    std::cout << std::hex << "addres of output_file is " << output_file_ptr;
    std::cout << std::dec << " b = " << output_file_ptr->c << std::endl; // expected b = 15, cz we cast it from the io file with d = 5

    /* Let's try the static_cast up */
    IOFile* new_io_file_ptr_1 = static_cast<IOFile*>(input_file_ptr);
    std::cout << std::hex << "addres of io_file is " << new_io_file_ptr_1;
    std::cout << std::dec << " d = " << new_io_file_ptr_1->d << std::endl; // expected the addres and d similar to the first IOFile

    IOFile* new_io_file_ptr_2 = static_cast<IOFile*>(output_file_ptr);
    std::cout << std::hex << "addres of io_file is " << new_io_file_ptr_2;
    std::cout << std::dec << " d = " << new_io_file_ptr_2->d << std::endl; // expected the addres and d similar to the first IOFile
#endif

#if STATIC_CAST_VIRTUAL==1
    IOFile* io_file_ptr = new IOFile(5);
    InputFile* input_file_ptr = static_cast<InputFile*>(io_file_ptr); // ok
    File* file_ptr = static_cast<File*>(input_file_ptr); // ok

    IOFile* new_io_file = static_cast<IOFile*>(file_ptr); // compilation error (base is virtual)
#endif

    // Parent-Child shceme in our case
    /*
            File
             /\
    InputFile  OutputFile
             \/
           IOFile
    */

   /*
    * dynamic_cast не выдает ошибки на этапе компиляции, потому что на этапе компиляции он не 
    * может распознать динамический тип. Т. о. единственный способ выдавать ошибку -- что-то типо исключений.
    * Но на самом деле dynamic_cast использует возвращаемое значение, если произведено некорректное преобразование
    * типов, dynamic_cast вернет nullptr (это работает в случае указателей, в случае работы с сылками он действительно \
    * кидает exception).
    */

#if DYNAMIC_CAST_EXAMPLE==1
    File* input_file = new InputFile(1);
    File* output_file = new OutputFile(1);
    File* io_file = new IOFile(1);

    DescoverFileType(input_file); // expected InputFile
    DescoverFileType(output_file); // expected OutputFile
    DescoverFileType(io_file); // expected InputFile, OutputFile and IOFile

#endif

    /*
     * Examples of the up-casting, down-casting and cross-casting (side-casting)
     */

#if DYNAMIC_CAST_TEST==1
    IOFile* io_file_ptr = new IOFile(1);

    //! Пример up-cast
    File* file_ptr = static_cast<File*>(io_file_ptr); // законное действие, так как IOFile это и InputFile и OutputFile и File
    //! Пример удачного down-cast (изначальный статический тип *file_ptr -- IOFile, поэтому тут все ок)
    InputFile* input_file_ptr = dynamic_cast<InputFile*>(file_ptr); // ok
    assert(input_file_ptr != nullptr);
    OutputFile* output_file_ptr = dynamic_cast<OutputFile*>(file_ptr); //ok
    assert(output_file_ptr != nullptr);
    io_file_ptr = dynamic_cast<IOFile*>(file_ptr); // ok
    assert(io_file_ptr != nullptr);

    //! Пример удачного side-cast (опять же, указатель output_file_ptr изначально указывает на объект класса, который наъодится ниже по инрархии наследования)
    InputFile* new_input_file_ptr = dynamic_cast<InputFile*>(output_file_ptr); // даже это законно

    //! Пример неудачного side-cast (не понятно, по каким отношениям мы должны перейти от одного класса к другому)
    input_file_ptr = new InputFile(1);
    output_file_ptr = dynamic_cast<OutputFile*>(input_file_ptr);
    assert(output_file_ptr == nullptr);

    //! Пример неудачного down-cast (опять же, непонятно по какому пути переходить)
    file_ptr = new File(1);
    io_file_ptr = dynamic_cast<IOFile*>(file_ptr);
    assert(io_file_ptr == nullptr);

#endif

    return 0;
}