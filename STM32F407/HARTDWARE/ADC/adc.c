
/*--------------------- ADC����Ĭ������ --------------------------
ADC_CommonInitStruct->ADC_Mode = ADC_Mode_Independent;						//ģʽ:����ģʽ
ADC_CommonInitStruct->ADC_Prescaler = ADC_Prescaler_Div2;					//��Ƶ:2��Ƶ , 84M / 2 ��Ϊ 42M 
ADC_CommonInitStruct->ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;		//DMA����:ʧ��
ADC_CommonInitStruct->ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;	//����ʱ��:5��ʱ������
---------------------- ADC����Ĭ������ --------------------------
ADC_InitStruct->ADC_Resolution = ADC_Resolution_12b;						//�ֱ���:12λ
ADC_InitStruct->ADC_ScanConvMode = DISABLE;									//ɨ�蹦��:ʧ��
ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;							//����ת����ʧ��
ADC_InitStruct->ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;	//������ʽ����ֹ
ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;			//������ʽ��
ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;						//���䷽ʽ���Ҷ���
ADC_InitStruct->ADC_NbrOfConversion = 1;									//�ɼ����������βɼ�
------------------------------------------------------------------*/
#include "adc.h"

/*************************************************
������:void ADC1_Init(void)
����:��ʼ��ADC1
����:��
����ֵ:��
˵��:
	ADC1��ʼ�� APB2 ����
**************************************************/
void ADC1_Init(void)
{
	//1.ʹ��ADC1 ����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);	
	
	//2.����ADC�������� (�ܶ�ͨ�������õ���ͬһ��ADC)
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_CommonStructInit(&ADC_CommonInitStruct);	//ADCĬ�����ü���
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	//3.ADC��������
	ADC_InitTypeDef ADC_InitStruct;
	ADC_StructInit(&ADC_InitStruct);//ADC����Ĭ�����ü���
	ADC_Init(ADC1, &ADC_InitStruct);
	
	//4.ʹ��ADC����
	ADC_Cmd(ADC1,ENABLE);
}

/**************************************
����:�ɼ�ADCͨ��ֵ
����:
	@ADCx:ʹ�õ���ADC1|2|3
	@ch:�ɼ�ͨ��0 - 15
����ֵ:��ֵ���
***************************************/
u16 Get_ADC(ADC_TypeDef* ADCx,u8 ch)
{
	//1.ָ��ADCͨ������:������ͨ��,һ�����в���ʱ�� ---- ����
	ADC_RegularChannelConfig(ADCx, ch, 1, ADC_SampleTime_480Cycles);	//1��,480��ʱ�����ڲ���
	
	//2.ָ��ADC����ת��
	ADC_SoftwareStartConv(ADCx);
	
	//3.��ȡ�ɼ����
	while(ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) != 1);	//����ת�����
	
	//4.���ؽ��
	return ADC_GetConversionValue(ADCx);
}


