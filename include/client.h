#ifndef DICTIONARY_CLIENT_H_
#define DICTIONARY_CLIENT_H_

#include <dictionary.h>
#include <time.h>

//#define _DEBUG

/*服务器地址端口配置*/
#define SERVER_ADDR "192.168.2.78"
#define SERVER_PORT 8888

typedef uint16_t cmd_t;

/*客户端函数标志宏*/
#define FREGISTER   REQ_REGISTER
#define FLOGIN      REQ_LOGIN
#define FSEARCH     REQ_QUERYWORD
#define FLIST_HIS   REQ_HISTORY
#define FQUIT       REQ_EXIT
#define FDIS_HELP   0x0010
#define FDIS_MENUL  0x0011
#define FDIS_MENUS  0x0012
#define FMAX        0x1000

/*服务端未响应，客户端等待时间*/
#define DELAY_TIME 1

/*用户状态*/
enum{
    ONLINE,
    OFFLINE
}ustate;
uint16_t ukey;

/*延迟处理函数*/
void delay_fun(int sign_no);

/*初始化配置*/
int init_config();

/*打印登陆菜单*/
void dis_menul();

/*打印查询菜单*/
void dis_menus();

/*打印帮助*/
void dis_help();

/*获取用户输入命令*/
cmd_t get_cmdl();

/*获取用户输入命令*/
cmd_t get_cmds();

/*选择功能*/
int sec_fun(cmd_t cmd, int sockfd, unsigned char *lo_data);

/*发送数据，数据包由处理函数打包好*/
int send_msg(int sockfd, unsigned char *lo_data);

/*接收数据,解码到本地数据中*/
int recv_msg(int sockfd, unsigned char *lo_data);

/*注册*/
int fregister(int sockfd, unsigned char *lo_data);

/*登陆*/
int flogin(int sockfd, unsigned char *lo_data);

/*查询单词*/
int fsearch(int sockfd, unsigned char *lo_data);

/*查询记录*/
int flist_his(int sockfd, unsigned char *lo_data);

/*退出*/
int quit();

/*打印帮助*/
void dis_help();

#endif /*DICTIONARY_CLIENT_H_*/
