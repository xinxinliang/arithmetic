/*fput.c*/
#include<stdio.h>
main()
{
  	 int c;
/* 把fgetc()的结果作为fputc()的输入 */
  	 fputc(fgetc(stdin), stdout);
}
