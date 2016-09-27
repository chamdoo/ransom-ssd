################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../csv.c \
../detect.c \
../io.c \
../main.c \
../sec.c \
../util.c 

OBJS += \
./csv.o \
./detect.o \
./io.o \
./main.o \
./sec.o \
./util.o 

C_DEPS += \
./csv.d \
./detect.d \
./io.d \
./main.d \
./sec.d \
./util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


