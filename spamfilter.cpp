#include "spamfilter.h"
#include <iostream>
#include <string>
#include "word.h"
#include <fstream>
#include <vector>
#include <dirent.h>

using namespace std;


spam_filter::spam_filter()
{
}


    //функция обучения на тестовом не спаме
    void spam_filter::count_test_ham()
    {
        string str;
        ifstream ham_mail("file.txt");  //открывает файл письма
        while (getline(ham_mail, str))  //цикл, берет строку слова и
        {
            for (int i=0; i<=wordlist.size(); ++i)  //цикл проверки на то что слово встречалось раньше и есть в векторе
            {

                if (wordlist[i]->compare_word(str)) //если есть
                {
                    wordlist[i]->common_counter();//то просто увеличивает счетчик
                    i=wordlist.size()+1;         //и выходит из цикла
                }
                else if ( (!wordlist[i]->compare_word(str)) && (i==wordlist.size()) ) //если дошел до конца вектора не найдя совпадений
                {
                    word *w= new word;     //то создает новый класс
                    w->set_word(str);       //записывает новое слово
                    w->common_counter();   // увеличивает счетчик
                    wordlist.push_back(w); //добавляет его в вектор
                }
            }
        }
    }



    //функция обучения на тестовом спаме
    void spam_filter::count_test_spam()
    {
        string str;
        ifstream spam_mail("file.txt"); //открывает файл письма
        while (getline(spam_mail, str)) //цикл, берет строку слова и
        {

            for (int i=0; i<=wordlist.size(); ++i)   //цикл проверки на то что слово встречалось раньше и есть в векторе
            {
                if (wordlist[i]->compare_word(str))   //если есть
                {
                    wordlist[i]->common_counter();    //то просто увеличивает
                    wordlist[i]->in_spam_counter();   //счетчики
                    i=wordlist.size()+1;               //и выходит из цикла
                }
                else if ( (!wordlist[i]->compare_word(str)) && (i==wordlist.size()) )//если дошел до конца вектора не найдя совпадений
                {
                    word *w= new word;        //то создает новый класс
                    w->set_word(str);         //записывает туда новое слово
                    w->common_counter();      //увеличивает
                    w->in_spam_counter();    //  счетчики
                    wordlist.push_back(w); //добавляет его в вектор
                }
            }
        }
    }

    void spam_filter::show_datas()
    {
        for(int i; i<wordlist.size(); ++i) wordlist[i]->show_data();
    }


    double spam_filter::check_mail()
    {
        string str;
        ifstream mail("file.txt"); //открывает файл письма
        vector<string> mw;
        while (getline(mail, str))
        {
            mw.push_back(str);
        }
        double a=1;
        double b=1;
        for (int k=0; k<mw.size(); ++k)
        {
            for (int i=0; i<wordlist.size(); ++i)
            {
                if ( wordlist[i]->compare_word(mw[i]) )
                {
                    a=a*wordlist[i]->give_spamity();
                    b=b*(1-wordlist[i]->give_spamity());
                    i=wordlist.size()+1;
                }
                else if ( (!wordlist[i]->compare_word(mw[i])) && (i==wordlist.size()) )
                {
                    a=a*0.5;
                    b=b*0.5;
                }
            }
        }
        double mail_spamity=a/(a+b);

        for (int k=0; k<mw.size(); ++k)
        {
            for (int i=0; i<wordlist.size(); ++i)
            {
                if ( wordlist[i]->compare_word(mw[i]) )
                {
                    wordlist[i]->common_counter();    //то просто увеличивает
                    if (mail_spamity>0.8) wordlist[i]->in_spam_counter();   //счетчики
                    i=wordlist.size()+1;
                }
                else if ( (!wordlist[i]->compare_word(mw[i])) && (i==wordlist.size()) )//если дошел до конца вектора не найдя совпадений
                {
                    word *w= new word;        //то создает новый класс
                    w->set_word(mw[i]);         //записывает туда новое слово
                    w->common_counter();      //увеличивает
                    if (mail_spamity>0.8) w->in_spam_counter();    //  счетчики
                    wordlist.push_back(w); //добавляет его в вектор
                }
            }

        }
        return mail_spamity;
    }



vector<string> open(string path)
{
    DIR* dir;
    dirent* pdir;
    vector<string> files;
    dir=opendir(path.c_str());
    while (pdir = readdir(dir))
    {
        files.push_back(pdir->d_name);

    }
    return files;
}
