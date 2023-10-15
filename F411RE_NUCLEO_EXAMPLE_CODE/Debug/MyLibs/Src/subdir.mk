################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MyLibs/Src/software_timer.c 

OBJS += \
./MyLibs/Src/software_timer.o 

C_DEPS += \
./MyLibs/Src/software_timer.d 


# Each subdirectory must supply rules for building sources it contributes
MyLibs/Src/%.o MyLibs/Src/%.su: ../MyLibs/Src/%.c MyLibs/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"C:/Users/seakdogan/Desktop/Software Timer on STM32/F411RE_NUCLEO_EXAMPLE_CODE/MyLibs/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MyLibs-2f-Src

clean-MyLibs-2f-Src:
	-$(RM) ./MyLibs/Src/software_timer.d ./MyLibs/Src/software_timer.o ./MyLibs/Src/software_timer.su

.PHONY: clean-MyLibs-2f-Src

