#include <stdio.h>
#include <string.h>

void startgame()
{
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void chuta(char kicks[26], int attempts)
{
    char usertry;
    scanf(" %c", &usertry);

    kicks[attempts] = usertry;
}

int main()
{

    char secretword[20];
    sprintf(secretword, "MELANCIA");

    int right = 0;
    int hanged = 0;

    char kicks[26];
    int attempts = 0;

    startgame();

    while (!right && !hanged)
    {
        for (unsigned int i = 0; i < strlen(secretword); i++)
        {

            int found = 0;

            for (int x = 0; x < attempts; x++)
            {
                if (kicks[x] == secretword[i])
                {
                    found = 1;
                    break;
                }
            }

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

        chuta(kicks, attempts);
        attempts++;
    }
}