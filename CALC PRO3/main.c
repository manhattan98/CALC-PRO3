//
//  CALC.c
//  CALC PRO3
//
//  Created by Еремей Шумченко on 29.04.15.
//  Copyright (c) 2015 Еремей Шумченко. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long i,p; // глобальный счетчик
// функции
unsigned long numlen(float mas[]){ // numlen() - фактическая длина массива float ...[]
    unsigned long nfact=0;
    i=0;
    while (mas[i] !=0){
        ++nfact;
        ++i;
    }
    return nfact;
}
float sumT(float mas[]){ // sumT() - сумма элементов массива (автоматическое вычисление размерности массива)
    unsigned long nfact=numlen(mas);
    float s=0;
    for (i=0; i<nfact; i++) s+=mas[i];
    return s;
}
float medART(float mas[]){ // medART() - среднее арифметическое элементов массива (автоматическое вычисление размерности массива)
    unsigned long nfact=numlen(mas);
    float s=0;
    for (i=0; i<nfact; i++) s+=mas[i];
    return s/nfact;
}
float multT(float mas[]){ // multT() - произведение элементов массива (автоматическое вычисление размерности массива)
    unsigned long nfact=numlen(mas);
    float m=1;
    for (i=0; i<nfact; i++) if (mas[i] !=0) m*=mas[i];
    return m;
}

// ф-ция main()
int main(int argc, const char * argv[]) {
    unsigned long debug=0;
    char answer = '\0'; // управление программой
    unsigned long n,nfact;
    n=4096; // кол-во элементов массивов
    float result = 0.0;
    float obj[n];
    char symb[n];
    char sign[n];
    
    printf("Решение математических выражений со знаками + - * /\n");
    // тело программы
    do{
        fpurge(stdin); // очистка потока stdin
        
        // обнуление переменных и массивов
        nfact=0;
        result = 0.0;
        answer = '\0';
        for (i=0; i<n; i++) obj[i]=0.0; // обнуление массива obj[]
        for (i=0; i<n; i++) symb[i]='\0'; // обнуление массива symb[]
        for (i=0; i<n; i++) sign[i]='\0'; // обнуление массива sign[]
        
        printf("Ввод: ");
        i=0; // обнуление счетчика
        // ввод элементов символьного массива symb[]
        do{
            scanf("%c",&symb[i]);
            if (((symb[i] !='0')&&(symb[i] !='1')&&(symb[i] !='2')&&(symb[i] !='3')&&(symb[i] !='4')&&(symb[i] !='5')&&(symb[i] !='6')&&(symb[i] !='7')&&(symb[i] !='8')&&(symb[i] !='9')&&(symb[i] !='+')&&(symb[i] !='-')&&(symb[i] !='*')&&(symb[i] !='/')&&(symb[i] !='(')&&(symb[i] !=')')&&(symb[i] !='.')&&(symb[i] !=' ')&&(symb[i] !='\n'))||(symb[0]=='\n')) answer='y';
            if (symb[0]=='-'){
                if (symb[1]=='d'){ // debug enable
                    if (debug==0) printf("DEBUG MODE\n");
                    debug=1;
                    answer='y';
                }
            }
            i++;
        } while (symb[i-1] !='\n');
        
        // конвертирование char->int копирование массива symb[] в obj[]
        obj[0]=1;
        p=0;
        unsigned long l=0; // дополнительный счетчик
        for (i=0; i<n; i++){
            if ((symb[i]!='0')&&(atoi(&symb[i])==0)) i++;
            obj[p]=atof(&symb[i]);
            if ((i>0)&&(symb[i-1]=='-')) obj[p]=-1*obj[p];
            if ((i>0)&&(symb[i-1]=='/')) obj[p]=1.0/obj[p];
            for(l=0; l<5; l++) if ((symb[i+1] !='+')&&(symb[i+1] !='-')&&(symb[i+1] !='*')&&(symb[i+1] !='/')&&(symb[i+1] !=' ')) i++;
            p++;
        }
        nfact=numlen(obj); // фактическое кол-во элементов массива obj[]
        p=0;
        // распознавание знаков, заполнение массива sign[]
        for (i=0; i<n; i++){
            if ((i==0)&&(symb[0]!='-')&&(symb[0]!='+')){
                sign[p]='+';
                p++;
            }
            if ((symb[i]=='+')||(symb[i]=='-')){
                sign[p]='+';
                p++;
            }
            if ((symb[i]=='*')||(symb[i]=='/')){
                sign[p]='*';
                p++;
            }
        }
        
        // вычисления в соответствии с массивами obj[] и sign[]
        float umn=1, sumUM=0;
        for (i=0; i<nfact; i++){ // умножение чисел > или < 0 (дроби)
            if (sign[i+1]=='*') umn*=obj[i];
            if ((i>0)&&(sign[i+1]!='*')&&(sign[i]=='*')){
                umn*=obj[i];
                sumUM+=umn;
                umn=1;
            }
        }
        float plus=0;
        for (i=0; i<nfact; i++){ // сложение чисел со знаком + или -
            if ((sign[i+1]=='+')&&(sign[i]=='*')) i++;
            if (sign[i+1]=='+') plus+=obj[i];
            if ((i==nfact-1)&&(sign[i]=='+')) plus+=obj[i];
        }
        result=sumUM+plus; // результат
        if ((answer !='y')&&(result !=0)&&(sign[1] !='\0')) printf("= %g",result); // вывод результата
        
        // debug
        if ((debug==1)&&(obj[0]!='\0')){
            if ((answer !='y')&&(result !=0)&&(sign[1] !='\0')) printf("\n");
            printf("symb[]: ");
            for (i=0; i<n; i++){ // вывод массива symb[]
                if ((symb[i] !='\0')&&(symb[i] !='\n')){
                    if (symb[i] !=' ') printf("[%ld]=%c; ",i,symb[i]);
                    else printf("[%ld]=_; ",i);
                }
            }
            printf("\nobj[]: ");
            for (i=0; i<n; i++) if (obj[i] !=0) printf("[%ld]=%g; ",i,obj[i]); // вывод массива obj[]
            printf("\nsign[]: ");
            for (i=0; i<n; i++) if (sign[i] !='\0') printf("[%ld]=%c; ",i,sign[i]); // вывод массива sign[]
            printf("\nnfact=%ld",nfact);
            if ((answer !='y')&&(sign[1] =='\0')) printf("\n");
        }
        
        // обработка элементов массива obj[] вывод и управление программой
        if ((answer !='y')&&(sign[1] =='\0')){
            printf("Операции: 1 - СУММА; 2 - ПРОИЗВЕДЕНИЕ; 3 - СР. АРИФМЕТИЧЕСКОЕ\n");
            do{
                fpurge(stdin);
                printf("Нажмите цифру(1 - 3): ");
                scanf("%c",&answer);
            } while ((answer !='1')&&(answer !='2')&&(answer !='3'));
            if (atoi(&answer)==1) printf("СУММА: %g",sumT(obj));
            if (atoi(&answer)==2) printf("ПРОИЗВЕДЕНИЕ: %g",multT(obj));
            if (atoi(&answer)==3) printf("СР. АРИФМЕТИЧЕСКОЕ: %g",medART(obj));
        }
        if (answer !='y'){
            printf("\n");
            do{
                fpurge(stdin);
                printf("Продолжить?(y/n) ");
                scanf("%c",&answer);
            }while ((answer !='y')&&(answer !='n'));
        }
    } while(answer=='y');
    printf("Выход...\n");
    return 0;
}