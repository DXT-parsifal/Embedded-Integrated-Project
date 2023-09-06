
/*--------------------- ADC公共默认配置 --------------------------
ADC_CommonInitStruct->ADC_Mode = ADC_Mode_Independent;						//模式:独立模式
ADC_CommonInitStruct->ADC_Prescaler = ADC_Prescaler_Div2;					//分频:2分频 , 84M / 2 则为 42M 
ADC_CommonInitStruct->ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;		//DMA功能:失能
ADC_CommonInitStruct->ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;	//采样时间:5个时钟周期
---------------------- ADC参数默认配置 --------------------------
ADC_InitStruct->ADC_Resolution = ADC_Resolution_12b;						//分辨率:12位
ADC_InitStruct->ADC_ScanConvMode = DISABLE;									//扫描功能:失能
ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;							//连续转换：失能
ADC_InitStruct->ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;	//触发方式：禁止
ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;			//触发方式：
ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;						//对其方式：右对齐
ADC_InitStruct->ADC_NbrOfConversion = 1;									//采集次数：单次采集
------------------------------------------------------------------*/
#include "adc.h"

/*************************************************
函数名:void ADC1_Init(void)
功能:初始化ADC1
参数:无
返回值:无
说明:
	ADC1初始化 APB2 总线
**************************************************/
void ADC1_Init(void)
{
	//1.使能ADC1 总线时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);	
	
	//2.配置ADC公共设置 (很多通道都是用的是同一个ADC)
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_CommonStructInit(&ADC_CommonInitStruct);	//ADC默认配置即可
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	//3.ADC参数配置
	ADC_InitTypeDef ADC_InitStruct;
	ADC_StructInit(&ADC_InitStruct);//ADC参数默认配置即可
	ADC_Init(ADC1, &ADC_InitStruct);
	
	//4.使能ADC功能
	ADC_Cmd(ADC1,ENABLE);
}

/**************************************
功能:采集ADC通道值
参数:
	@ADCx:使用的是ADC1|2|3
	@ch:采集通道0 - 15
返回值:数值结果
***************************************/
u16 Get_ADC(ADC_TypeDef* ADCx,u8 ch)
{
	//1.指定ADC通道规则:规则组通道,一个序列采样时间 ---- 单次
	ADC_RegularChannelConfig(ADCx, ch, 1, ADC_SampleTime_480Cycles);	//1次,480个时钟周期采样
	
	//2.指定ADC开启转换
	ADC_SoftwareStartConv(ADCx);
	
	//3.获取采集结果
	while(ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) != 1);	//死等转换结果
	
	//4.返回结果
	return ADC_GetConversionValue(ADCx);
}


