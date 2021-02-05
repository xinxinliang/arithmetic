#include <stdio.h>
#include <string.h>
//解密回文--队列
int main()
{
    char a[101],s[101];
    int i,len,mid,next,top;

    gets(a);
    len = strlen(a);
    mid = len/2 - 1;

    top=0; //栈顶初始化
    
//将mid前的字符依次入栈
    for(i=0;i<=mid;i++)
        s[++top]=a[i];

//判断字符串的长度是奇数还是偶数，找到需要匹配字符串的下标
    if(len%2 == 0)
        next = mid+1;
    else
        next=mid+2;

    //开始匹配
    for(i=next;i<len-1;i++)
    {
        if(a[i]!=s[top])
            break;
        top--;
    }

    //如果top的值为0，则说明都匹配了
    if(top==0)
        printf("YES");
    else
        printf("NO");

    return 0;

}