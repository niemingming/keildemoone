#include "LPC17xx.h"//引入LPC头文件
//我们根据网上例子熟悉蜂鸣器使用，通过引脚选择寄存器PINSEL1设置相关引脚功能。
//预定义变量
uint32_t BEEP = (1<<26);//定位到第26位，该位位p0.26
//定义变量
uint32_t systick = 0;//系统时钟变化
uint32_t delay1S = 0;//延迟1秒标志

//定义延迟函数，延迟函数没有调用，通过Tick形式实现延迟									  l
void delay(uint32_t ultime){
	ultime*= 5000;
	while(ultime--);
}
//选择引脚被设置为输入输出GPIO
void GPIOInit(){
	LPC_PINCON->PINSEL1 &= ~(0x3<<20);//表示的第21/20位位1，这里取反设置为0，根据对照表设置p0.26为GPIO
	//初始化为输出，且为高电平
	LPC_GPIO0->FIODIR |= BEEP;
	LPC_GPIO0->FIOSET |= BEEP;

}
void SysTick_Handler(){//时钟处理函数，根据代码阅读发现，这类处理函数都是相关事件+Handler，默认形式
	if(systick++ >= 99){
		systick = 0;
		delay1S = 1;
	}
}
//主函数，短接p0.26与蜂鸣器
int main(){
	SystemInit();//系统初始化，切勿删除
	GPIOInit();//初始化，将p0.26设置为GPIO，且置位输出，高电平
	SysTick_Config(10000000/100);//设置时钟频率
	while(1){
		while(delay1S == 0);
		delay1S = 0;
		LPC_GPIO0 -> FIOSET |= BEEP;//输出，蜂鸣器响起
		while(delay1S ==0);
		delay1S = 0;
		LPC_GPIO0 -> FIOCLR |= BEEP;//清除高电平设置。
	}
}
