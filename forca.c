#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

char secretword[WORD_LENGTH];
char kicks[26];
int attempts = 0;

int kickfails()
{
    int errors = 0;

    for (int i = 0; i < attempts; i++)
    {
        int exist = 0;

        for (unsigned int j = 0; j < strlen(secretword); j++)
        {
            if (kicks[i] == secretword[j])
            {
                exist = 1;
                break;
            }
        }
        if (!exist)
        {
            errors++;
        }
    }

    return (errors);
}

int hanged()
{
    return kickfails() >= 5;
}

int winplayer()
{
    for (unsigned int i = 0; i < strlen(secretword); i++)
    {
        if (!wordkicked(secretword[i]))
        {
            return 0;
        }
    }
    return 1;
}

void startgame()
{
    printf("\n/****************/\n");
    printf("/ Jogo da Forca */\n");
    printf("/****************/\n");
}

void kick()
{
    char usertry;
    printf("Chute uma letra: \n");
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

    int errors = kickfails();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (errors>=1?'(':' '), (errors>=1?'_':' '), (errors>=1?')':' '));
    printf(" |      %c%c%c  \n", (errors>=3?'\\':' '), (errors>=2?'|':' '), (errors>=3?'/': ' '));
    printf(" |       %c     \n", (errors>=2?'|':' '));
    printf(" |      %c %c   \n", (errors>=4?'/':' '), (errors>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    printf("Voce ja chutou %d vezes\n", attempts);

    for (unsigned int i = 0; i < strlen(secretword); i++)
    {
        if (wordkicked(secretword[i]))
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
    FILE* f;

    f = fopen("words.txt","r");
    if(f == 0)
    {
        printf("::ERROR BD::\n\n");
        exit(1);
    }

    int qtdwords;
    fscanf(f,"%d",&qtdwords);

    srand(time(0));
    int randon = rand() % qtdwords;

    for (int i = 0; i < randon; i++)
    {
        fscanf(f,"%s",secretword);
    }

    fclose(f);
}

void addwordsecret() {

    char yes;

    printf("Deseja adicionar uma nova palavra no jogo? (S/N)");
    scanf("%c", &yes);

    if (yes == 'S' || yes == 's')
    {
        char newword[WORD_LENGTH];
        printf("Digite a nova palavra: ");
        scanf("%s", newword);

        FILE* f;

        f = fopen("words.txt", "r+");
        if(f == 0)
        {
            printf("::ERROR BD::\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", newword);

        fclose(f);
    }
}

int main()
{
    startgame();
    choosewordsecret();

    while (!winplayer() && !hanged())
    {
        drawforca();
        kick();
    }

    if (winplayer()) {

    printf("\nParabéns, você ganhou!\n\n");

    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");

    } else {
    printf("\nPuxa, você foi enforcado!\n");
    printf("A palavra era **%s**\n\n", secretword);

    printf("    _______________         \n");
    printf("   /               \\       \n");
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
    }

    addwordsecret();
}
