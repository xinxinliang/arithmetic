#include<stdio.h>
//队列，使用结构体
struct queue
{
    int data[100];
    int head;
    int tail;
};

int main()
{
    struct queue q;
    int i;
    //初始化队列
    q.head = 1;
    q.tail = 1;
    for(i=1;i<=9;i++)
    {
        //从尾部开始插入
        scanf("%d",&q.data[q.tail]);
        q.tail++;
    }

    q.data[q.tail] = q.data[q.head];
    q.head++;

    while(q.head<=q.tail)
    {
        //打印队列首，并将首出列
        printf("%d ",q.data[q.head]);
        q.head++;
    }
    return 0;
}