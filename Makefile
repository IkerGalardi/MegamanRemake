# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  megaman_config = debug

else ifeq ($(config),release)
  megaman_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := megaman

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

megaman:
ifneq (,$(megaman_config))
	@echo "==== Building megaman ($(megaman_config)) ===="
	@${MAKE} --no-print-directory -C . -f megaman.make config=$(megaman_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f megaman.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   megaman"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"