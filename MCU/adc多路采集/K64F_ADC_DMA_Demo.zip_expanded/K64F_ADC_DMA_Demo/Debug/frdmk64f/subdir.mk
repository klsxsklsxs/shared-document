################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../frdmk64f/board.c \
../frdmk64f/clock_config.c \
../frdmk64f/pin_mux.c 

OBJS += \
./frdmk64f/board.o \
./frdmk64f/clock_config.o \
./frdmk64f/pin_mux.o 

C_DEPS += \
./frdmk64f/board.d \
./frdmk64f/clock_config.d \
./frdmk64f/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
frdmk64f/%.o: ../frdmk64f/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCPU_MK64FN1M0VDC12 -DCPU_MK64FN1M0VDC12_cm4 -D__REDLIB__ -I"C:\Users\nxf56274\Documents\MCUXpressoIDE_11.2.0_4095_prc2\workspace\K64F_ADC_DMA_Demo.zip_expanded\K64F_ADC_DMA_Demo\source" -I"C:\Users\nxf56274\Documents\MCUXpressoIDE_11.2.0_4095_prc2\workspace\K64F_ADC_DMA_Demo.zip_expanded\K64F_ADC_DMA_Demo" -I"C:\Users\nxf56274\Documents\MCUXpressoIDE_11.2.0_4095_prc2\workspace\K64F_ADC_DMA_Demo.zip_expanded\K64F_ADC_DMA_Demo\frdmk64f" -I"C:\Users\nxf56274\Documents\MCUXpressoIDE_11.2.0_4095_prc2\workspace\K64F_ADC_DMA_Demo.zip_expanded\K64F_ADC_DMA_Demo\drivers" -I"C:\Users\nxf56274\Documents\MCUXpressoIDE_11.2.0_4095_prc2\workspace\K64F_ADC_DMA_Demo.zip_expanded\K64F_ADC_DMA_Demo\startup" -I"C:\Users\nxf56274\Documents\MCUXpressoIDE_11.2.0_4095_prc2\workspace\K64F_ADC_DMA_Demo.zip_expanded\K64F_ADC_DMA_Demo\utilities" -I"C:\Users\nxf56274\Documents\MCUXpressoIDE_11.2.0_4095_prc2\workspace\K64F_ADC_DMA_Demo.zip_expanded\K64F_ADC_DMA_Demo\CMSIS" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


