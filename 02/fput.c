/*fput.c*/
#include<stdio.h>
main()
{
  	 int c;
/* ��fgetc()�Ľ����Ϊfputc()������ */
  	 fputc(fgetc(stdin), stdout);
}
