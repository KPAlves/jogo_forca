#include <stdio.h>
#include <string.h>

char secretword[20];
char kicks[26];
int attempts = 0;

void startgame()
{
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void kick()
{
    char usertry;
    scanf(" %c", &usertry);

    kicks[attempts] = usertry;
    attempts++;
}

int wordkicked(char letter)
{
    int found = 0;

    for (int x = 0; x < attempts; x++)
    {
        if (kicks[x] == letter)
        {
            found = 1;
            break;
        }
    }
    return found;
}

void drawforca()
{

    for (unsigned int i = 0; i < strlen(secretword); i++)
    {

        int found = wordkicked(secretword[i]);

        if (found)
        {
            printf("%c ", secretword[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

void choosewordsecret()
{
    sprintf(secretword, "MELANCIA");
}

int main()
{
    int right = 0;
    int hanged = 0;

    choosewordsecret();
    startgame();

    while (!right && !hanged)
    {

        drawforca();
        kick();
    }
}