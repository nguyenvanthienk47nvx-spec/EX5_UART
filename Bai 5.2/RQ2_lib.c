#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "string.h"

char data[100];
char check_onled[]  = "ON";
char check_offled[] = "OFF";
int t = 0;

void GPIO_Configure(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void USART_Configure(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate            = 9600;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_EnableIRQ(USART1_IRQn);
}

int on_led(void){
    for (int i = 0; i < strlen(check_onled); i++) {
        if (data[i] != check_onled[i]) return 0;
    }
    return 1;
}

int off_led(void){
    for (int i = 0; i < strlen(check_offled); i++) {
        if (data[i] != check_offled[i]) return 0;
    }
    return 1;
}

void USART1_IRQHandler(void){
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        char c = USART_ReceiveData(USART1);
      
        USART_SendData(USART1, c);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        
        if(c != '\n' && c != '\r') data[t++] = c;
				else{
            if(on_led()){
                GPIO_SetBits(GPIOA, GPIO_Pin_5);   
            }
						else if(off_led()){
                GPIO_ResetBits(GPIOA, GPIO_Pin_5); 
            }
            t = 0;
            memset(data, 0, sizeof(data));
        }
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

int main(void){
    GPIO_Configure();
    USART_Configure();
    while(1){
    }
}