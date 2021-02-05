#include <stdio.h>
int a[101],n; //定义全局变量，子函数中需要

void quicksort(int left,int right)
{
    int i,j,t,temp;
    if(left>right)
        return;
    
    temp = a[left];
    i=left;
    j=right;
    while(i!=j)
    {
        //顺序很重要，先从左往右找
        while(a[j]>=temp&&i<j)
            j--;
        //再从左往右找
        while(a[i]<=temp && i<j)
            i++;
        //交换两数再数组中的位置
        if(i<j)
        {
            t=a[i];
            a[i]=a[j];
            a[j]=t;
        }
    }
    //最终将基准数归为
    a[left]=a[i];
    a[i]=temp;

    quicksort(left,i-1);
    quicksort(i+1,right);
}

int main()
{
    int i,j,t;
    //读入数据
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);

    quicksort(1,n);//快速排序调用

    //输出排序后的结果
    for(i=1;i<=n;i++)
     printf("%d ",a[i]);
     return 0;

}