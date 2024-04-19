#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Files;
//----------------класс аггрегатор----------------
class Aggregator
{       
private:
    std::string name;
    int size;
    std::string creationDate;
    int accessCount;

public:
    Aggregator* next;

    Aggregator ()
    {
        name = "";
        creationDate = "";
        size = NULL;
        accessCount = NULL;
        next = NULL;
    }
     
    Aggregator (std::string n, int s, std::string cd, int ac)  /*с параметрами*/
    {
        this-> name = n; 
        this->size = s;
        this->creationDate = cd; 
        this->accessCount = ac; 
        this->next = NULL;
    }

void GetInfo()
{
    std::cout<<"имя файла "<<name<<" размер файла "<<size<<" количество перезаписей "<<accessCount<<" дата создания "<<creationDate;
}
};

//----------------Класс обсервер----------------
class Observer
{
public:
    void GetInfo(const Files&);
};

//----------------класс файлов----------------

class Files
{
private:
    std::string name;
    int size;
    std::string creationDate;
    int accessCount;
    Aggregator *head; 

public:

    //----------------конструкторы----------------
    
    Files(std::string n, int s, std::string cd, int ac) : /*с параметрами*/
        name(n), 
        size(s), 
        creationDate(cd), 
        accessCount(ac) 
    {}

    friend void Observer::GetInfo(const Files&);//указание что метод гетинфо класса обсервер являеться дружественным

    //----------------функции----------------

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

        //----------------Sets----------------
        void setName(std::string name) {this->name = name;}
        void setSize(int size) {this->size = size;}
        void setDate(std::string date) {this->creationDate = date;}
        void setCount(int count) {this->accessCount = count;}

        //перегрузки операторов ==, != и =
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

        void operator - ()
        {
            Aggregator *tmp;
            tmp = head;
            head = head->next;
            tmp->GetInfo();
        }

        void operator + ()
        {
           Aggregator tmp(name, size, creationDate, accessCount);
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
