#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct no
{
    int h;
    struct no *p;
    int doente;
    int x;
    int y;
} no;

no *criaconj(uint32_t x, uint32_t y)
{
    no *pessoa = (no *)malloc(sizeof(no));
    pessoa->p = pessoa;
    pessoa->h = 0;
    pessoa->doente = 0;
    pessoa->x = x;
    pessoa->y = y;
    return pessoa;
}

uint32_t myrand()
{
    static uint32_t next = 1;
    next = next * 1103515245 + 12345;
    return next;
}

int main(int argc, char *argv[])
{
    uint32_t range = 0, altura = 0, largura = 0, x = 0, y = 0;

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    fscanf(input, "%i", &range);

    for (int i = 0; i < range; i++)
    {
        fscanf(input, "%i %i %i %i", &altura, &largura, &x, &y);
        fprintf(output, "%i:(%i,%i);", i + 1, x, y);

        uint32_t gx = x;
        uint32_t gy = y;

        no ***local = (no ***)malloc(altura * sizeof(no **));

        for (int z = 0; z < altura; z++)
        {
            local[z] = (no **)malloc(largura * sizeof(no *));
            for (int x = 0; x < largura; x++)
            {
                local[z][x] = (no *)malloc(sizeof(no));
                local[z][x] = criaconj(z, x);
            }
        }
        local[x][y]->doente = 1;
        for (int z = 1; z < (altura * largura); z++)
        {
            for (;;)
            {
                x = gx + (-1 + myrand() % 3);
                while (x >= altura)
                {
                    x = gx + (-1 + myrand() % 3);
                }
                y = gy + (-1 + myrand() % 3);
                while (y >= largura)
                {
                    y = gy + (-1 + myrand() % 3);
                }
                if (local[x][y]->doente == 0)
                {
                    gx = x;
                    gy = y;
                    break;
                }
                else if (local[x][y]->doente == 1)
                {
                    gx = x;
                    gy = y;
                }
            }
            local[x][y]->doente = 1;
            if (z == largura * altura - 1)
            {
                fprintf(output, "(%i,%i)", local[x][y]->x, local[x][y]->y);
            }
            else
            {
                fprintf(output, "(%i,%i);", local[x][y]->x, local[x][y]->y);
            }
        }
        fprintf(output, "\n");
    }

    fclose(input);
    fclose(output);

    return 0;
}