/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2014年08月25日 星期一 08时04分28秒
 ************************************************************************/

#include<stdio.h>

int main()
{
    int ch, count;
    char passwd[19];
    while (1) {
        count = 0;
        printf("passwd>");
        while ((ch = getchar()) >0){
            if ((ch>='0' && ch<='9') || (ch>='a' && ch<='z') || (ch>='A' && ch<='Z')){
                passwd[count] = ch;
                if (count >16){/*输入字符过长*/
                    printf("\n字符过长!\n");
                    return -1;
                }
                count++;
            } else if(ch == '\n'){/*正常输入结束*/
                if (count<8){/*字符数量不够*/
                    printf("密码太短!\n");
                    return -2;
                } else {/*合法结束*/
                    passwd[count] = '\0';
                    printf("%s", passwd);
                    printf("get passwd OK\n");
                    return 0;
                }
            }else {/*字符不合法异常结束*/
                printf("不合法字符！\n");
                return -3;
            }
        }
    }
    return 0;
}
