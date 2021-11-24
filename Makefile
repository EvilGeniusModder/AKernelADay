# Collect all subdirectories for us
SUBDIRS := $(wildcard Source/*/.)

# Call make on all of them.
all: $(SUBDIRS)
$(SUBDIRS):
        $(MAKE) -C $@

# Let Make know that these don't directly corespond to an actual file.
.PHONY: all $(SUBDIRS)