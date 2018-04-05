#include <stdio.h>

int scanUnsignedInteger(char** str)
{
    char* tmp = *str;
    while(**str >= '0' && **str <= '9')
    {
        ++(*str);
    }
    //当存在了 0~9 的数字时就返回 1
    //一旦碰到不合法的字符就会跳出循环
    return *str > tmp;
}

int Integer(char** str)
{
    if(str == NULL)
    {//输入非法
        return 0;
    }
    if(**str == '+' || **str == '-')
    {
        ++(*str);
    }
    //目的是使 str 跳过整数部分所有的数字
    return scanUnsignedInteger(str);
}

int IsNumeric(char* str)
{
    if(str == NULL)
    {
        return 0;
    }
    //1.处理整数部分
    int ret = Integer(&str);

    //2.处理小数部分
    if(*str == '.')
    {
        ++str;
        //目的是使 str 跳过小数部分所有的数字
        //这里使用 |= 是因为
        //  a) 小数可以没有整数部分   .5 -> 0.5
        //  b) 小数可以没有小数部分   5. -> 5.0
        //  c) 小数可以前后都有       5.5 
        ret |= scanUnsignedInteger(&str);
    }

    //3.处理指数部分
    if(*str == 'e' || *str == 'E')
    {
        ++str;
        //目的是使 str 跳过小数部分所有的数字
        //这里使用 &= 的原因是
        //  a) 指数e前面必须有数字    如: e1 是错误的写法
        //  b) 指数e后面必须有数字    如: 1e 是错误的写法
        ret &= scanUnsignedInteger(&str);
    }

    //处理不合法的字符 如: a,b,c,*,$,#...
    //  1) *str 不是数字
    //  2) *str 不是 .
    //  3) *str 不是 e 或者 E
    //  4) *str 不是 '\0' ,如果是 '\0' 证明已经查找结束,返回ret就可以了
    //if(!scanUnsignedInteger(&str) && *str != '.' && (*str != 'e' || *str != 'E') && *str != '\0')
    //{
    //    ret = 0;
    //}
    
    //不用做以上判断,如果是可以表示数值的字符串,走到这里 *str 一定已经是 '\0'了
    //如果不是 '\0' 就证明不可以表示数值
    //可能是不满足 整数 小数 指数 任意部分
    //也可能是出现了不合法字符
    if(*str != '\0')
    {
        ret = 0;
    }
    return ret;
}

void Test()
{
    char str[] = "12.34e56";
    int ret = IsNumeric(str);
    printf("ret = %d\n",ret);
}

int main()
{
    Test();
    return 0;
}
