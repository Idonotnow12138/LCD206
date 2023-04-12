//ͷ�� ��ʱ ���� ���� ��ʼ ��ʾ ����

#include <reg51.h>
sbit RS=P3^5;
sbit RW=P3^6;
sbit E=P3^7;
unsigned char str[]={"   WARNING!!!   "};//����
unsigned char sz[]={"About to explode"};//Ҫ��ը��

void delay(unsigned char w)
{
 unsigned int c=0,f=0;
 for(c=0;c<w;c++)
 {
  for(f=0;f<120;f++);
 }
}

void writedat(unsigned char dat)//д����   write(д��....)
{
 RS=1;
 RW=0;
 E=0;
 P1=dat;
 //delay(5); û�������ʱ����ͬ����ʾ����
 E=1;
 E=0;
}

void writecom(unsigned char com)//д����
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
writecom(0x38);//����16*2����ʾ��5*7���󣨷ֱ��ʣ���8λ���ݽӿ�
writecom(0x0c);//���ÿ���ʾ������ʾ���
writecom(0x06);//дһ���ַ����ַ��1���Զ�����һ����ʾ��λ���Ųһ����
writecom(0x01);//��ʾ��0������ָ����0
}

void display()
{
 unsigned int q=0,t=0;//����
 writecom(0x80);//LCD��һ�е���ʼλ�á�0x80+0x40�ǵڶ��е���ʼλ�á�
 while(str[q]!='\0')//��ֵ�����ڽ������ţ�\0��ʱ������ʾ������ʱ���¶�
 {
  writedat(str[q]);//д���ַ����ڵ�ֵ��w��
//  delay(5);		  
  q++;//�Լ�,��ʾ��һ����ĸ������ʾ��һ����ŵû���Լӻ�һֱ��ʾ��һ����ĸ
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