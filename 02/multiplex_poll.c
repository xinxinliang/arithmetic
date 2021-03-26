/* multiplex_poll.c */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <poll.h>
#define MAX_BUFFER_SIZE		1024	/* ��������С */
#define IN_FILES			3		/* ��·���������ļ���Ŀ */
#define TIME_DELAY			60000	/* ��ʱʱ������:60�� */
#define MAX(a, b)		((a > b) ? (a) : (b))

int main(void)
{
	struct pollfd fds[IN_FILES];
	char buf[MAX_BUFFER_SIZE];
	int i, res, real_read, maxfd;
	
	/*���Ȱ�һ����Ȩ�޴�����Դ�ļ�*/
	fds[0].fd = 0;
	if((fds[1].fd = open ("in1", O_RDONLY|O_NONBLOCK)) < 0)
	{
		printf("Open in1 error\n");
		return 1;
	}  		    
 	if((fds[2].fd = open ("in2", O_RDONLY|O_NONBLOCK)) < 0)
 	{
 		printf("Open in2 error\n");
		return 1;
	}
	/*ȡ�������ļ��������еĽϴ���*/
  	for (i = 0; i < IN_FILES; i++)
  	{
  		fds[i].events = POLLIN;
  	}
  	
  	/* ѭ�������Ƿ�������ڼ������ļ������� */
  	while(fds[0].events || fds[1].events || fds[2].events)
  	{
		if (poll(fds, IN_FILES, 0) < 0) 
		{
			printf("Poll error or Time out\n");
			return 1;
		}		
		for (i = 0; i< IN_FILES; i++)
		{
			if (fds[i].revents) /* �ж����ĸ��ļ��Ϸ������¼�*/
			{
				memset(buf, 0, MAX_BUFFER_SIZE);
				real_read = read(fds[i].fd, buf, MAX_BUFFER_SIZE);
				if (real_read < 0)
				{
					if (errno != EAGAIN)
					{
						return 1; /* ϵͳ���󣬽�������*/
					}
				}
				else if (!real_read)
				{
					close(fds[i].fd);
					fds[i].events = 0; /* ȡ���Ը��ļ��ļ��� */
				}
				else
				{
					if (i == 0) /* ����ڱ�׼����������������ʱ */
					{
						if ((buf[0] == 'q') || (buf[0] == 'Q'))
						{
							return 1; /*����"q"��"Q"����˳�*/
						}
					}
					else
					{ /* ����ȡ���������ǵ��ն��� */
						buf[real_read] = '\0';
						printf("%s", buf);
					}
				} /* end of if real_read*/
			} /* end of if revents */
		} /* end of for */
  	} /*end of while */
  	exit(0);
}
