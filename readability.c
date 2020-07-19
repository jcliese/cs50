#include <stdio.h>
#include <cs50.h>
#include <math.h>

int count_letters(string);
int count_words(string str);
int count_sentences(string str);
int get_index(int letters, int words, int sentences);

int main(void)
{
    string str = get_string("Text:\n");
    printf("%s\n", str);
    int letters = count_letters(str);
    int words = count_words(str);
    int sentences = count_sentences(str);
    int index = get_index(letters, words, sentences);
    if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string str)
{
    int letters = 0;
    int i = 0;
    while(str[i]!='\0')
    {
        if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z'))
        {
            letters++;
        }
        i++;
    }
    return letters;
}

int count_words(string str)
{
    int words = 1;
    int i = 0;
    while(str[i]!='\0')
    {
        if(str[i]==' ' )
        {
            words++;
        }
        i++;
    }
    return words;
}

int count_sentences(string str)
{
    int sentences = 0;
    int i = 0;
    while(str[i]!='\0')
    {
        if(str[i]=='.' || str[i]=='!' || str[i]=='?' )
        {
            sentences++;
        }
        i++;
    }
    return sentences;
}

int get_index(int let, int wrds, int sent)
{
    double index, letters, sentences, words = 0;
    words = wrds;
    double multiple = (100 / words);
    letters = let * multiple;
    sentences = sent * multiple;
    index = 0.0588 * letters - 0.296 * sentences - 15.8;
    index = round(index);
    return index;
}