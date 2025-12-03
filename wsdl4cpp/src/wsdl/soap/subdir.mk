################################################################################
SUB_DIR := wsdl/soap

# Add inputs and outputs from these tool invocations to the build variables 
SRC_LIST := \
SOAPAddressSerializer.cpp \
SOAPBindingSerializer.cpp \
SOAPBodySerializer.cpp \
SOAPConstants.cpp \
SOAPElement.cpp \
SOAPFaultSerializer.cpp \
SOAPHeaderSerializer.cpp \
SOAPOperationSerializer.cpp \
SOAPSerializerUtils.cpp \


CPP_SRCS += ${addprefix $(SRC_DIR)/$(SUB_DIR)/, $(SRC_LIST)}

OBJ_LIST := $(SRC_LIST:.cpp=.o)
OBJS += ${addprefix $(OBJ_DIR)/, $(OBJ_LIST)}

DEP_LIST := $(SRC_LIST:.cpp=.d)
DEPS += ${addprefix $(OBJ_DIR)/, $(DEP_LIST)}

# Each subdirectory must supply rules for building sources it contributes
$(OBJ_DIR)/%.o: $(SRC_DIR)/$(SUB_DIR)/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	@echo g++ $(COMPILE_OPTS) -o$@ $<
	@g++ $(COMPILE_OPTS) -o$@ $< && \
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	g++ $(DEP_OPTS) $< >> $(@:%.o=%.d)
	@echo 'Finished building: $<'
	@echo ' '


