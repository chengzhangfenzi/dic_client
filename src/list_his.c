/*************************************************************************
	> File Name: list_his.c
	> Author: 
	> Mail: 
	> Created Time: 2014年08月24日 星期日 12时17分39秒
 ************************************************************************/

#include<client.h>


/*查询记录*/
int flist_his(int sockfd, unsigned char *lo_data)
{
    int count = 0;
    struct XProtocol *msg = (struct XProtocol *)lo_data;

    msg->cmd_type = REQ_HISTORY;
    msg->state = ukey;
    msg->data_len = 0;
    memset(msg->data, 0x00, MAXLEN_DATA);
    send_msg(sockfd, lo_data);
    recv_msg(sockfd, lo_data);

    if (msg->state == RTL_USEROFFLINE){
        printf(">哎呀，太久没活动服务器不认识了，重新登陆一下吧！\n");
        ustate = OFFLINE;
        return 0;
    }
    while (msg->data_len > 0){
        if (count % 10 == 0){
            printf("\t-----------------------------\n");
        }
        count++;
        printf(">%-4d%s\n",count, msg->data);
        memset(msg->data, 0x00, MAXLEN_DATA);
        recv_msg(sockfd, lo_data);
    }
    
#ifdef _DEBUG
    printf("flist_his\n");
#endif
    return 0;
}
