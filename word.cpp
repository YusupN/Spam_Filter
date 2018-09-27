#include "word.h"
#include <iostream>
word::word()
{

}

void word::in_spam_counter()
{
    ++in_spam_count;
}


void word::common_counter()
{
    ++common_count;
}



bool word::compare_word(string s)
{
    if (one_word==s) return true;
            else return false;
}

void word::set_word(string s)
{
    one_word=s;
}


void word::show_data()
{
    cout<<one_word<<common_count<<in_spam_count<<"\n";
}

double word::give_spamity()
{
    return spamity;
}
