CXX = g++
CXXFLAGS = -std=c++11 -stdlib=libc++
CFLAGS = -MMD -MP -Wall
LIBS = -L/opt/brew/Cellar/libevent/2.1.8/lib/ -levent -L/opt/brew/Cellar/nghttp2/1.32.0/lib -lnghttp2
INCLUDE = -I/opt/brew/include

TARGET = server
SRCS := main.cc
OBJS = $(addsuffix .o, $(basename $(SRCS)))
DEPS := $(SRCS:%.cc=%.d)

$(TARGET): $(OBJS)
		$(CXX) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJS): $(SRCS)
		$(CXX) $(CFLAGS) $(CXXFLAGS) -c $^ $(INCLUDE)

.PHONY: clean all

clean:
		$(RM) $(TARGET) $(OBJS) $(DEPS)

all: clean $(TARGET)

-include $(DEPS)
