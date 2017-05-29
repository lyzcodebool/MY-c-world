/*************************************************************************
	> File Name: getstr.h
	> Author: 
	> Mail: 
	> Created Time: Sat 20 May 2017 03:40:04 PM PDT
 ************************************************************************/

#ifndef _GETSTR_H
#define _GETSTR_H
 char *getstr(char s[])
  { int i;
    for(i=0;s[i]!='+';i++)
    s[i]=getchar();
    return s;
 }
#endif
