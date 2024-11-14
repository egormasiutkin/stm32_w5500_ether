################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/APP_Web.c \
../Core/Src/Infrared.c \
../Core/Src/Protocol.c \
../Core/Src/buttons.c \
../Core/Src/loop.c \
../Core/Src/main.c \
../Core/Src/motion_detect.c \
../Core/Src/pcb_config.c \
../Core/Src/stm32g0xx_hal_msp.c \
../Core/Src/stm32g0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g0xx.c \
../Core/Src/usart.c \
../Core/Src/userHandler.c \
../Core/Src/w5500_init.c \
../Core/Src/webpage.c 

C_DEPS += \
./Core/Src/APP_Web.d \
./Core/Src/Infrared.d \
./Core/Src/Protocol.d \
./Core/Src/buttons.d \
./Core/Src/loop.d \
./Core/Src/main.d \
./Core/Src/motion_detect.d \
./Core/Src/pcb_config.d \
./Core/Src/stm32g0xx_hal_msp.d \
./Core/Src/stm32g0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g0xx.d \
./Core/Src/usart.d \
./Core/Src/userHandler.d \
./Core/Src/w5500_init.d \
./Core/Src/webpage.d 

OBJS += \
./Core/Src/APP_Web.o \
./Core/Src/Infrared.o \
./Core/Src/Protocol.o \
./Core/Src/buttons.o \
./Core/Src/loop.o \
./Core/Src/main.o \
./Core/Src/motion_detect.o \
./Core/Src/pcb_config.o \
./Core/Src/stm32g0xx_hal_msp.o \
./Core/Src/stm32g0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g0xx.o \
./Core/Src/usart.o \
./Core/Src/userHandler.o \
./Core/Src/w5500_init.o \
./Core/Src/webpage.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0B0xx -c -I../Core/Inc -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/MyApp" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Internet/SNTP" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Application/loopback" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Internet/httpServer" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Ethernet" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/APP_Web.cyclo ./Core/Src/APP_Web.d ./Core/Src/APP_Web.o ./Core/Src/APP_Web.su ./Core/Src/Infrared.cyclo ./Core/Src/Infrared.d ./Core/Src/Infrared.o ./Core/Src/Infrared.su ./Core/Src/Protocol.cyclo ./Core/Src/Protocol.d ./Core/Src/Protocol.o ./Core/Src/Protocol.su ./Core/Src/buttons.cyclo ./Core/Src/buttons.d ./Core/Src/buttons.o ./Core/Src/buttons.su ./Core/Src/loop.cyclo ./Core/Src/loop.d ./Core/Src/loop.o ./Core/Src/loop.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motion_detect.cyclo ./Core/Src/motion_detect.d ./Core/Src/motion_detect.o ./Core/Src/motion_detect.su ./Core/Src/pcb_config.cyclo ./Core/Src/pcb_config.d ./Core/Src/pcb_config.o ./Core/Src/pcb_config.su ./Core/Src/stm32g0xx_hal_msp.cyclo ./Core/Src/stm32g0xx_hal_msp.d ./Core/Src/stm32g0xx_hal_msp.o ./Core/Src/stm32g0xx_hal_msp.su ./Core/Src/stm32g0xx_it.cyclo ./Core/Src/stm32g0xx_it.d ./Core/Src/stm32g0xx_it.o ./Core/Src/stm32g0xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g0xx.cyclo ./Core/Src/system_stm32g0xx.d ./Core/Src/system_stm32g0xx.o ./Core/Src/system_stm32g0xx.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/userHandler.cyclo ./Core/Src/userHandler.d ./Core/Src/userHandler.o ./Core/Src/userHandler.su ./Core/Src/w5500_init.cyclo ./Core/Src/w5500_init.d ./Core/Src/w5500_init.o ./Core/Src/w5500_init.su ./Core/Src/webpage.cyclo ./Core/Src/webpage.d ./Core/Src/webpage.o ./Core/Src/webpage.su

.PHONY: clean-Core-2f-Src

