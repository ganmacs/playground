CXX = g++
CXXFLAGS = -std=c++14 -stdlib=libc++
CFLAGS = -MMD -MP -Wall -g -fsanitize=address -fno-omit-frame-pointer
LIBS = -L/opt/brew/Cellar/libevent/2.1.8/lib -levent -L/opt/brew/Cellar/nghttp2/1.32.0/lib -lnghttp2  -L/opt/brew/Cellar/protobuf/3.6.0/lib -lprotobuf

INC_DIRS := /opt/brew/include /opt/brew/Cellar/protobuf/3.6.0/include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

TARGET = server
SRCS := $(shell find . -name '*.cc')
OBJS := $(SRCS:%.cc=%.o)
DEPS := $(SRCS:%.cc=%.d)

$(TARGET): $(OBJS)
		$(CXX) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

.cc.o:
		$(CXX) $(CFLAGS) $(CXXFLAGS) $(INC_FLAGS) -c $<

.PHONY: clean all

clean:
		$(RM) $(TARGET) $(OBJS) $(DEPS)

all: clean $(TARGET)

-include $(DEPS)
