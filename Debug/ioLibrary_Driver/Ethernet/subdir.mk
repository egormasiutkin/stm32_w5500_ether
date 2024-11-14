################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Ethernet/dhcp.c \
../ioLibrary_Driver/Ethernet/socket.c \
../ioLibrary_Driver/Ethernet/wizchip_conf.c 

C_DEPS += \
./ioLibrary_Driver/Ethernet/dhcp.d \
./ioLibrary_Driver/Ethernet/socket.d \
./ioLibrary_Driver/Ethernet/wizchip_conf.d 

OBJS += \
./ioLibrary_Driver/Ethernet/dhcp.o \
./ioLibrary_Driver/Ethernet/socket.o \
./ioLibrary_Driver/Ethernet/wizchip_conf.o 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Ethernet/%.o ioLibrary_Driver/Ethernet/%.su ioLibrary_Driver/Ethernet/%.cyclo: ../ioLibrary_Driver/Ethernet/%.c ioLibrary_Driver/Ethernet/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0B0xx -c -I../Core/Inc -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/MyApp" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Internet/SNTP" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Application/loopback" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Internet/httpServer" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Ethernet" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ioLibrary_Driver-2f-Ethernet

clean-ioLibrary_Driver-2f-Ethernet:
	-$(RM) ./ioLibrary_Driver/Ethernet/dhcp.cyclo ./ioLibrary_Driver/Ethernet/dhcp.d ./ioLibrary_Driver/Ethernet/dhcp.o ./ioLibrary_Driver/Ethernet/dhcp.su ./ioLibrary_Driver/Ethernet/socket.cyclo ./ioLibrary_Driver/Ethernet/socket.d ./ioLibrary_Driver/Ethernet/socket.o ./ioLibrary_Driver/Ethernet/socket.su ./ioLibrary_Driver/Ethernet/wizchip_conf.cyclo ./ioLibrary_Driver/Ethernet/wizchip_conf.d ./ioLibrary_Driver/Ethernet/wizchip_conf.o ./ioLibrary_Driver/Ethernet/wizchip_conf.su

.PHONY: clean-ioLibrary_Driver-2f-Ethernet

