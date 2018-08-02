################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Wezel.cpp \
../komputer.cpp \
../main.cpp \
../partia.cpp \
../pionek.cpp \
../plansza.cpp \
../pole.cpp \
../zawodnik.cpp 

OBJS += \
./Wezel.o \
./komputer.o \
./main.o \
./partia.o \
./pionek.o \
./plansza.o \
./pole.o \
./zawodnik.o 

CPP_DEPS += \
./Wezel.d \
./komputer.d \
./main.d \
./partia.d \
./pionek.d \
./plansza.d \
./pole.d \
./zawodnik.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\MinGW\include\allegro" -I"C:\MinGW\include" -O3 -Wall -Werror -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


