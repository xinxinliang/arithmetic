#include<stdio.h>
//队列
int main()
{
    int q[102] = {0,6,1,7,5,8,9,2,4},head,tail;
    int i;
    //初始化队列
    head = 1;
    tail = 10;

    while(head<tail)
    {
        printf("%d",q[head]);
        head++;

        //先将新队列的数据添加到尾部
        q[tail] = q[head];
        tail++;
        //再将队首出队
        head++;
    }
}