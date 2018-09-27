#ifndef WORD_H
#define WORD_H
#include <string>
using namespace std;


class word
{
private:
    string one_word;   //содержит слово/последовательность символов
    double spamity;
    int common_count=0;  //счетчик - как часто это слово встречается во всех письмах, влючая спам
    int in_spam_count=0;  //счетчик в спаме - как часто это слово встречается в спаме
public:
    word();
    void in_spam_counter();  //инкремент счетчика в спаме
    void common_counter();    //инкремент общего счетчика
    bool compare_word(string s);  //сравнивает слово с другой строкой
    void set_word(string s);   //положить в класс строку
    void show_data();
    double give_spamity();

};

#endif // WORD_H
