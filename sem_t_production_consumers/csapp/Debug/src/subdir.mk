################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/csapp.c \
../src/echo_cnt.c \
../src/main.c \
../src/sbuf.c 

OBJS += \
./src/csapp.o \
./src/echo_cnt.o \
./src/main.o \
./src/sbuf.o 

C_DEPS += \
./src/csapp.d \
./src/echo_cnt.d \
./src/main.d \
./src/sbuf.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/home/lizhen/workspace/csapp/Debug/pthread -O0 -g3 -Wall -c -fmessage-length=0 -lpthread -lrt -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


