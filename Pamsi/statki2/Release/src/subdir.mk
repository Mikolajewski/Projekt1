################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/gracz.cpp \
../src/main.cpp \
../src/statek.cpp 

OBJS += \
./src/gracz.o \
./src/main.o \
./src/statek.o 

CPP_DEPS += \
./src/gracz.d \
./src/main.d \
./src/statek.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\Users\Tomek\workspace\statki\inc" -I"C:\Users\Tomek\workspace\SFML-2.0\include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


