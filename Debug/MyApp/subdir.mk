################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MyApp/Ch376msc.cpp \
../MyApp/MyApp.cpp \
../MyApp/SetGet.cpp \
../MyApp/comm.cpp 

OBJS += \
./MyApp/Ch376msc.o \
./MyApp/MyApp.o \
./MyApp/SetGet.o \
./MyApp/comm.o 

CPP_DEPS += \
./MyApp/Ch376msc.d \
./MyApp/MyApp.d \
./MyApp/SetGet.d \
./MyApp/comm.d 


# Each subdirectory must supply rules for building sources it contributes
MyApp/%.o MyApp/%.su MyApp/%.cyclo: ../MyApp/%.cpp MyApp/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0B0xx -c -I../Core/Inc -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/MyApp" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Internet/SNTP" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Application/loopback" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Internet/httpServer" -I"C:/Users/Camille Chevrier/Desktop/WORKING FOLDER/STM32CudeIDE_Projects/ioLibrary_Driver/Ethernet" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MyApp

clean-MyApp:
	-$(RM) ./MyApp/Ch376msc.cyclo ./MyApp/Ch376msc.d ./MyApp/Ch376msc.o ./MyApp/Ch376msc.su ./MyApp/MyApp.cyclo ./MyApp/MyApp.d ./MyApp/MyApp.o ./MyApp/MyApp.su ./MyApp/SetGet.cyclo ./MyApp/SetGet.d ./MyApp/SetGet.o ./MyApp/SetGet.su ./MyApp/comm.cyclo ./MyApp/comm.d ./MyApp/comm.o ./MyApp/comm.su

.PHONY: clean-MyApp

