SRC_DIR := ./src
INC_DIRS := ./inc
BUILD_DIR := ./build

INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := -std=c++11 -g $(INC_FLAGS) -O2 -MMD -MP

SRCS := $(shell cd $(SRC_DIR); find . -name "*.cpp")
OBJS := $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(SRCS)))
DEPS := $(OBJS:.o=.d)

main: $(OBJS)
	g++ $(CPPFLAGS) $(OBJS) -o $@;

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -r $(BUILD_DIR)

.PHONY: clean all

-include $(DEPS)
