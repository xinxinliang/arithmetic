/* com_host.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "uart_api.h"

int main(void) 
{
	int fds[SEL_FILE_NUM], recv_fd, maxfd;
	char buff[BUFFER_SIZE];
	fd_set inset,tmp_inset;
	struct timeval tv;
	unsigned loop = 1;
	int res, real_read, i;
	/* 将从串口读取的数据写入到这个文件中 */
	if ((recv_fd = open(RECV_FILE_NAME, O_CREAT|O_WRONLY, 0644)) < 0)
	{   
		perror("open");
		return 1;
	}
  	
	fds[0] = STDIN_FILENO; /* 标准输入 */
	if ((fds[1] = open_port(HOST_COM_PORT)) < 0) /* 打开串口 */
	{
		perror("open_port");
		return 1;
	}
	
	if (set_com_config(fds[1], 115200, 8, 'N', 1) < 0) /* 配置串口 */
	{
		perror("set_com_config");
		return 1;
	}

	FD_ZERO(&inset); 
	FD_SET(fds[0], &inset);
	FD_SET(fds[1], &inset);
	maxfd = (fds[0] > fds[1])?fds[0]:fds[1];
	tv.tv_sec = TIME_DELAY;
	tv.tv_usec = 0;
	printf("Input some words(enter 'quit' to exit):\n");
	while (loop && (FD_ISSET(fds[0], &inset) || FD_ISSET(fds[1], &inset)))
	{   
		tmp_inset = inset;
		res = select(maxfd + 1, &tmp_inset, NULL, NULL, &tv);
		switch(res)
		{
			case -1: /* 错误 */
			{
				perror("select");
				loop = 0;
			}
			break;

			case 0: /* 超时 */
			{
				perror("select time out");
				loop = 0;
			}
			break;

			default:
			{
				for (i = 0; i < SEL_FILE_NUM; i++)
				{
					if (FD_ISSET(fds[i], &tmp_inset))
					{
						memset(buff, 0, BUFFER_SIZE);
						/* 读取标准输入或者串口设备文件 */
						real_read = read(fds[i], buff, BUFFER_SIZE);
						if ((real_read < 0) && (errno != EAGAIN))
						{
							loop = 0;
						}
						else if (!real_read)
						{
							close(fds[i]);
                         	FD_CLR(fds[i], &inset);
						}
						else
						{	
							buff[real_read] = '\0';
							if (i == 0)
							{ /* 将从终端读取的数据写入到串口*/
								write(fds[1], buff, strlen(buff));
								printf("Input some words
									(enter 'quit' to exit):\n");
							}
							else if (i == 1)
							{ /* 将从串口读取的数据写入到普通文件中*/
								write(recv_fd, buff, real_read);
							}
							if (strncmp(buff, "quit", 4) == 0)
							{ /* 如果读取为'quit'则退出*/
								loop = 0;
							}							
						}
					} /* end of if FD_ISSET */
				} /* for i */
			} 
		} /* end of switch */
	} /* end of while */
	close(recv_fd);	
  	return 0;
}
