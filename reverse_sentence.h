/*
 * I am a student. => student. a am I
 */

char * reverse_sentence(char* s)
{
    if (!s) return NULL;
    char* begin = s;
    char* end = s + strlen(s) - 1;
    reverse(begin, end);
    begin = end = s;
    while (*begin != '\0')
    {
        if (*begin == ' ')
        {
            begin++;
            end++;
            continue;
        }

        if (*end == ' ' || *end == '\0')
        {
            reverse(begin, end-1);
            begin = end;
        }
        else
        {
            end++;
        }
    }
}

//XY => YX
char * left_rotate(char* s, int m)
{
    if (s)
    {
        
    }
}

void reverse(char* begin, char* end)
{
    while (begin < end)
    {
        char c = *begin;
        *begin = *end;
        *end = c;
        begin++;
        end--;
    }
}

