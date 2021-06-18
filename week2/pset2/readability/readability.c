#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int lettercount(string);
int wordcount(string);
int sentencecount(string);
int Coleman_Liau(float, float, float);

int main(void)
{
    int nletter, nword, nsentence, index;

    string text = get_string("Text: ");

    nletter = lettercount(text);
    nword = wordcount(text);
    nsentence = sentencecount(text);

    index = Coleman_Liau(nletter, nword, nsentence); ;

    printf("%d letter(s)\n", nletter);
    printf("%d word(s)\n", nword);
    printf("%d sentence(s)\n", nsentence);

    if(index > 16)
        printf("Grade 16+\n");
    else
        printf("Grade %d\n",index);
}

int lettercount(string text)
{
    int n, i;

    n = i = 0;

    while(text[i] != '\0')
        if(isalpha(text[i++]))
            n++;

    return n;
}

int wordcount(string text)
{
    int n, i;
    bool state = false;

    n = i = 0;

    while(text[i] != '\0')
    {
        if(isspace(text[i++]))
            state = false;

        else if(state == false)
        {
            state = true;
            n++;
        }
    }

    return n;
}

int sentencecount(string text)
{
    int n, i;

    n= i = 0;

    while(text[i] != '\0')
    {
        if(text[i] == '.' || text[i] == '?' || text[i] == '!')
            ++n;

        i++;
    }

    return n;
}

//index = 0.0588 * L - 0.296 * S - 15.8
int Coleman_Liau(float l, float w, float s)
{
    float L, S;

    L = l / w * 100;
    S = s / w * 100;

    return round(0.0588 * L - 0.296 * S - 15.8);
}