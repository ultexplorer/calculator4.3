#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//////////////////////////////////
#define MAXOP 100
#define NUMBER '0'


//////////////////////////////////
int getop(char s[]);
int getch(void);
void ungetch(int);
//////////////////////////////////
void push(double);
double pop(void);

int main()
{
    int type;
    double op2;
    char s[MAXOP];
    
    while((type=getop(s))!=EOF){
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop()+pop());
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("Error, неивестная команда %s\n", s);
            break;
        }
    }
    
    return 0;
}

///////////////////////////////////////
int getop(char s[]){
    int i, c;
    while((s[0]=c=getch())==' ' && c=='\t');
    s[1]='\0';
    i=0;
    if(!isdigit(c) && c!='.' && c!='-'){
        return c;
    }
    
    if(c=='-'){
        if(isdigit(c=getch()) || c=='.'){
            s[++i]=c;
        }else{
            if(c!=EOF){
                ungetch(c);
            }
            return '-';
        }
    }
    if(isdigit(c)){
        while(isdigit(s[++i]=c=getch()));       
    }
    if(c=='.'){
        while(isdigit(s[++i]=c=getch()));
    }
    s[i]='\0';
    if(c!=EOF){
        ungetch(c);
    }
    return NUMBER;
}




////////////////////////////////////////
#define MAXBUF 100

char buf[MAXBUF];
int bufp = 0;

int getch(void){
    return (bufp>0)? buf[--bufp] : getchar();
}

void ungetch(int c){
    if(bufp>MAXBUF){
        printf("Error, too many characters (buf is full)!\n");
    }else{
        buf[bufp++]=c;
    }
}

////////////////////////////////////

#define MAXVAL 100
double val[MAXVAL];
int sp = 0;

void push(double f){
    if(sp>MAXVAL){
        printf("Error, stack is full, can't push %.8g\n", f);
    }else{
        val[sp++]=f;
    }
}

double pop(void){
    if(sp>0){
        return val[--sp];
    }else{
        printf("Error, stack is empty!\n");
    }
}