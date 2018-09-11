BUILD_SCRIPTS := build_scripts

CC = gcc
CXX = g++

CXXFLAGS ?= -ggdb3 -fno-omit-frame-pointer -O2
CFLAGS ?= -ggdb3 -fno-omit-frame-pointer -O2
CPPFLAGS ?= -DNDEBUG

# Keep track of the env vars
ENV_STR := $(CC) $(CXX) $(CXXFLAGS) $(CFLAGS) $(CPPFLAGS)

.PHONY: FORCE
FORCE:

.PRECIOUS: $(THIRDPARTY_DEPS)/%.dep.env

$(THIRDPARTY_DEPS)/%.dep.env: FORCE
	@[ "$$(cat $@)" != "$(ENV_STR)" ] && echo "$(ENV_STR)" > $@ || echo "No need to rebuild $@"

build-repo = $< && \
	echo "Successful build of $@" && \
	touch $@

$(THIRDPARTY_DEPS)/%.dep: $(BUILD_SCRIPTS)/%.sh $(THIRDPARTY_DEPS)/%.dep.env
	@+$(call build-repo)
