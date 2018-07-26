#include "LPC17xx.h"//����LPCͷ�ļ�
//���Ǹ�������������Ϥ������ʹ�ã�ͨ������ѡ��Ĵ���PINSEL1����������Ź��ܡ�
//Ԥ�������
uint32_t BEEP = (1<<26);//��λ����26λ����λλp0.26
//�������
uint32_t systick = 0;//ϵͳʱ�ӱ仯
uint32_t delay1S = 0;//�ӳ�1���־

//�����ӳٺ������ӳٺ���û�е��ã�ͨ��Tick��ʽʵ���ӳ�									  l
void delay(uint32_t ultime){
	ultime*= 5000;
	while(ultime--);
}
//ѡ�����ű�����Ϊ�������GPIO
void GPIOInit(){
	LPC_PINCON->PINSEL1 &= ~(0x3<<20);//��ʾ�ĵ�21/20λλ1������ȡ������Ϊ0�����ݶ��ձ�����p0.26ΪGPIO
	//��ʼ��Ϊ�������Ϊ�ߵ�ƽ
	LPC_GPIO0->FIODIR |= BEEP;
	LPC_GPIO0->FIOSET |= BEEP;

}
void SysTick_Handler(){//ʱ�Ӵ����������ݴ����Ķ����֣����ദ������������¼�+Handler��Ĭ����ʽ
	if(systick++ >= 99){
		systick = 0;
		delay1S = 1;
	}
}
//���������̽�p0.26�������
int main(){
	SystemInit();//ϵͳ��ʼ��������ɾ��
	GPIOInit();//��ʼ������p0.26����ΪGPIO������λ������ߵ�ƽ
	SysTick_Config(10000000/100);//����ʱ��Ƶ��
	while(1){
		while(delay1S == 0);
		delay1S = 0;
		LPC_GPIO0 -> FIOSET |= BEEP;//���������������
		while(delay1S ==0);
		delay1S = 0;
		LPC_GPIO0 -> FIOCLR |= BEEP;//����ߵ�ƽ���á�
	}
}
