/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Sat 22 Apr 2017 07:55:42 AM PDT
 ************************************************************************/

#include<stdio.h>
int main()
{

    /*char a= 'a';
    int b = a;
    printf("%d", b);
    
    int c = 97;
    char m = c;
    printf("%c",m);*/

    char a = 'a';
    int *p = (int *)&a;

    printf("%d", *p);

}


