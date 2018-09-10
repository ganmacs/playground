BUILD_SCRIPTS := build_scripts

CC ?= gcc
CXX ?= g++

CXXFLAGS ?= -ggdb3 -fno-omit-frame-pointer -O2
CFLAGS ?= -ggdb3 -fno-omit-frame-pointer -O2
CPPFLAGS ?= -DNDEBUG

# Keep track of the env vars
ENV_STR := $(CC) $(CXX) $(CXXFLAGS) $(CFLAGS) $(CPPFLAGS)

.PHONY: FORCE
FORCE:

$(BUILD_SCRIPTS)/%.dep.env: FORCE
	@[ "$$(cat $@)" != "$(ENV_STR)" ] && echo "$(ENV_STR)" > $@ || echo "No need to rebuild $@"

$(THIRDPARTY_DEPS)/%.dep: $(BUILD_SCRIPTS)/%.sh $(BUILD_SCRIPTS)/%.dep.env
		$<
