#ifndef SPAM_FILTER_H
#define SPAM_FILTER_H
#include<vector>
#include"word.h"

using namespace std;

class spam_filter
{
private:
    vector<word*> wordlist;  //последовательность классов, внутри которых содержатся 
    //слова-токены и то как часто эти слова встречались в спаме
public:
    spam_filter();
    void count_test_spam(); //функция обучения на тестовом спаме
    void count_test_ham();  //обучение на тестовом не спамовом письме
    double check_mail();      //проверка письма на спамовость
    void show_datas();       //выдать все данные из вектора
    vector<string> open(string path);//получает адрес папки и выдает вектор стрингов с названиями файлов в ней
};

#endif // SPAM_FILTER_H
