/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
//uint8_t u2_RX_Buf[8];
uint8_t recv_msg[8];
uint8_t send_msg[8];
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */

    /* 初始示例 */
    /*
    static int cnt = 1;
    HAL_GPIO_TogglePin(USR_LED_GPIO_Port, USR_LED_Pin);
    u_printf(&huart1, "test: %d %f\r\n", cnt, 1.0/cnt);
    ++cnt;
    HAL_Delay(500);
    */

    /* 蓝牙和电脑通信 */
    /*
    while (HAL_UART_Receive(&huart2, u2_RX_Buf, sizeof(u2_RX_Buf), 100) != HAL_OK);
    u_printf(&huart1, "received:"); // 转发到串口1
    HAL_UART_Transmit(&huart1, u2_RX_Buf, sizeof(u2_RX_Buf), HAL_MAX_DELAY);
    u_printf(&huart2, "received:"); // 转发到串口2
    HAL_UART_Transmit(&huart2, u2_RX_Buf, sizeof(u2_RX_Buf), HAL_MAX_DELAY);
    delay_ms(100);
    */

    /* Asignment */

    /* A */
    // partA();

    /* B */
    partB();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void partA()
{
  int rand_num = 100000 + rand() % 900000; //生成随机六位数
  uint8_t recv_msg[8];

  u_printf(&huart1, "A-made:%d", rand_num);

  u_printf(&huart2, "%d", rand_num);

  u_printf(&huart1, "A->B");

  while (HAL_UART_Receive(&huart2, recv_msg, 6, 100) != HAL_OK); //接收数据,最大延时100ms
  recv_msg[6] = '\0';
  u_printf(&huart1, "A-recv:%s", recv_msg); // A接收字符发送给串口

  for (int j = 0; j < 6; ++j)
  {
    HAL_GPIO_TogglePin(USR_LED_GPIO_Port, USR_LED_Pin);
    delay_ms(20);
  } //如果接收到信息，LED闪三下

  HAL_Delay(3000);  //每隔三秒发送随机数字
}

void partB()
{
   while (HAL_UART_Receive(&huart2, recv_msg, 6, 10000) != HAL_OK); //接收数据
   recv_msg[6] = '\0';
   u_printf(&huart1, "B-recv:%s", recv_msg); // B接收字符发送给串口

   for (int j = 0; j < 6; ++j)
   {
     send_msg[j] = recv_msg[5 - j];
   }
   send_msg[6] = '\0';

   u_printf(&huart1, "B-reverse:%s", send_msg); //反转后发给串口

   u_printf(&huart1, "B->A");
   
   u_printf(&huart2, send_msg);

   
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
