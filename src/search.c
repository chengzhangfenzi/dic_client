/*************************************************************************
	> File Name: search.c
	> Author: 
	> Mail: 
	> Created Time: 2014年08月24日 星期日 12时15分21秒
 ************************************************************************/

#include<client.h>


/*查询单词*/
int fsearch(int sockfd, unsigned char *lo_data)
{

    struct XProtocol *msg = (struct XProtocol *)lo_data;
    printf("\t想要查什么单词呢？(提示：qqq退出查询状态)\n");
    char words[40];
    while (1) 
	{
        printf(">");
        scanf("%s%*c",words);
        if (strncmp(words, "qqq", 3) == 0) break;

        msg->cmd_type = REQ_QUERYWORD;
        msg->data_len = strlen(words);
        strncpy(msg->data, words, msg->data_len);
        msg->state = ukey;

        send_msg(sockfd, lo_data);
        bzero(msg->data, MAXLEN_DATA);
        recv_msg(sockfd, lo_data);
        if (msg->state == RTL_USEROFFLINE)
		{
            printf(">哎呀，太久没活动被服务器抛弃了，重新登陆一下吧！\n");
            ustate = OFFLINE;
        } else if (msg->state != RTL_SUCCESS)
		{
            printf(">不好意思，没找到你要的单词，我会逐渐学习的。\n");
        } else 
		{
            printf(">%s", msg->data);
        }
    }

    //dis_smenu();

#ifdef _DEBUG
    printf("fsearch\n");
#endif
    return 0;
}
