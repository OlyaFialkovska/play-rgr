#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define highfield 4
#define widthfield 6
int field [highfield][widthfield];

void generation_fox()
{
    srand(time(NULL));
    int eight=0;
    for(int i=0; i<highfield; i++)
        for(int j=0; j<widthfield; j++)
            field[i][j]=0;
    while( eight<8 )
    {
        field [rand()%highfield][rand()%widthfield]+=1;
        eight++;
    }
    for(int i=0; i<highfield; i++)
    {
        for(int j=0; j<widthfield; j++)
            printf("%d\t",field[i][j]);
        printf("\n");
    }
}
void input_coordinates()
{
    int h,w;
    printf("Field %dx%d\n",highfield,widthfield);
    printf("Enter the coordinates of the fox:\n");
    while(1)
    {
        printf("height:\t");
        scanf("%d",&h);
        if(h>=0 && h<highfield)
        {
            break;
        }
        else
        {
            printf("h>=0 && h<%d\n",highfield);
            fflush (stdin);
        }

    }
    //system("cls");
    while(1)
    {
        printf("width:\t");
        scanf("%d",&w);
        if(w>=0 && w<widthfield)
        {
            break;
        }
        else
        {
            printf("w>=0 && && w<%d\n",widthfield);
            fflush (stdin);
        }
    }
    // system("cls");
   // printf("height:\t%d\n",h);
    //printf("width:\t%d\n",w);
    switch( field [h][w] )
    {
    case 0:
        printf("fox not found\n");
        count_foxes(h,w);
        break;
    case 1:
        printf("fox found\n");
        count_foxes(h,w);
        break;
    default:
        printf("%d foxes found\n",field [h][w]);
        count_foxes(h,w);
        break;
    }
}
void count_foxes(int h,int w)
{

    int counter_1=0;
    printf("vertical:\t");
    for(int i=0; i<highfield; i++)
    {
        if(field [i][w]!=0 && i!=h)
            counter_1+=field [i][w];
    }
    printf("%d\n",counter_1);

    int counter_2=0;
    printf("horizontal:\t");
    for(int j=0; j<widthfield; j++)
    {
        if(field [h][j]!=0 && j!=w)
            counter_2+=field [h][j];
    }
    printf("%d\n",counter_2);

    int counter_3=0;
    printf("diagonal:\t");
    for(int i=h-1,j=w-1; i>=0 && j>=0; i--,j--)
        if(field [i][j]!=0 && i!=h && j!=w)
            counter_3+=field [i][i];

    for(int i=h+1,j=w+1; i<highfield && j<widthfield; i++,j++)
        if(field [i][j]!=0 && i!=h && j!=w)
            counter_3+=field [i][i];

//diagonal
    for(int i=h-1,j=w+1; i>=0 && j<widthfield; i--, j++)
        if(field [i][j]!=0)
            counter_3+=field [i][j];


    for(int i=h+1, j=w-1; i<highfield && j>=0; i++,j--)
        if(field [i][j]!=0)
            counter_3+=field [i][j];
    printf("%d\n",counter_3);
}
int main()
{
    generation_fox();
    input_coordinates();

    return 0;
}
