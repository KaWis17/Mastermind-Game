#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>
#include <assert.h>

bool is_similar(int test[], int code[], int on_spot, int off_spot);
void user_input(int* on_spot, int* off_spot, int code[]);


int main()
{
    int code[1296][4];
    bool is_eliminated[1296] = {false};
    int index = 0;
    int number_of_possibilites = 1296;
    int on_spot, off_spot;

    for(int i = 1; i <= 6; i++)
        for(int j = 1; j <= 6; j++)
            for(int k = 1; k <= 6; k++)
                for(int l = 1; l <= 6; l++){
                code[index][0] = i;
                code[index][1] = j;
                code[index][2] = k;
                code[index][3] = l;
                index++;}

    while (number_of_possibilites > 0){
        index = 0;
        while(is_eliminated[index]) index++;  //szukamy pierwszej mozliwoœci która moze byc poprawna

        user_input(&on_spot, &off_spot, code[index]);  //wpisywanie danych od gracza

        if(on_spot == 4){       //warunek wygranej
            printf("I win\n");
            return 0;
        }

        is_eliminated[index] = true;        //usuniecie omawanej permutacji
        number_of_possibilites--;

        for(int i = 0; i < 1296; i++){      //usuniecie niepodobnych permutacji
            if (!is_eliminated[i] && !is_similar(code[i], code[index], on_spot, off_spot)){
                is_eliminated[i] = true;
                number_of_possibilites--;
            }
        }
    }
    printf("You are cheating!\n");
    return 0;
}


bool is_similar(int test[], int code[], int on_spot, int off_spot)
{
    int test_on_spot = 0;
    int test_off_spot = 0;
    bool correct_on_spot[4] = {false};
    bool correct_off_spot[4] = {false};

    for (int i = 0; i < 4; i++){        //sprawdzanie ilosci on_spot
        if (test[i] == code[i]){
            correct_on_spot[i] = true;
            test_on_spot++;
        }
    }
    for (int i = 0; i < 4; i++){           //sprawdzanie ilosci off_spot
        if (correct_on_spot[i])
            continue;
        for (int j = 0; j < 4; j++){
            if (correct_on_spot[j] || correct_off_spot[j])
                continue;
            if (code[i] == test[j]){
                correct_off_spot[j] = true;
                test_off_spot++;

                break;
            }
        }
    }
    return (test_on_spot == on_spot && test_off_spot == off_spot);
}


void user_input(int* on_spot, int* off_spot, int code[])
{
    for(int i=0; i<4; i++) printf("[%d]", code[i]);
    printf("\n\tred: ");
    scanf("%d", on_spot);
    printf("\twhite: ");
    scanf("%d", off_spot);
    assert(*on_spot+*off_spot<=4 && 0<=*on_spot<=4 && 0<= *off_spot<= 4);
}

