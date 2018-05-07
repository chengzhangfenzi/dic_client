/*************************************************************************
	> File Name: register.c
	> Author: 
	> Mail: 
	> Created Time: 2014年08月24日 星期日 11时33分35秒
 ************************************************************************/

#include<client.h>

/*检测用户名*/
int check_usrname(char *uname)
{
    int ch, count;
    while (1) {
        count = 0;
        printf("username>");
        while ((ch = getchar()) > 0){
#ifdef _DEBUG
            printf("%c",ch);
#endif
            if ((ch>='0' && ch<='9') || (ch>='a' && ch<='z') || (ch>='A' && ch<='Z')){
                uname[count] = ch;
                count++;
                if (count >8){/*输入字符过长*/
                    printf("   error>名字有点长，记不过来啊!\n");
                    while (getchar() != '\n'){
                        continue;
                    }
                    return -1;
                }
            } else if(ch == '\n'){/*正常输入结束*/
                if (count<1){/*字符数量不够*/
                    printf("   error>您的用户名有点短啊!\n");
                    return -2;
                } else {/*合法结束*/
                    uname[count] = '\0';
#ifdef _DEBUG
                    printf("username: %s\n", uname);
#endif
                    return 0;
                }
            }else {/*字符不合法异常结束*/
                printf("   error>亲，有字符我不认识啊！\n");
                while (getchar() != '\n'){
                    continue;
                }
                return -3;
            }
        }
    }
   /*原版
    printf("username>");
    fgets(uname, MAXLEN_USERNAME+1, stdin);
    int i = strlen(uname);
    if (unam[(i-1] == '\n' )
        uname[i-1] = '\0';

    if (i < 1 || i >8){
        printf("error>亲，长度不对啊！\n");
        return -1;
    }
    while (*uname != '\0'){
        if((*uname >= '0' && *uname <= '9') || (*uname >= 'a' && *uname <= 'z') || (*uname >= 'A' && *uname <= 'Z')){
            uname++;
        } else {
            return -1;
        }
    }
    return 0;*/
}

/*检查密码*/
int check_passwd(char *passwd)
{
    int ch, count;
    while (1) {
        count = 0;
        printf("password>");
        while ((ch = getchar()) >0){
#ifdef _DEBUG
            printf("%c",ch);
#endif
            if ((ch>='0' && ch<='9') || (ch>='a' && ch<='z') || (ch>='A' && ch<='Z')){
                passwd[count] = ch;
                count++;
                if (count > 16){/*输入字符过长*/
                    printf("   error>密码有点长，小的记不过来啊!\n");
                    while (getchar() != '\n'){
                        continue;
                    }
                    return -1;
                }
            } else if(ch == '\n'){/*正常输入结束*/
                if (count<8){/*字符数量不够*/
                    printf("   error>为了安全，换个长点的密码吧亲!\n");
                    return -2;
                } else {/*合法结束*/
                    passwd[count] = '\0';
#ifdef _DEBUG
                    printf("get passwd OK\n");
#endif
                    return 0;
                }
            }else {/*字符不合法异常结束*/
                printf("   error>亲，有字符我不认识啊！\n");
                while (getchar() != '\n'){
                    continue;
                }
                return -3;
            }
        }
    }
}

/*注册*/
int fregister(int sockfd, unsigned char *lo_data)
{
    char ch;
    struct XProtocol *msg = (struct XProtocol *)lo_data;
    bzero(msg, sizeof(struct XProtocol));

    printf("\t告诉我你要注册的用户名和密码吧\n");
    printf("\t记得我现在只认识阿拉伯数字和英文字母\n");
    printf("\t最好名字在1~8个字符（⊙ｏ⊙）哦\n");

    while (check_usrname(msg->usrname) != 0)
	{
        continue;
    }

    printf("\t密码８～16位就好啦\n");
    while (check_passwd(msg->data) != 0)
	{
        continue;
    }
    
    msg->cmd_type = REQ_REGISTER;
    msg->data_len = strlen(msg->data);
    //printf("%d\n", msg->data_len);
    //msg->state = 2;

    send_msg(sockfd, (unsigned char *)msg);
    recv_msg(sockfd, (unsigned char *)msg);
    if (msg->state == RTL_SUCCESS)
	{
        printf("\t啊哈，我记住你了，快查单词吧!\n");
        
    } else if (msg->state == RTL_USEREXIST) 
	{
        printf("\t~~(>_<)~~下手晚了，已经被注册拉\n");
    } else 
	{
        printf("\tsome error!\n");
    }
    //dis_lmenu();

#ifdef _DEBUG
    printf("fregister\n");
#endif
    return 0;
}

