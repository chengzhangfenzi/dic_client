/*************************************************************************
	> File Name: login.c
	> Author: 
	> Mail: 
	> Created Time: 2014年08月24日 星期日 12时11分09秒
 ************************************************************************/

#include<client.h>


/*登陆*/
int flogin(int sockfd, unsigned char *lo_data)
{
    struct XProtocol *msg = (struct XProtocol*)lo_data;
    bzero(msg, sizeof(struct XProtocol));

    printf("\t很高兴又见到你了O(∩_∩)O！\n");
    printf("username>:");
    fgets(msg->usrname, MAXLEN_USERNAME+1, stdin);
    if (msg->usrname[strlen(msg->usrname)-1] == '\n' )
        msg->usrname[strlen(msg->usrname)-1] = '\0';
    //check_usrname(msg->usrname);

    printf("password>:");
    fgets(msg->data, MAXLEN_DATA, stdin);
        msg->data[strlen(msg->data)-1] = '\0';
    msg->data_len = strlen(msg->data);
    
    msg->cmd_type = REQ_LOGIN;
    msg->state = ukey;

    send_msg(sockfd, lo_data);
    recv_msg(sockfd, lo_data);
    if (msg->state == RTL_SUCCESS){
        /*如果返回用户验证通过，进入查询阶段*/
        ustate = ONLINE;
        fsearch(sockfd, lo_data);
    } else if (msg->state == RTL_NUSEREXIST){
        printf("\t亲，木有这个用户哦，要不你注册一下?\n");
    } else if (msg->state == RTL_WRONGPASSWD){
        printf("\t咕～～（╯﹏╰）ｂ，密码不对啊。。\n");
    } else if (msg->state == RTL_USERONLINE){
        printf("\t咕～～（╯﹏╰）ｂ，您不是已经登陆了吗？。。\n");
    } else {
        printf("\t惨了我的小服务器挂了>_<..\n");
    }

#ifdef _DEBUG
    printf("flogin\n");
#endif
    return 0;
}

