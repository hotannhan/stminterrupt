#include <stm32f10x.h>


void GPIO_config( void ) ;
void EXTI_config( void ) ;
void EXTI0_IRQHandler( void ) ;

int main(){
		
		GPIO_config() ;
		EXTI_config() ;
		
		while ( 1 ) {
		GPIO_ResetBits(	GPIOB , GPIO_Pin_0 ) ;
		}

}

void GPIO_config( void ) {
		
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE ) ;
		
		GPIO_InitTypeDef  GPIO_InitStructure ;
		
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
		GPIO_Init ( GPIOA, &GPIO_InitStructure ) ;
	
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
		GPIO_Init ( GPIOB, &GPIO_InitStructure ) ;
	
}

void EXTI_config( void ) {
		
		RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE	) ;
		
		GPIO_EXTILineConfig(	GPIO_PortSourceGPIOA, GPIO_PinSource0 ) ;
		EXTI_ClearITPendingBit(	EXTI_Line0 ) ;
	
		EXTI_InitTypeDef	EXTI_InitStructure ;
		NVIC_InitTypeDef  NVIC_InitStructure ;
	
		EXTI_InitStructure.EXTI_Line = EXTI_Line0 ;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt ;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling ;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE ;
		EXTI_Init ( &EXTI_InitStructure );
	
		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn ;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
		NVIC_Init ( &NVIC_InitStructure ) ;
	
}



void EXTI0_IRQHandler( void ) {

		if (	EXTI_GetITStatus( EXTI_Line0 ) != RESET	){
				EXTI_ClearITPendingBit(	EXTI_Line0 ) ;
				GPIO_SetBits(	GPIOB , GPIO_Pin_0 ) ;
			
		}
	
}

