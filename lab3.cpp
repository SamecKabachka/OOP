#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Files;

class Observer
{
public:
    void GetInfo(const Files&);
};

class Files
{
private:
    std::string name;
    int size;
    std::string creationDate;
    int accessCount;

public:

    //----------------designers----------------
    Files() : /*default*/
        size(NULL),
        accessCount(NULL)
    {}
    
    Files(std::string n, int s, std::string cd, int ac) : /*parameters*/
        name(n), 
        size(s), 
        creationDate(cd), 
        accessCount(ac) 
    {}

    /*
    Files(const Files &fl) : /copying/
        name(fl.name),
        size(fl.size),
        creationDate(fl.creationDate),
        accessCount(fl.accessCount)
    {}*/

    friend void Observer::GetInfo(const Files&);

    //----------------functions----------------

      void printFiles() const
        {
          std::cout << "Имя файла: " << name << std::endl;
          std::cout << "Размер: " << size << " байт" << std::endl;
          std::cout << "Дата создания: " << creationDate << std::endl;
          std::cout << "Количество обращений: " << accessCount << std::endl;
          std::cout << std::endl;
        }

        //----------------Gets----------------
        std::string getName() const {return name;}
        int getSize() const {return size;}
        std::string getDate() const {return creationDate;}
        int getCount() const {return accessCount;}

        /*----------------Sets----------------
        void setName(std::string name) {this->name = name;}
        void setSize(int size) {this->size = size;}
        void setDate(std::string date) {this->creationDate = date;}
        void setCount(int count) {this->accessCount = count;}*/
        void operator = (const Files& fl)
        {
            this->name = fl.name;
            this->size = fl.size;
            this->accessCount = fl.accessCount;
            this->creationDate = fl.creationDate;
        }

        bool operator == (const Files& fl)
        {
            return this->name == fl.getName()
                and this->size == fl.getSize()
                and this->creationDate == fl.getDate()
                and this->accessCount == fl.getCount();
        }
       
        bool operator != (const Files& fl)
        {
            return this->name != fl.getName()
                and this->size != fl.getSize()
                and this->creationDate != fl.getDate()
                and this->accessCount != fl.getCount();
        }
};

void Observer::GetInfo(const Files& fl)
{
    std::cout<<"имя файла "<<fl.name<<" размер файла "<<fl.size<<" количество перезаписей "<<fl.accessCount<<" дата создания "<<fl.creationDate;
}

bool compareByName(const Files& file1, const Files& file2)
{
    return file1.getName() < file2.getName();
}


int main()
{
    int n;
    std::cout << "Введите количество файлов: ";
    std::cin >> n;
    std::cin.ignore(); // Игнорировать символ новой строки после ввода числа

    std::vector<Files> files;

    for (int i = 0; i < n; i++)
    {
        std::cout << "Файл " << i + 1 << std::endl;

        std::string name;
        std::cout << "Имя файла: ";
        std::getline(std::cin, name);

        int size;
        std::cout << "Размер: ";
        std::cin >> size;
        std::cin.ignore(); // Игнорировать символ новой строки после ввода числа

        std::string creationDate;
        std::cout << "Дата создания: ";
        std::getline(std::cin, creationDate);

        int accessCount;
        std::cout << "Количество обращений: ";
        std::cin >> accessCount;
        std::cin.ignore(); // Игнорировать символ новой строки после ввода числа

        files.push_back(Files(name, size, creationDate, accessCount));
        std::cout << std::endl;
    }

    // а) список файлов, упорядоченный в алфавитном порядке
    std::cout << "Список файлов, упорядоченный в алфавитном порядке:" << std::endl;
    std::sort(files.begin(), files.end(), compareByName);
    for (const Files& file : files) file.printFiles();
    std::cout << std::endl;

    // б) список файлов, размер которых превышает заданный
    int maxSize;
    std::cout << "Введите максимальный размер файла: ";
    std::cin >> maxSize;
    std::cin.ignore(); // Игнорировать символ новой строки после ввода числа

    std::vector<Files> largeFiles;
    for (const Files& file : files)
    {
        if (file.getSize() > maxSize)
        {
            largeFiles.push_back(file);
        }
    }

    std::cout << "Список файлов, размер которых превышает " << maxSize << " байт:" << std::endl;
    for (const Files& file : largeFiles) file.printFiles();
    std::cout << std::endl;

    // в) список файлов, число обращений к которым превышает заданное
    int minAccessCount;
    std::cout << "Введите минимальное количество обращений к файлу: ";
    std::cin >> minAccessCount;
    std::cin.ignore(); // Игнорировать символ новой строки после ввода числа

    std::vector<Files> frequentlyAccessedFiles;
    for (const Files& file : files)
    {
        if (file.getCount() > minAccessCount)
        {
            frequentlyAccessedFiles.push_back(file);
        }
    }

    std::cout << "Список файлов, количество обращений к которым превышает " << minAccessCount << ":" << std::endl;
    for (const Files& file : frequentlyAccessedFiles) file.printFiles();

    return 0;
}
