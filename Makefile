include base.mk

# Collect all subdirectories for us
SUBDIRS := $(wildcard Source/*/.)

TARGET := Source/crt0.o

# Call make on all of them.
all: Source/crt0.s $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

# Let Make know that these don't directly corespond to an actual file.
.PHONY: all $(SUBDIRS)