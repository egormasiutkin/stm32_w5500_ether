/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32g0xx_hal.h"
#include "pcb_config.h"
#include "usart.h"
#include <String.h>
#include "buttons.h"
#include "Protocol.h"
#include "APP_Web.h"
#include "String.h"
#include "socket.h"
#include "Infrared.h"
#include <math.h>
#include "loop.h"
#include "MyApp.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum
{
	INIT_STATUS_LED,
	IDLE_STATUS_LED,
	LOAD_USB_LED,
	BUTTON_PRESSED_LED_1,
	BUTTON_PRESSED_LED_2,
	BUTTON_PRESSED_LED_3,
	BUTTON_PRESSED_LED_4,
	LEARNLED,
	LEARNLED2,
	LEARNLED3,
	LEARNLED4
} LED_Status_State;
typedef enum
{
	IDLESTAT,
	BTN_PRESSED1,
	BTN_PRESSED2,
	USB_LOAD_INITIATED,
	LEARN_STATUS_LED,
	LEARN_STATUS_LED2
} LED_Status;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SEND_TEST_IR 0
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim14;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
extern struct PCB_Config file;
extern uint32_t send_var;
extern uint64_t code_ON[MAX_NUMBER];
extern uint64_t code_OFF[MAX_NUMBER];
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern struct tv_protocol tv_protocol[3];
extern uint32_t RS232_command_ON;
extern uint32_t RS232_command_OFF;
extern uint32_t IR_command;
extern uint32_t IR_command_off;
extern uint32_t Temp_Treshold_Min;
extern uint32_t Temp_Treshold_Max;
extern int PIRAlarm;
extern int TempAlarm;
extern int RS232Alarm;
extern int IRAlarm;
extern IR_Receive_State_def IR_Receive_State;
extern IR_Receive_OFF_State_def IR_Receive_OFF_State;
extern Loop_State loop_state_process;
extern Motion_State motion_state_process;
extern uint8_t time_alarm_on_hh, time_alarm_on_mm, time_alarm_off_hh, time_alarm_off_mm;
extern uint8_t onSwitch;
extern uint32_t onDateTime;
extern uint8_t offSwitch;
extern uint32_t offDateTime;
extern uint8_t timezone;
extern bool timesynch_on_was_sent;
extern bool timesynch_off_was_sent;
uint32_t timesynch_counter = 0;
uint32_t recursion_counter = 0;
extern int Recursion_Alarm_ON[7];
extern int Recursion_Alarm_OFF[7];
extern int Recursion_Alarm_ON[7];
extern int Recursion_Alarm_OFF[7];
extern uint8_t time_alarm_on_hh, time_alarm_on_mm, time_alarm_off_hh, time_alarm_off_mm;
extern uint8_t time_alarm_on_sun, time_alarm_on_mon, time_alarm_on_tue, time_alarm_on_wed, time_alarm_on_thu, time_alarm_on_fri, time_alarm_on_sat;
extern uint8_t time_alarm_off_sun, time_alarm_off_mon, time_alarm_off_tue, time_alarm_off_wed, time_alarm_off_thu, time_alarm_off_fri, time_alarm_off_sat;
int sw1_instantaneous = 0;
int sw2_instantaneous = 0;
int sw3_instantaneous = 0;
extern float realTimeZone;
uint32_t timestamp_1min_lock = 0;
uint32_t timestamp_100ms = 0;
uint32_t timestamp_algo = 0;
uint32_t timestamp_led = 0;
uint32_t timestamp_btn = 0;
uint32_t command_sent = 0;
struct PCB_Config pcb_config_read;
int locked = 1;
int on_receive = 1;
uint32_t tv_type = 1; // 0 = lg and 1 = samsung
uint32_t adcval = 0;
float adcval2;
float temperature_farenheit = 0;
bool start_pir = false;
int dechundred;
int decten;
int dec;
uint16_t temp_max;
int dechundred_min;
int decten_min;
int dec_min;
uint16_t temp_min;
uint32_t nec_start_delay = 4500; // 9000 LG and 4500 Samsung
float temperature_max_treshold;
float temperature_min_treshold;
void *vptr_test;
unsigned int allo, Number, RevNumber;
int device, subdevice, function_code, function_code_ff, full_ir_code_from_db;
int function_code = 0;
static LED_Status_State status_led_state = INIT_STATUS_LED;
LED_Status led2_status = IDLESTAT;
int count_led_status = 0;
uint32_t timestamp_status_led = 0;
uint8_t firmware_update = 0;
uint8_t loggin = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM14_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */
void USART2_ReInit(void);
void MeasureTemperature(int tempsensortype);
void TestIR();
void GetDeviceCodeNEC();
void TimeSyncAlgorithm();
void HeartBeatLedStart();
int dayofweek(time_t now, int tz_offset);
void RecursionAlarmAlgorithm();
void Status_Led();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
pFunction JumpToApplication;
uint32_t JumpAddress;
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
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM14_Init();
  MX_USART2_UART_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  /*
  if (((*(__IO uint32_t*)APPLICATION_ADDRESS) & 0x2FF00000 ) == 0x20000000)
  	{
  	 __disable_irq();
  	  SCB->VTOR = APPLICATION_ADDRESS;
  	  JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
  	  JumpToApplication = (pFunction) JumpAddress;
  	  __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
  	  JumpToApplication();
  	}*/
	SetPCB_Config();
	Set_tv_protocol();
	USART2_ReInit();
	SET_BIT(SYSCFG->CFGR1, (1 << 9));
	CLEAR_BIT(SYSCFG->CFGR1, (1 << 9));
	SET_BIT(SYSCFG->CFGR1, (1 << 9));
	ReadAndSetConfig();
	Calculate_Temperatures_Offsets();
	Send_Version_Data();
	// PWM for the IR sending
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	TIM14->CCR1 = VAR;
	// 1us timer
	HAL_TIM_Base_Start(&htim1);
	// take t0 for the main loop
	timestamp_100ms = HAL_GetTick();
	HAL_ADC_Start(&hadc1);
	// Start temp adc measurement
	HAL_ADC_PollForConversion(&hadc1, 1000);
	adcval = HAL_ADC_GetValue(&hadc1);
	adcval2 = adcval * 3.3 / 4095 * 100;
	temperature_farenheit = (adcval2 * 9.0 / 5.0) + 30.25;
	HAL_ADC_Stop(&hadc1);
	init_the_thing();
	Init_WebAPP();
	timestamp_led = HAL_GetTick();
	// GET app t0
	timestamp_btn = HAL_GetTick();
	timesynch_counter = HAL_GetTick();
	recursion_counter = HAL_GetTick();
	char stringrer[] = "PCB Board Initialization done2, starting loop";
	LogToBufferLog(stringrer, sizeof(stringrer));
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	if (locked) Task_WebAPP();
	if(firmware_update) NVIC_SystemReset();
	Uart_process();
	if (start_pir) Motion_Detection_Process();
	// Blink LED1 each 500 ms
	Status_Led();
	HeartBeatLedStart();
	// Buttons reading process
	Btn1_Process();
	Btn2_Process();
	// Btn3_Process();
	// Lock the IR receive process after 60s
	if (((HAL_GetTick() - timestamp_1min_lock) >= 60000) && !locked)		locked = true;
	// Keep receiving IR until locked
	if (!locked)
	{
		if (on_receive)
			IR_Receive_Process();
		else
			IR_Receive_Process_OFF();
	}
	// Read temperature each 10 sec
	if ((HAL_GetTick() - timestamp_100ms) >= 15000 && locked)
	{
		timestamp_100ms = HAL_GetTick();
		start_pir = true;
		MeasureTemperature(0);
	}
	//  Check buttons each 60 ms
	if ((HAL_GetTick() - timestamp_algo) >= 60)
	{
		timestamp_algo = HAL_GetTick();
		ButtonsAlgorithm();
	}
	// MAIN PIR sensor and temp sensor algorithm
	MainAlgorithm();
	TimeSyncAlgorithm();
	RecursionAlarmAlgorithm();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.LowPowerAutoPowerOff = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_160CYCLES_5;
  hadc1.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_160CYCLES_5;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */
  HAL_ADCEx_Calibration_Start(&hadc1);
  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00303D5B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutPullUp = RTC_OUTPUT_PULLUP_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  sTime.Hours = 0x0;
	sTime.Minutes = 0x0;
	sTime.Seconds = 0x0;
	sTime.SubSeconds = 0x0;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
	{
	  Error_Handler();
	}
	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	sDate.Month = RTC_MONTH_JANUARY;
	sDate.Date = 0x1;
	sDate.Year = 0x0;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
	{
	  Error_Handler();
	}
  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 15;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65534;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 0;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 420;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 631;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim14, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */
  HAL_TIM_MspPostInit(&htim14);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, CS_Pin|WP_Pin|RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : CS_Pin WP_Pin RST_Pin */
  GPIO_InitStruct.Pin = CS_Pin|WP_Pin|RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Pin LED2_Pin */
  GPIO_InitStruct.Pin = LED_Pin|LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SW3_Pin BTN_2_Pin SW2_Pin */
  GPIO_InitStruct.Pin = SW3_Pin|BTN_2_Pin|SW2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DETECT_Pin IR_IN_Pin */
  GPIO_InitStruct.Pin = DETECT_Pin|IR_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_1_Pin SW1_Pin */
  GPIO_InitStruct.Pin = BTN_1_Pin|SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void USART2_ReInit(void)
{

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	int baurate = ((uint32_t)(pcb_config.rs1[0] - '0') * 100000) +
				  ((uint32_t)(pcb_config.rs1[1] - '0') * 10000) +
				  ((uint32_t)(pcb_config.rs1[2] - '0') * 1000) +
				  ((uint32_t)(pcb_config.rs1[3] - '0') * 100) +
				  ((uint32_t)(pcb_config.rs1[4] - '0') * 10) +
				  ((uint32_t)(pcb_config.rs1[5] - '0'));

	changeBaudRate(baurate, pcb_config.rs2[0] - '0', pcb_config.rs3[0] - '0');

	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */
	// HAL_UART_Receive_IT(&huart2, (uint8_t*)&rx_uart, 1); //Init the UART interruption for the first time
	/* USER CODE END USART2_Init 2 */
}
void ResetLoopProcess()
{
	loop_state_process = LOOP_INIT;
	command_sent = 0;
	motion_state_process = INITMOT;
}
void TestIR()
{
	// RC5_Send_Data(0x3012);
	// RC5_Send_Data(0x300C);
	//	  BurstRC5TV(0x300C);
	//	  RC5_Send_Data(0x300C);
	//		  Sharp_Send_Data(0x045A);
	//		  HAL_Delay(40);
	//		  Sharp_Send_Data(0x075A);
	//		  HAL_Delay(40);
	//		  Sharp_Send_Data(0x045A);
	//		 		  HAL_Delay(40);
	//		 		  Sharp_Send_Data(0x075A);

	//	  Sharp_Send_Data(0x41A2);
	//	  HAL_Delay(49.1);
	//	  Sharp_Send_Data(0x425D);
	//	  HAL_Delay(46.18);
	//	  Sharp_Send_Data(0x41A2);
	//	  HAL_Delay(48.1);
	//	  Sharp_Send_Data(0x425D);
	//	  HAL_Delay(46.18);
	//	  Sharp_Send_Data(0x41A2);

	//		  HAL_Delay(67.9);
	//		  Sharp_Send_Data(0x41A2);
	//
	//
	//		 		  HAL_Delay(67.9);
	//
	//		 		 Sharp_Send_Data(0x41A2);
	//		 				  HAL_Delay(67.9);
	//		 				  Sharp_Send_Data(0x425D);
	//		 				  HAL_Delay(67.9);
	//		 				  Sharp_Send_Data(0x41A2);
	// Sharp_Send_Data(0x425D);
	//		 		HAL_Delay(40);
	//		 		Sharp_Send_Data(0x41A2);
	//		 				  HAL_Delay(40);
	//		 				 Sharp_Send_Data(0x425D);

	//	  Sharp_Send_Data(0x425E);
	//	  HAL_Delay(40);
	//  Sharp_Send_Data(0x41A2);
	//	  HAL_Delay(40);
	// Sharp_Send_Data(0x425D);
	//  Sharp_Send_Data(0x425E);
	//		  HAL_Delay(40);
	//		  Sharp_Send_Data(0x41A2);
	//		  HAL_Delay(40);
	//		  Sharp_Send_Data(0x425D);

	//		  	  HAL_Delay(45);
	//		  	  //NEC_Start();
	//		  	  RC5_Send_Data(0x3800C);
	//		  	  HAL_Delay(45);
	//		  	 // NEC_Start();
	//		  	  RC5_Send_Data(0x300C);
	//
	//		  	HAL_Delay(45);
	//		  			  	 // NEC_Start();
	//		  			  	  RC5_Send_Data(0x3800C);
	//	 RC6TV(0x000C);
	// BurstRC6TV(0x000C);
	// BurstNEC(true);
	// IRSend_Var_NEC(0xEAC717E8); // addr ea c7 command 17e8
	// IRSend_Var_NEC(0x73577117);

	//		 IRSend_Var_NEC(0x57E3E817);
	//		 IRSend_Var_NEC(0x57E3E817);
	//		 IRSend_Var_NEC(0x57E3E817);

	//		 IRSend_Var_NEC(0x61A0F00F);
	//				 IRSend_Var_NEC(0x61A0F00F);
	//				 IRSend_Var_NEC(0x61A0F00F);
	//		 IRSend_Var_NEC(0xEAC717E8);
	//		 IRSend_Var_NEC(0xEAC717E8);
	//
	//		 IRSend_Var_NEC(0xC7EAE817);
	//		 IRSend_Var_NEC(0xC7EAE817);
	//		 IRSend_Var_NEC(0xC7EAE817);
	//
	//
	//		 IRSend_Var_NEC(0x17E8E357);
	//		 IRSend_Var_NEC(0x17E8E357);
	//		 IRSend_Var_NEC(0x17E8E357);

	//		 IRSend_Var_NEC(0xE35717E8);
	//		 		 IRSend_Var_NEC(0xE35717E8);
	//		 		 IRSend_Var_NEC(0xE35717E8);
	//
	//		 		IRSend_Var_NEC(0xAE7C17E8);
	//		 				 		 IRSend_Var_NEC(0xAE7C17E8);
	//		 				 		 IRSend_Var_NEC(0xAE7C17E8);
	//
	//
	//		 				 		IRSend_Var_NEC(0xAE7CE817);
	//		 				 		 IRSend_Var_NEC(0xAE7CE817);
	//		 				 		 IRSend_Var_NEC(0xAE7CE817);

	// BurstRC5TV(0x3012);
	//		  IRSend_Var_NEC(0xE0E040BF);
	//		  IRSend_Var_NEC(0xE0E040BF);
	////		  IRSend_Var_NEC(0xE0E040BF);
	//		  NEC_Start();
	//		  			//Panasonic_Send_Data(0x022080003DBD);
	//		  			//Panasonic_Send_Data(0xBDBC00010440);
	//		  			Panasonic_Send_Data(0x40040100BCBD);
	//		  			 NEC_Stop();
	//		  			HAL_Delay(100);
	//		  			 NEC_Start();
	//		  					  			//Panasonic_Send_Data(0x022080003DBD);
	//		  					  			//Panasonic_Send_Data(0xBDBC00010440);
	//		  					  			Panasonic_Send_Data(0x40040100BCBD);
	//		  					  		 NEC_Stop();
	//		  					  		HAL_Delay(100);
	//		  					  		 NEC_Start();
	//		  					  				  			//Panasonic_Send_Data(0x022080003DBD);
	//		  					  				  			//Panasonic_Send_Data(0xBDBC00010440);
	//		  					  				  			Panasonic_Send_Data(0x40040100BCBD);
	//		  					  				  		 NEC_Stop();
	//  BurstSony12TV(0xA90);
}
void MeasureTemperature(int tempsensortype)
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
	adcval = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	// HAL_ADC_Start(&hadc1);

	switch (tempsensortype)
	{

	case 0 /* "LM35DZ"*/:
		adcval2 = adcval * 3.3 / 4095 * 100; // LM35DZ
		break;
	case 1 /*"LMT86LPGM"*/:
		adcval2 = -10 / 109 * (1000 * adcval * 3.3 / 4095 - 2103); // LMT86LPGM
		break;
	case 2 /*"LMT84LPGM"*/:
		adcval2 = -adcval * 1.1 / 4095 - 893 / 600; // LMT84LPGM
		break;
	case 3 /*"LMT85LPGM"*/:
		adcval2 = 5 / 41 * (1569 - 1000 * adcval * 3.3 / 4095); // LMT85LPGM
		break;
	default:
		adcval2 = adcval * 3.3 / 4095 * 100; // LM35DZ
		break;
	}

	temperature_farenheit = (adcval2 * 9.0 / 5.0) + 30.25;
	Send_Temperature_Data(temperature_farenheit);
	// command_sent = 0;
	dechundred = (pcb_config.sSetTempTreshMax[0] - '0') * 100;
}

void ButtonsAlgorithm()
{
	function_code = (int)(BTN3_Is_Pressed()) * 4 + (int)(BTN2_Is_Pressed()) * 2 + (int)(BTN1_Is_Pressed());
	sw1_instantaneous = !(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin));
	sw2_instantaneous = !(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin));
	sw3_instantaneous = !(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin));

	function_code = sw1_instantaneous * 16 + sw2_instantaneous * 8 + sw3_instantaneous * 4 + (int)(BTN2_Is_Pressed()) * 2 + (int)(BTN1_Is_Pressed());

	switch (function_code)
	{

	case 18: // IR LEARN ON

		Send_BTN_ON(1, 8);
		SetBtnPress(false, 2);
		on_receive = 1;
		locked = false;
		IR_Receive_State = INIT_IR;
		IR_Receive_OFF_State = INIT2;
		timestamp_1min_lock = HAL_GetTick();
		Send_Version_Data();
		led2_status = LEARN_STATUS_LED;
		break;

	case 17: // IR LEARNING OFF

		Send_BTN_ON(1, 7);
		SetBtnPress(false, 1);
		locked = false;
		on_receive = 0;
		timestamp_1min_lock = HAL_GetTick();
		IR_Receive_State = INIT_IR;
		IR_Receive_OFF_State = INIT2;
		led2_status = LEARN_STATUS_LED2;
		break;

	case 10: // TRANSMIT OFF COMMAND
		led2_status = BTN_PRESSED2;
		SetBtnPress(false, 2);
		Send_BTN_ON(1, 0);
		Send_RS232_Command_OFF();
		IRSend_NEC(false);

		break;

	case 9: // SEND RSR 232 COMMAND
		Send_BTN_ON(0, 9);
		led2_status = BTN_PRESSED1;
		SetBtnPress(false, 1);
		Send_RS232_Command_ON();
		IRSend_NEC(true);

		break;

	case 6: // LOG USB 18
		Send_BTN_ON(0, 6);
		led2_status = LEARN_STATUS_LED;
		SetBtnPress(false, 2);
		loop2();
		loop3();
		Send_String("Logging to USB\n\r", sizeof("Logging to USB\n\r"));
		break;
	case 5: // READ PCB CONFIG 17
	{
		led2_status = BTN_PRESSED1;
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		SetBtnPress(false, 1);
		Send_BTN_ON(1, 7);

		MyApp();

		ReadAndSetConfig();
		Calculate_Temperatures_Offsets();
		int baurate = ((uint32_t)(pcb_config.rs1[0] - '0') * 100000) + ((uint32_t)(pcb_config.rs1[1] - '0') * 10000) + ((uint32_t)(pcb_config.rs1[2] - '0') * 1000) + ((uint32_t)(pcb_config.rs1[3] - '0') * 100) + ((uint32_t)(pcb_config.rs1[4] - '0') * 10) + ((uint32_t)(pcb_config.rs1[5] - '0'));

		changeBaudRate(baurate, pcb_config.rs2[0] - '0',
					   pcb_config.rs3[0] - '0');

		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		break;
	}
	default:
		led2_status = IDLESTAT;
		break;
	}
}

void TimeSyncAlgorithm()
{
	if ((HAL_GetTick() - timesynch_counter) >= 20000)
	{
		timesynch_counter = HAL_GetTick();

		if (onSwitch == 1 && timesynch_on_was_sent == 0)
		{

			if (get_epoch_time() >= onDateTime)
			{
				timesynch_on_was_sent = 1;

				if (pcb_config.sSetIRON[0] - '0')
				{
					IRSend_NEC(true);
					IRSend_NEC(true);
					IRSend_NEC(true);
				}
				if (pcb_config.sSetRS232ON[0] - '0')
					Send_RS232_Command_ON();
			}
		}

		if (offSwitch == 1 && timesynch_off_was_sent == 0)
		{

			if (get_epoch_time() >= offDateTime)
			{
				timesynch_off_was_sent = 1;

				if (pcb_config.sSetIRON[0] - '0')
				{
					IRSend_NEC(false);
					IRSend_NEC(false);
					IRSend_NEC(false);
				}
				if (pcb_config.sSetRS232ON[0] - '0')
					Send_RS232_Command_OFF();
			}
		}
	}
}

void RecursionAlarmAlgorithm()
{
	int timezoneHours = 0;

	if (ceilf(realTimeZone) == realTimeZone)
		timezoneHours = (int)realTimeZone;
	else
	{
		timezoneHours = floorf(realTimeZone);

		if (timezoneHours > 0)
			time_alarm_on_mm += 30;
		else
			time_alarm_on_mm -= 30;
	}
	if ((HAL_GetTick() - recursion_counter) >= 59000)
	{
		recursion_counter = HAL_GetTick();

		// Convert to number of days since 1 Jan 1970 1 Jan 1970 was a Thursday, so add 4 so Sunday is day 0, and mod 7
		time_t localtime = get_epoch_time() + (timezoneHours * 60 * 60);
		int days_since_epoch = localtime / 86400;
		int day_of_week = (days_since_epoch + 4) % 7;
		printf("Day of Week : %d\r\n", day_of_week);

		// When DAY alarm is active
		if (Recursion_Alarm_ON[day_of_week] == 1)
		{
			// Did we reach desired local time?
			if (Get_Hours() + timezoneHours == time_alarm_on_hh)
			{
				// Did we reach the desired minute?
				if (Get_Minutes() == time_alarm_on_mm)
				{
					printf("DAILY ALARM ON /R/N");

					if (pcb_config.sSetIRON[0] - '0')
					{
						IRSend_NEC(true);
						IRSend_NEC(true);
						IRSend_NEC(true);
					}
					if (pcb_config.sSetRS232ON[0] - '0')
						Send_RS232_Command_ON();
				}
			}
		}

		if (Recursion_Alarm_OFF[day_of_week] == 1)
		{
			// Did we reach desired local time?
			if (Get_Hours() + timezoneHours == time_alarm_off_hh)
			{
				// Did we reach the desired minute?
				if (Get_Minutes() == time_alarm_off_mm)
				{
					printf("DAILY ALARM OFF /R/N");

					if (pcb_config.sSetIRON[0] - '0')
					{
						IRSend_NEC(false);
						IRSend_NEC(false);
						IRSend_NEC(false);
					}
					if (pcb_config.sSetRS232ON[0] - '0')
						Send_RS232_Command_OFF();
				}
			}
		}
	}
}
void MainAlgorithm()
{
	if (pcb_config.loopon == 2 && pcb_config.loopoff == 2)
	{
		if (command_sent == 0)
		{
			if (pcb_config.sSetTempON[0] - '0' == 1)
			{

				if ((temperature_farenheit < temperature_min_treshold) || (temperature_farenheit > temperature_max_treshold))
				{
					if (pcb_config.sSetIRON[0] - '0')
					{
						IRSend_NEC(true);
						IRSend_NEC(true);
						IRSend_NEC(true);
					}
					if (pcb_config.sSetRS232ON[0] - '0')
						Send_RS232_Command_ON();

					command_sent = 1;
				}
			}
			if (pcb_config.sSetPIRON[0] - '0' == 1)
			{
				if (send_var == 1)
				{
					send_var = 0;

					if (pcb_config.sSetIRON[0] - '0')
					{
						if (Motion_Is_Detected())
						{
							IRSend_NEC(true);
							IRSend_NEC(true);
							IRSend_NEC(true);
						}
						else
						{
							IRSend_NEC(false);
							IRSend_NEC(false);
							IRSend_NEC(false);
						}
					}
					if (pcb_config.sSetRS232ON[0] - '0')
					{
						if (Motion_Is_Detected())
							Send_RS232_Command_ON();
						else
							Send_RS232_Command_OFF();
					}
					command_sent = 1;
				}
			}
		}
		else
		{
			if (pcb_config.sSetTempON[0] - '0' == 1)
			{

				if ((temperature_farenheit < temperature_min_treshold) && (temperature_farenheit < temperature_max_treshold))
				{
					if (pcb_config.sSetIRON[0] - '0')
					{
						IRSend_NEC(false);
						IRSend_NEC(false);
						IRSend_NEC(false);
					}
					if (pcb_config.sSetRS232ON[0] - '0')
						Send_RS232_Command_OFF();

					command_sent = 0;
				}
			}
			if (pcb_config.sSetPIRON[0] - '0' == 1)
			{
				if (send_var == 1)
				{
					send_var = 0;
					if (pcb_config.sSetIRON[0] - '0')
					{
						if (Motion_Is_Detected())
						{
							IRSend_NEC(true);
							IRSend_NEC(true);
							IRSend_NEC(true);
						}
						else
						{
							IRSend_NEC(false);
							IRSend_NEC(false);
							IRSend_NEC(false);
						}
					}
					if (pcb_config.sSetRS232ON[0] - '0')
					{
						if (Motion_Is_Detected())
							Send_RS232_Command_ON();
						else
							Send_RS232_Command_OFF();
					}

					command_sent = 0;
				}
			}
		}
	}
	else
	{
		loop_process();
	}
}
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART1 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

	return ch;
}

/* USER CODE BEGIN 1 */
/* Process States */

// Calculate the current day of the week as an integer
//   now - Unix timestamp like that from time(NULL)
//   tz_offset - Number of hours off from UTC; i.e. PST = -8
//   Return value: Sunday=0, Monday=1, ... Saturday=6
int dayofweek(time_t now, int tz_offset)
{
	// Calculate number of seconds since midnight 1 Jan 1970 local time
	time_t localtime = now + (tz_offset * 60 * 60);
	// Convert to number of days since 1 Jan 1970
	int days_since_epoch = localtime / 86400;
	// 1 Jan 1970 was a Thursday, so add 4 so Sunday is day 0, and mod 7
	int day_of_week = (days_since_epoch + 4) % 7;

	return day_of_week;
}

uint32_t count_led_status2 = 0;
bool stop_heart_beat_led = false;

void HeartBeatLed()
{
	if ((HAL_GetTick() - timestamp_led) >= 500)
	{
		timestamp_led = HAL_GetTick();
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}
}
void HeartBeatLedStart()
{
	if ((HAL_GetTick() - timestamp_led) >= 500 && !stop_heart_beat_led)
	{
		count_led_status2++;
		timestamp_led = HAL_GetTick();
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}
	if (count_led_status2 >= 20)
	{
		stop_heart_beat_led = true;
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		count_led_status2 = 0;
	}
}

void Status_Led()
{
	switch (status_led_state)
	{
	case INIT_STATUS_LED:
	{
		status_led_state = IDLE_STATUS_LED;
		led2_status = IDLESTAT;
		break;
	}
	case IDLE_STATUS_LED:
	{
		if (led2_status == BTN_PRESSED1)
			status_led_state = BUTTON_PRESSED_LED_3;
		else if (led2_status == LEARN_STATUS_LED)
			status_led_state = LEARNLED;
		else if (led2_status == LEARN_STATUS_LED2)
			status_led_state = LEARNLED3;
		else if (led2_status == BTN_PRESSED2)
			status_led_state = BUTTON_PRESSED_LED_1;
		break;
	}
	case LOAD_USB_LED:
	{

		break;
	}
	case LEARNLED:
	{
		led2_status = IDLESTAT;
		timestamp_status_led = HAL_GetTick();
		status_led_state = LEARNLED2;
		break;
	}
	case LEARNLED2:
	{
		if ((HAL_GetTick() - timestamp_status_led) >= 100)
		{
			count_led_status++;
			timestamp_status_led = HAL_GetTick();
			HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		}
		if (count_led_status == 300)
		{
			status_led_state = IDLE_STATUS_LED;
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
			count_led_status = 0;
		}
		break;
		break;
	}
	case LEARNLED3:
	{
		led2_status = IDLESTAT;
		timestamp_status_led = HAL_GetTick();
		status_led_state = LEARNLED4;
		break;
	}
	case LEARNLED4:
	{
		if ((HAL_GetTick() - timestamp_status_led) >= 100)
		{
			count_led_status++;
			timestamp_status_led = HAL_GetTick();
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		}
		if (count_led_status == 300)
		{
			status_led_state = IDLE_STATUS_LED;
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
			count_led_status = 0;
		}

		break;
	}
	case BUTTON_PRESSED_LED_1:
		led2_status = IDLESTAT;
		timestamp_status_led = HAL_GetTick();
		status_led_state = BUTTON_PRESSED_LED_2;
		break;
	case BUTTON_PRESSED_LED_2:
	{
		if ((HAL_GetTick() - timestamp_status_led) >= 100)
		{
			count_led_status++;
			timestamp_status_led = HAL_GetTick();
			HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		}
		if (count_led_status == 20)
		{
			status_led_state = IDLE_STATUS_LED;
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
			count_led_status = 0;
		}
		break;
	}
	case BUTTON_PRESSED_LED_3:
		led2_status = IDLESTAT;
		timestamp_status_led = HAL_GetTick();
		status_led_state = BUTTON_PRESSED_LED_4;
		break;
	case BUTTON_PRESSED_LED_4:
	{
		if ((HAL_GetTick() - timestamp_status_led) >= 100)
		{
			count_led_status++;
			timestamp_status_led = HAL_GetTick();
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		}
		if (count_led_status == 20)
		{
			status_led_state = IDLE_STATUS_LED;
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
			count_led_status = 0;
		}
		break;
	}
	default:
		status_led_state = INIT_STATUS_LED;
	}
}

void Calculate_Temperatures_Offsets()
{

	dechundred = (pcb_config.sSetTempTreshMax[0] - '0') * 100;
	decten = (pcb_config.sSetTempTreshMax[1] - '0') * 10;
	dec = (pcb_config.sSetTempTreshMax[2] - '0');

	temp_max = dechundred + decten + dec;

	dechundred_min = (pcb_config.sSetTempTreshMin[0] - '0') * 100;
	decten_min = (pcb_config.sSetTempTreshMin[1] - '0') * 10;
	dec_min = (pcb_config.sSetTempTreshMin[2] - '0');

	temp_min = dechundred_min + decten_min + dec_min;

	temperature_max_treshold = (float)(temp_max) / 10;
	temperature_min_treshold = (float)(temp_min) / 10;

	// Send_Temperature_Data(temperature_max_treshold);
}

void WriteToEeprom()
{
	uint8_t buffercopy[sizeof(pcb_config)];

	// Write the default config into the eeprom
	memcpy(buffercopy, &pcb_config, sizeof(pcb_config));
	for (unsigned int i = 0; i < 255; i++)
	{
		HAL_I2C_Mem_Write(&hi2c1, EEPROM_C24_ADDR_WRITE, i, 1, &buffercopy[i], 1, 1000);
		HAL_Delay(15);
	}
	for (unsigned int i = 0; i < (sizeof(pcb_config) - 255); i++)
	{
		HAL_I2C_Mem_Write(&hi2c1, (EEPROM_C24_ADDR_WRITE + 2), i, 1, &buffercopy[i + 255], 1, 1000);
		HAL_Delay(15);
	}
	HAL_Delay(50);

	tv_type = pcb_config.tvtype[0] - '0';
	struct PCB_Config copy_config;
	memcpy(&copy_config, &pcb_config, sizeof(pcb_config));
	switch (tv_type)
	{

	case 0: // LG
	case 1: // Samsung

	default:
		to_hex(copy_config.sSetIR, 0);
		for (int i = 0; i < 4; i++)
			copy_config.sSetIR[i] = copy_config.sSetIR[2 * i + 1];
		to_hex(copy_config.sSetIROFF, 0);
		for (int i = 0; i < 4; i++)
			copy_config.sSetIROFF[i] = copy_config.sSetIROFF[2 * i + 1];

		code_ON[0] = ((uint64_t)(copy_config.sSetIR[0]) << 24) + ((uint64_t)(copy_config.sSetIR[1]) << 16) + ((uint64_t)(copy_config.sSetIR[2]) << 8) + (uint64_t)(copy_config.sSetIR[3]); // full_ir_code_from_db;//
		code_OFF[0] = ((uint64_t)(copy_config.sSetIROFF[0]) << 24) + ((uint64_t)(copy_config.sSetIROFF[1]) << 16) + ((uint64_t)(copy_config.sSetIROFF[2]) << 8) + (uint64_t)(copy_config.sSetIROFF[3]);
		break;

	case 2: // PANASONIC
		to_hex(copy_config.sSetIR, 0);
		for (int i = 0; i < 6; i++)
			copy_config.sSetIR[i] = copy_config.sSetIR[2 * i + 1];
		to_hex(copy_config.sSetIROFF, 0);
		for (int i = 0; i < 6; i++)
			copy_config.sSetIROFF[i] = copy_config.sSetIROFF[2 * i + 1];

		code_ON[0] = ((uint64_t)(copy_config.sSetIR[0]) << 40) + ((uint64_t)(copy_config.sSetIR[1]) << 32) + ((uint64_t)(copy_config.sSetIR[2]) << 24) + ((uint64_t)(copy_config.sSetIR[3]) << 16) + ((uint64_t)(copy_config.sSetIR[4]) << 8) + (uint64_t)(copy_config.sSetIR[5]); // full_ir_code_from_db;//
		code_OFF[0] = ((uint64_t)(copy_config.sSetIROFF[0]) << 40) + ((uint64_t)(copy_config.sSetIROFF[1]) << 32) + ((uint64_t)(copy_config.sSetIROFF[2]) << 24) + ((uint64_t)(copy_config.sSetIROFF[3]) << 16) + ((uint64_t)(copy_config.sSetIROFF[4]) << 8) + (uint64_t)(copy_config.sSetIROFF[5]);
		break;
	case 3: // SONY12
	case 6: // SHARP
	case 4: // RC5
	case 5:
		to_hex(copy_config.sSetIR, 0);
		for (int i = 0; i < 2; i++)
			copy_config.sSetIR[i] = copy_config.sSetIR[2 * i + 1];
		to_hex(copy_config.sSetIROFF, 0);
		for (int i = 0; i < 2; i++)
			copy_config.sSetIROFF[i] = copy_config.sSetIROFF[2 * i + 1];

		code_ON[0] = ((uint16_t)((uint32_t)(copy_config.sSetIR[0]) << 8) + copy_config.sSetIR[1]); // full_ir_code_from_db;//
		code_OFF[0] = ((uint16_t)((uint32_t)(copy_config.sSetIROFF[0]) << 8) + copy_config.sSetIROFF[1]);

		break;
	}
}

void ReadAndSetConfig()
{
	vptr_test = &pcb_config;
	uint8_t buffer[400];
	uint8_t buffer2[400];
	//	  // Read the config
	//	  for( int j = 0; j < 18; j++ ) //0 to page 18
	//	  {
	//		  HAL_I2C_Mem_Read (&hi2c1, EEPROM_C24_ADDR_READ, (j<<4), 1, &buffer2[16*j], 16, 1000); //read 16 bytes * 18 pages  = 288 bytes
	//		  HAL_Delay(50);
	//	  }

	// Read the config
	for (int j = 0; j < 255; j++)
	{
		HAL_I2C_Mem_Read(&hi2c1, EEPROM_C24_ADDR_READ, j, 1, &buffer2[j], 1, 1000);
		HAL_Delay(15);
	}
	for (int j = 0; j < (sizeof(pcb_config) - 255); j++)
	{
		HAL_I2C_Mem_Read(&hi2c1, (EEPROM_C24_ADDR_READ + 2), j, 1, &buffer2[j + 255], 1, 1000);
		HAL_Delay(15);
	}
	memcpy(&pcb_config_read, &buffer2, sizeof(pcb_config));
	HAL_Delay(20);

	// If we have never written default params, write default params, else do nothing and get params from eeprom
	if (pcb_config_read.MagicNumber[2] != MAGIC)
	{
		// Write the default config into the eeprom
		memcpy(buffer, vptr_test, sizeof(pcb_config));

		// HAL_I2C_Mem_Write(&hi2c1, EEPROM_C24_ADDR_WRITE, 0x0, 1, &buffer[0], 1, 1000);
		// HAL_I2C_Mem_Write(&hi2c1, EEPROM_C24_ADDR_WRITE, 0x1, 1, &buffer[1], 1, 1000);
		for (int i = 0; i < 255; i++)
		{
			HAL_I2C_Mem_Write(&hi2c1, EEPROM_C24_ADDR_WRITE, i, 1, &buffer[i], 1, 1000);
			HAL_Delay(15);
		}
		for (int i = 0; i < (sizeof(pcb_config) - 255); i++)
		{
			HAL_I2C_Mem_Write(&hi2c1, (EEPROM_C24_ADDR_WRITE + 2), i, 1, &buffer[i + 255], 1, 1000);
			HAL_Delay(15);
		}

		// Read the config
		for (int j = 0; j < 255; j++)
		{
			HAL_I2C_Mem_Read(&hi2c1, EEPROM_C24_ADDR_READ, j, 1, &buffer2[j], 1, 1000);
			HAL_Delay(15);
		}
		for (int j = 0; j < (sizeof(pcb_config) - 255); j++)
		{
			HAL_I2C_Mem_Read(&hi2c1, (EEPROM_C24_ADDR_READ + 2), j, 1, &buffer2[j + 255], 1, 1000);
			HAL_Delay(15);
		}
		//			  for( int j = 0; j < 18; j++ ) //0 to page 18
		//			  {
		//				  HAL_I2C_Mem_Write(&hi2c1, EEPROM_C24_ADDR_WRITE, (j<<4), 1, &buffer[16*j], 16, 1000); //read 16 bytes * 18 pages  = 288 bytes
		//				  HAL_Delay(50);
		//			  }
		//			  HAL_Delay(50);
		//
		//			  // Read the config
		//				  for( int j = 0; j < 18; j++ ) //0 to page 18
		//				  {
		//					  HAL_I2C_Mem_Read (&hi2c1, EEPROM_C24_ADDR_READ, (j<<4), 1, &buffer2[16*j], 16, 1000); //read 16 bytes * 18 pages  = 288 bytes
		//					  HAL_Delay(50);
		//				  }

		memcpy(&pcb_config_read, &buffer2, sizeof(pcb_config));
	}
	else

		memcpy(&pcb_config, &pcb_config_read, sizeof(pcb_config));

	tv_type = pcb_config.tvtype[0] - '0';
	struct PCB_Config copy_config;
	memcpy(&copy_config, &pcb_config, sizeof(pcb_config));
	switch (tv_type)
	{

	case 0: // LG
	case 1: // Samsung
	case 4: // RC5
	case 5:
	case 6:
	default:
		to_hex(copy_config.sSetIR, 0);
		for (int i = 0; i < 4; i++)
			copy_config.sSetIR[i] = copy_config.sSetIR[2 * i + 1];
		to_hex(copy_config.sSetIROFF, 0);
		for (int i = 0; i < 4; i++)
			copy_config.sSetIROFF[i] = copy_config.sSetIROFF[2 * i + 1];

		code_ON[0] = ((uint32_t)(copy_config.sSetIR[0]) << 24) + ((uint32_t)(copy_config.sSetIR[1]) << 16) + ((uint32_t)(copy_config.sSetIR[2]) << 8) + copy_config.sSetIR[3]; // full_ir_code_from_db;//
		code_OFF[0] = ((uint32_t)(copy_config.sSetIROFF[0]) << 24) + ((uint32_t)(copy_config.sSetIROFF[1]) << 16) + ((uint32_t)(copy_config.sSetIROFF[2]) << 8) + copy_config.sSetIROFF[3];
		break;

	case 2: // PANASONIC
		to_hex(copy_config.sSetIR, 0);
		for (int i = 0; i < 6; i++)
			copy_config.sSetIR[i] = copy_config.sSetIR[2 * i + 1];
		to_hex(copy_config.sSetIROFF, 0);
		for (int i = 0; i < 6; i++)
			copy_config.sSetIROFF[i] = copy_config.sSetIROFF[2 * i + 1];

		code_ON[0] = ((uint64_t)(copy_config.sSetIR[0]) << 40) + ((uint64_t)(copy_config.sSetIR[1]) << 32) + ((uint64_t)(copy_config.sSetIR[2]) << 24) + ((uint64_t)(copy_config.sSetIR[3]) << 16) + ((uint64_t)(copy_config.sSetIR[4]) << 8) + copy_config.sSetIR[5]; // full_ir_code_from_db;//
		code_OFF[0] = ((uint64_t)(copy_config.sSetIROFF[0]) << 40) + ((uint64_t)(copy_config.sSetIROFF[1]) << 32) + ((uint64_t)(copy_config.sSetIROFF[2]) << 24) + ((uint64_t)(copy_config.sSetIROFF[3]) << 16) + ((uint64_t)(copy_config.sSetIROFF[4]) << 8) + copy_config.sSetIROFF[5];
		break;
	case 3: // SONY12
		to_hex(copy_config.sSetIR, 0);
		for (int i = 0; i < 3; i++)
			copy_config.sSetIR[i] = copy_config.sSetIR[2 * i + 1];
		to_hex(copy_config.sSetIROFF, 0);
		for (int i = 0; i < 3; i++)
			copy_config.sSetIROFF[i] = copy_config.sSetIROFF[2 * i + 1];

		code_ON[0] = ((uint16_t)(copy_config.sSetIR[0]) << 16) + ((uint32_t)(copy_config.sSetIR[1]) << 8) + copy_config.sSetIR[2]; // full_ir_code_from_db;//
		code_OFF[0] = ((uint16_t)(copy_config.sSetIROFF[0]) << 16) + ((uint32_t)(copy_config.sSetIROFF[1]) << 8) + copy_config.sSetIROFF[2];

		break;
	}

	loopon = pcb_config.loopon;
	loopoff = pcb_config.loopoff;
	looptime = pcb_config.looptime;

	memcpy(&gWIZNETINFO.mac, &pcb_config.mac, 6);
	memcpy(&gWIZNETINFO.dns, &pcb_config.dns, 4);
	memcpy(&gWIZNETINFO.gw, &pcb_config.gw, 4);
	memcpy(&gWIZNETINFO.ip, &pcb_config.ip, 4);
	memcpy(&gWIZNETINFO.sn, &pcb_config.sn, 4);
	memcpy(&gWIZNETINFO.dhcp, &pcb_config.dhcp, 1);

	onSwitch = pcb_config.pcb_config_onSwitch;
	onDateTime = pcb_config.pcb_config_onDateTime;
	offSwitch = pcb_config.pcb_config_offSwitch;
	offDateTime = pcb_config.pcb_config_offDateTime;
	timezone = pcb_config.pcb_config_timezone;

	time_alarm_on_hh = pcb_config.pcb_config_time_alarm_on_hh;
	time_alarm_on_mm = pcb_config.pcb_config_time_alarm_on_mm;
	time_alarm_off_hh = pcb_config.pcb_config_time_alarm_off_hh;
	time_alarm_off_mm = pcb_config.pcb_config_time_alarm_off_mm;

	memcpy(Recursion_Alarm_ON, pcb_config.pcb_config_Recursion_Alarm_ON, sizeof(Recursion_Alarm_ON));
	memcpy(Recursion_Alarm_OFF, pcb_config.pcb_config_Recursion_Alarm_OFF, sizeof(Recursion_Alarm_OFF));

	time_alarm_on_sun = Recursion_Alarm_ON[0];
	time_alarm_on_mon = Recursion_Alarm_ON[1];
	time_alarm_on_tue = Recursion_Alarm_ON[2];
	time_alarm_on_wed = Recursion_Alarm_ON[3];
	time_alarm_on_thu = Recursion_Alarm_ON[4];
	time_alarm_on_fri = Recursion_Alarm_ON[5];
	time_alarm_on_sat = Recursion_Alarm_ON[6];

	time_alarm_off_sun = Recursion_Alarm_OFF[0];
	time_alarm_off_mon = Recursion_Alarm_OFF[1];
	time_alarm_off_tue = Recursion_Alarm_OFF[2];
	time_alarm_off_wed = Recursion_Alarm_OFF[3];
	time_alarm_off_thu = Recursion_Alarm_OFF[4];
	time_alarm_off_fri = Recursion_Alarm_OFF[5];
	time_alarm_off_sat = Recursion_Alarm_OFF[6];
}

void Send(uint8_t data)
{
	HAL_UART_Transmit(&huart1, &data, 1, 100);
}
uint8_t Receive(void)
{
	uint16_t data;
	HAL_UART_Receive(&huart1, (uint8_t*)&data, 2, 1000);
	return data;
}

T_u_int32 reverse_bits_test(T_u_int32 inval, int bits)
{
	if (bits > 0)
	{
		bits--;
		return reverse_bits_test(inval >> 1, bits) | ((inval & 1) << bits);
	}
	return 0;
}
void GetDeviceCodeNEC()
{
	//	device = reverse_bits_test(234, 8);
	//	subdevice = reverse_bits_test(199, 8);.

	//	function_code = reverse_bits_test(23, 8);
	//
	//	device = reverse_bits_test(134, 8);
	//		subdevice = reverse_bits_test(5, 8);
	//		function_code = reverse_bits_test(15, 8);
	//
	//	function_code_ff = 0xff - function_code;
	//
	//	full_ir_code_from_db = (uint32_t) (device << 24)
	//			+ (uint32_t) (subdevice << 16) + (uint32_t) (function_code << 8)
	//			+ function_code_ff;
	//
	//	uint64_t code48;
	//	const uint16_t manufacturer = 0x4004;
	//	const uint8_t device = 128;
	//	const uint8_t subdevice = 0;
	//	const uint8_t function = 61;
	//	uint8_t checksum = device ^ subdevice ^ function;
	//	code48 = (((uint64_t) manufacturer << 32) | ((uint64_t) device << 24)
	//			| ((uint64_t) subdevice << 16) | ((uint64_t) function << 8)
	//			| checksum);
	//	code_ON[0] = code48;
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
