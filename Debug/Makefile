################################################################################
# Automatically-generated file. Do not edit!
################################################################################

RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.cpp \
../usbl.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o \
usbl.o

OBJS_AS_ARGS +=  \
main.o \
usbl.o

C_DEPS +=  \
main.d \
usbl.d

C_DEPS_AS_ARGS +=  \
main.d \
usbl.d

OUTPUT_FILE_PATH +=USBMassStorageAVRUSB.elf

OUTPUT_FILE_PATH_AS_ARGS +=USBMassStorageAVRUSB.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= 

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./main.o: .././main.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 5.4.0
	avr-g++ -std=gnu++17 -funsigned-char -funsigned-bitfields -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=at90usb162 -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<


./usbl.o: .././usbl.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 5.4.0
	avr-g++ -std=gnu++17 -funsigned-char -funsigned-bitfields -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=at90usb162 -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<





# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 5.4.0
	avr-g++ -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="USBMassStorageAVRUSB.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=at90usb162 
	@echo Finished building target: $@
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "USBMassStorageAVRUSB.elf" "USBMassStorageAVRUSB.hex"
	avr-objcopy -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "USBMassStorageAVRUSB.elf" "USBMassStorageAVRUSB.eep" || exit 0
	avr-objdump -h -S "USBMassStorageAVRUSB.elf" > "USBMassStorageAVRUSB.lss"
	avr-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "USBMassStorageAVRUSB.elf" "USBMassStorageAVRUSB.srec"
	avr-size "USBMassStorageAVRUSB.elf"







# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)
	-$(RM) $(C_DEPS_AS_ARGS)
	rm -rf "USBMassStorageAVRUSB.elf" "USBMassStorageAVRUSB.a" "USBMassStorageAVRUSB.hex" "USBMassStorageAVRUSB.lss" "USBMassStorageAVRUSB.eep" "USBMassStorageAVRUSB.map" "USBMassStorageAVRUSB.srec" "USBMassStorageAVRUSB.usersignatures"

