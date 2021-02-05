#include<stdio.h>
//冒泡排序
int main()
{
    int a[100],n,i,j,temp;
    scanf("%d",&n);

    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    
    for(i = 0;i<n;i++)
        for(j = 0;j<n-1;j++)
        {
            
            if(a[j]>a[j+1])
            {
                temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
            }
        }

    for(i = 0;i<n;i++)
        printf("%d ",a[i]);
    return 0;
}