################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Internet/httpServer/httpParser.c \
../ioLibrary_Driver/Internet/httpServer/httpServer.c \
../ioLibrary_Driver/Internet/httpServer/httpUtil.c 

C_DEPS += \
./ioLibrary_Driver/Internet/httpServer/httpParser.d \
./ioLibrary_Driver/Internet/httpServer/httpServer.d \
./ioLibrary_Driver/Internet/httpServer/httpUtil.d 

OBJS += \
./ioLibrary_Driver/Internet/httpServer/httpParser.o \
./ioLibrary_Driver/Internet/httpServer/httpServer.o \
./ioLibrary_Driver/Internet/httpServer/httpUtil.o 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Internet/httpServer/%.o ioLibrary_Driver/Internet/httpServer/%.su ioLibrary_Driver/Internet/httpServer/%.cyclo: ../ioLibrary_Driver/Internet/httpServer/%.c ioLibrary_Driver/Internet/httpServer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0B0xx -c -I../Core/Inc -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/MyApp" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Internet/SNTP" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Application/loopback" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Internet/httpServer" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Ethernet" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ioLibrary_Driver-2f-Internet-2f-httpServer

clean-ioLibrary_Driver-2f-Internet-2f-httpServer:
	-$(RM) ./ioLibrary_Driver/Internet/httpServer/httpParser.cyclo ./ioLibrary_Driver/Internet/httpServer/httpParser.d ./ioLibrary_Driver/Internet/httpServer/httpParser.o ./ioLibrary_Driver/Internet/httpServer/httpParser.su ./ioLibrary_Driver/Internet/httpServer/httpServer.cyclo ./ioLibrary_Driver/Internet/httpServer/httpServer.d ./ioLibrary_Driver/Internet/httpServer/httpServer.o ./ioLibrary_Driver/Internet/httpServer/httpServer.su ./ioLibrary_Driver/Internet/httpServer/httpUtil.cyclo ./ioLibrary_Driver/Internet/httpServer/httpUtil.d ./ioLibrary_Driver/Internet/httpServer/httpUtil.o ./ioLibrary_Driver/Internet/httpServer/httpUtil.su

.PHONY: clean-ioLibrary_Driver-2f-Internet-2f-httpServer

