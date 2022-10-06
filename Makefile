# 
TOPTARGETS := all clean
# Register all subdirectories in the project's root directory
SUBDIRS := $(wildcard */*/.)

$(TOPTARGETS): $(SUBDIRS)
# Recursively call the makefile in each subdirectory
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)