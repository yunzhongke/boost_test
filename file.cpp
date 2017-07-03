/*
 *文件的一些应用
*/

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <string>
#include <boost/filesystem/fstream.hpp>
#include <list>


void boost_file1(const char *str)
{
    boost::filesystem::path *p =new boost::filesystem::path(str);

    if (boost::filesystem::exists(*p)){
        if (boost::filesystem::is_regular_file(*p))
            std::cout << *p << " size is " << boost::filesystem::file_size(*p) << std::endl;

        else if (boost::filesystem::is_directory(*p)){
            for (boost::filesystem::directory_entry &x : boost::filesystem::directory_iterator(*p))
                std::cout << " " << x.path() << '\n';

        }

        else
            std::cout << *p << "exists , but is not a regular file or directory\n";

    }
    else
        std::cout << *p << "does not exist\n";

    delete p;
}

void boost_file2(const char *str)
{
    boost::filesystem::path *p = new boost::filesystem::path(str);

    try{
        if (boost::filesystem::exists(*p)){

            if (boost::filesystem::is_regular_file(*p)){
                std::cout << p << " size is " << boost::filesystem::file_size(*p)\
                       << std::endl;
            }

            else if (boost::filesystem::is_directory(*p)){
                std::cout << *p << " is a directory containning:\n";
                std::vector<std::string> v;
                for (boost::filesystem::directory_entry &x: boost::filesystem::directory_iterator(*p)){
                    v.push_back( x.path().filename().string() );
                }

                std::sort(v.begin() , v.end());

                for (std::vector<std::string>::iterator it= v.begin(); it != v.end(); ++it){
                    std::cout << *it << std::endl;
                }
            }
            else
                std::cout << *p << " exists , but is not a regular file or directory\n";
        }
        else
            std::cout << *p << "does not exist\n";
    }
    catch (const boost::filesystem::filesystem_error &ex){
        std::cout << ex.what() << std::endl;
    }
}

void boost_file3()
{
    std::string *narrow_string = new std::string("smile2");
    std::wstring *wide_string = new std::wstring(L"smile2\u263A");
    std::list<char> *narrow_list = new std::list<char>();

    narrow_list->push_back('s');
    narrow_list->push_back('m');
    narrow_list->push_back('i');
    narrow_list->push_back('l');
    narrow_list->push_back('e');
    narrow_list->push_back('3');

    std::list<wchar_t> *wide_list = new std::list<wchar_t>();
    wide_list->push_back(L's');
    wide_list->push_back(L'm');
    wide_list->push_back(L'i');
    wide_list->push_back(L'l');
    wide_list->push_back(L'e');
    wide_list->push_back(L'3');
    wide_list->push_back(L'\u263A');

    {
        boost::filesystem::ofstream  f("smile");
    }

    {
        boost::filesystem::ofstream f(L"smile\u263A");
    }

    {
        boost::filesystem::ofstream f(*narrow_string);
    }

    {
        boost::filesystem::ofstream f(*wide_string);
    }

    {
        boost::filesystem::ofstream f(*narrow_list);
    }

    {
        boost::filesystem::ofstream f(*wide_list);
    }

    narrow_list->pop_back();
    narrow_list->push_back('4');
    wide_list->pop_back();
    wide_list->pop_back();
    wide_list->push_back(L'4');
    wide_list->push_back(L'\u263A');

    {
        boost::filesystem::ofstream f(boost::filesystem::path(narrow_list->begin() , narrow_list->end()));
    }

    {
        boost::filesystem::ofstream f(boost::filesystem::path(wide_list->begin() , wide_list->end()));
    }

    delete narrow_string;
    delete wide_string;
    delete narrow_list;
}

const char *say_what(bool b){return b ? "true":"false";}

void boost_file4( int *argc ,  char **argv)
{
    boost::filesystem::path *p = new boost::filesystem::path();

    for (; *argc > 1; --(*argc) ,argv++){
        *p /= *(argv + 1);
        std::cout << " ===== " << *(argv + 1) << std::endl;
    }
    std::cout << "composed path:\n";
    std::cout << " operator<<()---: " << *p << "\n";
    std::cout << " make_preferred() ---: " << p->make_preferred() << "\n";


    for (auto element : *p){   // ! path对象的四个成员属性
        std::cout << " " << element << '\n';
    }

    std::cout << "\nbservers , native format:" << std::endl;
#ifdef BOOST_POSIX_API
    std::cout << " native() --------: " << p->native() << std::endl;
    std::cout << " c_str() ---------: " << p->c_str() << std::endl;
#else
    std::wcout << L" native() --------: " << p->native() << std::endl;
    std::wcout << L" c_str() ---------: " << p->c_str() << std::endl;
#endif

    std::cout << " string() ----------: " << p->string() << std::endl;
    std::wcout << L" wstring() -------: " << p->wstring() << std::endl;

    std::cout << "\nobservers, generic format:\n";
    std::cout << " generic_string() --: " << p->generic_string() << std::endl;
    std::wcout << L" generic_string() : " << p->generic_wstring() << std::endl;

    std::cout <<  "\ndecomposition:\n";
    std::cout << " root_name() -------: " << p->root_name() << std::endl;
    std::cout << " root_directory() --: " << p->root_directory() << "\n";
    std::cout << " root_path() -------: " << p->root_path() << "\n";
    std::cout << " relative_path() ---: " << p->relative_path() << "\n";
    std::cout << " parent_path() -----: " << p->parent_path() << "\n";
    std::cout << " filename() --------: " << p->filename() << "\n";
    std::cout << " stem() ------------: " << p->stem() << "\n";
    std::cout << " extension() -------: " << p->extension() << "\n";

    std::cout << "\nquery:\n";
    std::cout << " empty() -----------: " << say_what(p->empty()) << '\n';
    std::cout << " is_absolute() -----: " << say_what(p->is_absolute()) << "\n";
    std::cout << " has_root_name() ---: " << say_what(p->has_root_name()) << "\n";
    std::cout << " has_root_directory():" << say_what(p->has_root_directory()) << "\n";
    std::cout << " has_root_directory():" << say_what(p->has_root_directory()) << "\n";
    std::cout << " has_relative_path(): " << say_what(p->has_relative_path()) << "\n";
    std::cout << " has_filename() ----: " << say_what(p->has_filename()) << "\n";
    std::cout << " has_stem() --------: " << say_what(p->has_stem()) << "\n";
    std::cout << " has_extension() ---: " << say_what(p->has_extension()) << "\n";
    delete p;
}

int mainfile(int argc , char *argv[])
{
    //boost_file1(argv[1]);
    //boost_file2(argv[1]);
    //boost_file3();
    boost_file4(&argc , argv);

    return 0;
}
