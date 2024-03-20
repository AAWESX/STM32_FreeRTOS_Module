#include "Buzzer\Buzzer_Control.h"

#include "cmsis_os.h"

extern TIM_HandleTypeDef htim4;

static TIM_HandleTypeDef  *g_PassiveBuzzer = &htim4;

/**********************************************************************
 * �������ƣ� PassiveBuzzer_Control
 * ���������� ��Դ���������ƺ���
 * ��������� on - 1-��, 0-����
 * ��������� ��
 * �� �� ֵ�� ��
 * �޸����ڣ�      �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2023/08/04	     V1.0
 ***********************************************************************/
void PassiveBuzzer_Control(int on)
{
    if (on)
    {
        HAL_TIM_PWM_Start(g_PassiveBuzzer, TIM_CHANNEL_3);
    }        
    else
    {
        HAL_TIM_PWM_Stop(g_PassiveBuzzer, TIM_CHANNEL_3);
    }
}

/**********************************************************************
 * �������ƣ� PassiveBuzzer_Set_Freq_Duty
 * ���������� ��Դ���������ƺ���: ����Ƶ�ʺ�ռ�ձ�
 * ��������� freq - Ƶ��, duty - ռ�ձ�
 * ��������� ��
 * �� �� ֵ�� ��
 * �޸����ڣ�      �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2023/08/04	     V1.0
 ***********************************************************************/
void PassiveBuzzer_Set_Freq_Duty(int freq, int duty)
{
    TIM_OC_InitTypeDef sConfig = { 0 };

    HAL_TIM_PWM_Stop(g_PassiveBuzzer, TIM_CHANNEL_3);

    HAL_TIM_Base_DeInit(g_PassiveBuzzer);
    g_PassiveBuzzer->Instance = TIM4;
    g_PassiveBuzzer->Init.Prescaler = 71;
    g_PassiveBuzzer->Init.CounterMode = TIM_COUNTERMODE_UP;
    g_PassiveBuzzer->Init.Period = 1000000 / freq - 1;  
    g_PassiveBuzzer->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    g_PassiveBuzzer->Init.RepetitionCounter = 0;
    g_PassiveBuzzer->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(g_PassiveBuzzer);


    sConfig.OCMode = TIM_OCMODE_PWM1;        // PWM ���������ģʽ:PWM1 ������Ϊ��,CCR<CNT,����͵�ƽ,��֮�ߵ�ƽ
    sConfig.OCPolarity = TIM_OCPOLARITY_LOW; // ���ü���Ϊ��(Ӳ���ϵ͵�ƽ����)
    sConfig.OCFastMode = TIM_OCFAST_DISABLE; // ����ȽϿ���ʹ�ܽ�ֹ(���� PWM1 �� PWM2 ������)
    sConfig.Pulse      = (1000000 / freq - 1) * duty / 100;                // �� PWM1 ģʽռ�ձ�
    
    HAL_TIM_PWM_ConfigChannel(g_PassiveBuzzer, &sConfig, TIM_CHANNEL_3);

    HAL_TIM_PWM_Start(g_PassiveBuzzer, TIM_CHANNEL_3);
}



/**********************************************************************
 * �������ƣ� PassiveBuzzer_Test
 * ���������� ��Դ���������Գ���
 * ��������� ��
 * ��������� ��
 *            ��
 * �� �� ֵ�� ��
 * �޸�����        �汾��     �޸���        �޸�����
 * -----------------------------------------------
 * 2023/08/04        V1.0
 ***********************************************************************/
void PassiveBuzzer_Test(void)
{

    while (1)
    {
        PassiveBuzzer_Control(1);
        osDelay(1000);

        PassiveBuzzer_Control(0);
        osDelay(1000);
    }
}
