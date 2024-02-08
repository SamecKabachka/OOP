#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Files
{
public:
    std::string name;
    int size;
    std::string creationDate;
    int accessCount;

    Files(std::string n, int s, std::string cd, int ac)
        : name(n), size(s), creationDate(cd), accessCount(ac) {}
};

bool compareByName(const Files& file1, const Files& file2)
{
    return file1.name < file2.name;
}

void printFiles(const std::vector<Files>& files)
{
    for (const Files& file : files)
    {
        std::cout << "Имя файла: " << file.name << std::endl;
        std::cout << "Размер: " << file.size << " байт" << std::endl;
        std::cout << "Дата создания: " << file.creationDate << std::endl;
        std::cout << "Количество обращений: " << file.accessCount << std::endl;
        std::cout << std::endl;
    }
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
    printFiles(files);
    std::cout << std::endl;

    // б) список файлов, размер которых превышает заданный
    int maxSize;
    std::cout << "Введите максимальный размер файла: ";
    std::cin >> maxSize;
    std::cin.ignore(); // Игнорировать символ новой строки после ввода числа

    std::vector<Files> largeFiles;
    for (const Files& file : files)
    {
        if (file.size > maxSize)
        {
            largeFiles.push_back(file);
        }
    }

    std::cout << "Список файлов, размер которых превышает " << maxSize << " байт:" << std::endl;
    printFiles(largeFiles);
    std::cout << std::endl;

    // в) список файлов, число обращений к которым превышает заданное
    int minAccessCount;
    std::cout << "Введите минимальное количество обращений к файлу: ";
    std::cin >> minAccessCount;
    std::cin.ignore(); // Игнорировать символ новой строки после ввода числа

    std::vector<Files> frequentlyAccessedFiles;
    for (const Files& file : files)
    {
        if (file.accessCount > minAccessCount)
        {
            frequentlyAccessedFiles.push_back(file);
        }
    }

    std::cout << "Список файлов, количество обращений к которым превышает " << minAccessCount << ":" << std::endl;
    printFiles(frequentlyAccessedFiles);

    return 0;
}