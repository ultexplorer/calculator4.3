#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

////////////////////////////////
#define MAXSIZE 100

#define NUMBER '0'
////////////////////////////////
#define MAXBUF 100
char buf[MAXBUF];
int bufp=0;
//////////////functions/////////
int getop(char s[]);
void ungetch(int c);
int getch(void);
////////////////////////////////
#define MAXVAL 100
double val[MAXVAL];
int sp=0;
void push(double f);
double pop(void);

int main()
{
    //int y = getop(s);
    //printf("%d %s\n", y, s);
    char s[MAXSIZE];
    int type;
    double op2;

     while ((type = getop (s)) != EOF) {
        switch (type) {
        case NUMBER:
            push (atof(s));
            break;
        case '+':
            push (pop() + pop());
            break;
        case '*':
            push (pop() * pop());
            break;
        case '-':
            op2 = pop();
            push (pop() - op2);
            break;
        case '%':
           op2 = pop();
           if(op2!=0.0){
               push(fmod(pop(), op2));
           }
           else{
               printf("Error, zero divisor!\n");
           }
           break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push (pop() / op2);
            else
                printf("Error, zero divisor!\n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("Error, unnoun command %s\n", s);
            break;
        }
    }


    return 0;
}

int getop(char s[])
{
    int c,i;
    while((s[0]=c=getch())==' ' || c=='\t');
    s[1]='\0';
    i=0;
    if(!isdigit(c) && c!='.' && c!='-')
    {
        return c; /*не число*/
    }

    if(c=='-'){
        if(isdigit(c=getch()) || c=='.')
        {
           s[++i]=c; //отрицательное число
        }
        else{
           if(c!=EOF) ungetch(c);
           return '-';
        }
    }

    if(isdigit(c))
    {
        while (isdigit((s[++i])=c=getch()));
    }

    if(c=='.')
    {
        while (isdigit((s[++i])=c=getch()));
    }
    s[i]='\0';
    if(c!=EOF){
        ungetch(c);
    }

    return NUMBER;
}

    

void ungetch(int c){
    if(bufp>=MAXBUF){
        printf("Error, bufp is: %d\n", bufp);
    }else{
        buf[bufp++]=c;
    }
}

int getch(void){
    return (bufp>0)? buf[--bufp] : getchar();
}

//////////////////////////////////

void push(double f){
    if(sp<MAXVAL-1){
        val[sp++]=f;
    }
    else{
        printf("Error, steck is full! can't push %g\n", f);
    }
}

double pop(void){
    if(sp>0){
        return val[--sp];
    }else{
        printf("Error, steck is empty!\n");
        return 0.0;
    }
}