//头部 延时 数据 命令 初始 显示 主体

#include <reg51.h>
sbit RS=P3^5;
sbit RW=P3^6;
sbit E=P3^7;
unsigned char str[]={"   WARNING!!!   "};//警告
unsigned char sz[]={"About to explode"};//要爆炸了

void delay(unsigned char w)
{
 unsigned int c=0,f=0;
 for(c=0;c<w;c++)
 {
  for(f=0;f<120;f++);
 }
}

void writedat(unsigned char dat)//写数据   write(写作....)
{
 RS=1;
 RW=0;
 E=0;
 P1=dat;
 //delay(5); 没有这个延时将会同步显示内容
 E=1;
 E=0;
}

void writecom(unsigned char com)//写命令
{
 RS=0;
 RW=0;
 E=0;
 P1=com;
 delay(5);
 E=1;
 E=0;
}

void initlcd()
{
writecom(0x38);//设置16*2的显示，5*7点阵（分辨率），8位数据接口
writecom(0x0c);//设置开显示，不显示光标
writecom(0x06);//写一个字符后地址加1（自动把下一个显示的位向后挪一个）
writecom(0x01);//显示清0，数据指针清0
}

void display()
{
 unsigned int q=0,t=0;//定义
 writecom(0x80);//LCD第一行的起始位置【0x80+0x40是第二行的起始位置】
 while(str[q]!='\0')//当值不等于结束符号（\0）时跳出显示，等于时往下读
 {
  writedat(str[q]);//写入字符串内的值（w）
//  delay(5);		  
  q++;//自加,显示完一个字母后再显示下一个，诺没有自加会一直显示第一个字母
 }
 writecom(0x80+0x40);
 while(sz[t]!='\0')
 {
  writedat(sz[t]);
//  delay(5);
  t++;
 } 
}

void main()
{
 initlcd();
 while(1)
 {
  display();
 }
}