/*************************************************************************
	> File Name: communication.c
	> Author: 
	> Mail: 
	> Created Time: 2014年08月24日 星期日 11时32分04秒
 ************************************************************************/

#include<client.h>


/*接收数据*/
int recv_msg(int sockfd, unsigned char *lo_data)
{
    int state;
    struct XProtocol *msg = (struct XProtocol *)lo_data;
    struct XProtocol buffer;
    bzero(&buffer, sizeof(struct XProtocol));

    /*接收命令*/
    state = recv(sockfd, &buffer, sizeof(struct XProtocol), 0);
    if (state == -1) {
        /*接收出错，返回一条错误消息,这里不能关闭连接*/
        perror("recv");
        send_msg(sockfd, (unsigned char *)&buffer);
        return 1;
    } else if (state == 0){

    }
    
    /*数据解码*/
    strcpy(msg->usrname, buffer.usrname);
    msg->cmd_type = ntohs(buffer.cmd_type);
    msg->state = ntohs(buffer.state);
    msg->data_len = ntohl(buffer.data_len);
    strncpy(msg->data, buffer.data, msg->data_len);

#ifdef _DEBUG
    coutmsg(lo_data);
#endif

    return 0;
}

/*发送数据*/
int send_msg(int sockfd, unsigned char *lo_data)
{
    struct XProtocol *msg = (struct XProtocol *)lo_data;
    struct XProtocol buffer;
    bzero(&buffer, sizeof(struct XProtocol));

    /*数据编码*/
    strcpy(buffer.usrname, msg->usrname);
    buffer.cmd_type = htons(msg->cmd_type);
    buffer.state = htons(msg->state);
    buffer.data_len = htonl(msg->data_len);
    strncpy(buffer.data, msg->data, msg->data_len);

    send(sockfd, (unsigned char *)&buffer, sizeof(struct XProtocol), 0);

#ifdef _DEBUG
    printf("send_msg OK!\n");
#endif
    return 0;
}

