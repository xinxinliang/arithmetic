#include<stdio.h>
//桶排序
int main()
{
    int a[11],i,j,t;

    //初始化为0
    for (i=0;i<=10;i++)
        a[i]=0;
    //输入5个数字
    for(i=1;i<=5;i++)
    {
        scanf("%d",&t);
        //对应位置加1
        a[t]++;
    }
    //输出结果
    for(i=0;i<=10;i++)
        for(j=1;j<=a[i];j++)
            printf("%d ",i);

    return 0;

}