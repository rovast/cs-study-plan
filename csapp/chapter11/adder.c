#include "csapp.h"

int main(void)
{
    char *buf, *p;
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE]; // arg1 参数1， arg2 参数2， content 请求的内容
    int n1 = 0, n2 = 0;

    // 从环境变量中读取两个参数，转为整数 n1, n2
    if ((buf = getenv("QUERY_STRING")) != NULL)
    {
        p = strchr(buf, '&'); // 获取到第一个 & 的位置
        *p = '\0';            // 妙啊，这里插入结束符。这样在后面 strcpy(arg1,p) 的时候，就可以直接把第一个参数弄到 arg1 里了
        strcpy(arg1, buf);    // 截取第一个参数
        strcpy(arg2, p + 1);  // 截取第二个参数
        n1 = atoi(arg1);
        n2 = atoi(arg2);
    }

    // 构造返回体 make the response body
    sprintf(content, "QUERY_STRING=%s", buf);
    sprintf(content, "Welcome to add.com: ");
    sprintf(content, "%sThe Internet addition portal.\r\n<p>", content);
    sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>", content, n1, n2, n1 + n2);
    sprintf(content, "%sThanks for visiting!\r\n", content);

    // Generate the HTTP response
    printf("Connection: close\r\n");
    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n");
    printf("%s", content);
    fflush(stdout);

    exit(0);
}
