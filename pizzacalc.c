#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PI 3.14159265358979323846

struct pizzaList{
    char name[64];
    float ppd;
    struct pizzaList* next;
};

void sortPizza(struct pizzaList* headPizza, int pizzaCount);

int main(int argc, char* argv[]){

    FILE* file;
    file = fopen(argv[1],"r");
    char textline[64];
    int pizzaCount = 0;
    struct pizzaList* headPizza = NULL;
    struct pizzaList* tailPizza = NULL;
    
    while(1){    

        if(file == NULL){
            printf("NO FILE INPUT\n");
            break;
        }

        fscanf(file, "%s", textline);

        if(strcmp(textline, "DONE") == 0){
            printf("isDONE\n");
            break;
        }

        if(strcmp(textline, "") == 0){
            printf("PIZZA FILE IS EMPTY\n");
            break;
        }

        struct pizzaList* nextPizza = (struct pizzaList* ) malloc(sizeof(struct pizzaList));
        
        strcpy(nextPizza->name, textline);
        fscanf(file, "%s", textline);
        float diameter = atof(textline);
        fscanf(file, "%s", textline);
        float price = atof(textline);

        if(price != 0){
            nextPizza->ppd = (PI*pow(diameter,2.0))/(4.0*price);
        }else{
            nextPizza->ppd = 0;
        }
        nextPizza->next = NULL;
        pizzaCount++;

        if(pizzaCount == 1){
            headPizza = nextPizza;
            tailPizza = nextPizza;
        }
        else{
            tailPizza->next = nextPizza;
            tailPizza = nextPizza;
        }

    }

    fclose(file);

    sortPizza(headPizza, pizzaCount);

    struct pizzaList* temp = headPizza;

    while(temp != NULL){

        printf("%s ", temp->name);
        printf("%f\n", temp->ppd);
        headPizza = temp;
        temp = temp->next;
        free(headPizza);

    }

    return 0;
}

void sortPizza(struct pizzaList* headPizza, int pizzaCount){
    for (int i = 0; i < pizzaCount; i++){

        struct pizzaList* temp = headPizza;
        
        while(temp->next != NULL){   

            if(temp->ppd < temp->next->ppd){
                char temp_name[64];
                strcpy(temp_name, temp->name);
                strcpy(temp->name, temp->next->name);
                strcpy(temp->next->name, temp_name);
                float temp_ppd = temp->ppd;
                temp->ppd = temp->next->ppd;
                temp->next->ppd = temp_ppd;
            }

            else if(temp->ppd == temp->next->ppd){
                if(strcmp(temp->name, temp->next->name) > 0){
                    char temp_name[64];
                    strcpy(temp_name, temp->name);
                    strcpy(temp->name, temp->next->name);
                    strcpy(temp->next->name, temp_name);
                }
            }
            temp = temp->next;
        }
    }
}
