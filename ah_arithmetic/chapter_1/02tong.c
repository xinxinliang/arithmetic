#include<stdio.h>
int main()
{
    int book[1001],i,j,t,n;

    //初始化为0
    for (i=0;i<=1000;i++)      //m次
        book[i]=0;

    //输入一个n，表示输入数字的个数
    scanf("%d",&n);
    //输入5个数字
    for(i=1;i<=n;i++)    //n次
    {
        scanf("%d",&t);
        //对应位置加1
        book[t]++;
    }
    //输出结果
    for(i=1000;i>=0;i--)        //m+n次
        for(j=1;j<=book[i];j++)
            printf("%d ",i);

    return 0;

}