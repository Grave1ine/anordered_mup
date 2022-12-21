#include <algorithm>//transform
#include <cctype> //tolower
#include <chrono>
#include <string>
#include <iostream>
#include <fstream>//работа с файлом
#include <sstream>//istringstream
#include <unordered_map>

//Vojna_i_mir._Tom_1.txt на русском
//Test_EU.txt            на англ

int main(int argc, char* argv[])                     //для ввода с консоли
{
    auto start = std::chrono::steady_clock::now();

    std::ifstream file ("Test_EU.txt");              //имя файлового вывода (имя файла)
    std::string B;                                   //массив для вывода данных из файла
    std::unordered_map<std::string, int> alphabet;   //<std::string, int>
    if (file.is_open())                              //пока файл открыт...
    {
        while (std::getline(file, B))                //считывать пока не кончится  ifstream_iterator?
        {
            std::transform(B.begin(), B.end(), B.begin(), tolower);//1 итератор на начало, 2 итератор на конец, 3 итератор на позицию, указатель на функцию tolower
                                                                   //перевод в нижний регистр| в начало, в конец, в начало(или в дуругое место) (что нужно сделать)|
            B.erase(std::remove_if(B.begin(), B.end(), ispunct), B.end());//убирает все знаки припинания и прочие символы
            std::istringstream stream(B);            //читает с транзитной строки по словам? std::istringstream название(откуда читать)
            std::string word;
            while (stream >> word) //передача из потока в строку
            {
            ++alphabet[word];      //заполнение мапа
            }
        }
        for (const auto &[key, value]: alphabet)    //лучше передавать по & чтоб не порождать копий
        {
            std::cout << key << ": " << value << "\n";
        }
    }
    file.close();                                    //закрыть файл

    auto finish = std::chrono::steady_clock::now();
    std::cout << "time"<< "\t" << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << "\t" << "ms";
    return 0;
}

