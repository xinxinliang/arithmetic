#include<stdio.h>
//冒泡排序

struct student
{
    char name[21];
    int score;
};

int main()
{
    struct student a[100],temp;
    int n,i,j;
    scanf("%d",&n);

    for(i=0;i<n;i++)
        scanf("%s %d",a[i].name,&a[i].score);
    
    for(i = 0;i<n;i++)
        for(j = 0;j<n-1;j++)
        {
            
            if(a[j].score>a[j+1].score)
            {
                temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
            }
        }

    for(i = 0;i<n;i++)
        printf("%s\n ",a[i].name);
    return 0;
}