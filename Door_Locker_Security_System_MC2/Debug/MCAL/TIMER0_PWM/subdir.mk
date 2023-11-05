################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/TIMER0_PWM/timer0_pwm.c 

OBJS += \
./MCAL/TIMER0_PWM/timer0_pwm.o 

C_DEPS += \
./MCAL/TIMER0_PWM/timer0_pwm.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/TIMER0_PWM/%.o: ../MCAL/TIMER0_PWM/%.c MCAL/TIMER0_PWM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


