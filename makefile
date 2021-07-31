################################################################################

SHELL = bash

NUM_CPU = $(shell nproc --all)

MAKECMDGOALS ?=

MAKEFLAGS += -rR                        # do not use make's built-in rules and variables
MAKEFLAGS += -j$(NUM_CPU)               # parallel processing
MAKEFLAGS += -k                         # keep going
MAKEFLAGS += --output-sync=recurse      # group output messages per recursive make call
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-print-directory

ifeq ($(MAKECMDGOALS), rebuild)
	MAKEFLAGS += -B                     # always make
endif

RM = rm -rf

################################################################################

suppress_echo ?= false

ifeq ($(suppress_echo), true)
	ECHO = :
else
	ECHO = echo -e
endif

ifeq ("$(origin verbose)", "command line")
	Q =
else
	Q = @
endif

################################################################################

PROJECT_NAME = $(notdir $(CURDIR))

$(info )
$(info PROJECT=$(PROJECT_NAME))
$(info )

SUB_TARGET_DIRS := $(realpath $(dir $(shell find -L . -mindepth 2 -maxdepth 2 -name makefile -type f)))

################################################################################

LINTER = clang-format

LINT_EXTENSIONS = .c .cpp .h
LINT_EXCLUDE_DIRS = extlib teensy_loader_cli
LINT_EXCLUDE_DIRS_ := $(addprefix -not -path '*/,$(addsuffix /*',$(LINT_EXCLUDE_DIRS)))

LINT_FILES := $(foreach ext, $(LINT_EXTENSIONS), $(shell find . -name '*$(ext)' $(LINT_EXCLUDE_DIRS_)))

################################################################################

.PHONY: all help clean rebuild run format format-check $(SUB_TARGET_DIRS)

all: $(SUB_TARGET_DIRS)

help:
	@$(ECHO)
	@$(ECHO) 'make                    - recursively make subdirs'
	@$(ECHO) '  verbose=<true>        - optional, default is false'
	@$(ECHO)
	@$(ECHO) 'make clean              - recursively clean subdirs'
	@$(ECHO)
	@$(ECHO) 'make rebuild            - recursively rebuild subdirs'
	@$(ECHO)
	@$(ECHO) 'make run                - recursively run subdirs'
	@$(ECHO)
	@$(ECHO) 'make lint               - lint source code'
	@$(ECHO)
	@$(ECHO) 'make lint-check         - check for lint issues'
	@$(ECHO)
	@$(ECHO) 'make help               - this info'
	@$(ECHO)

$(SUB_TARGET_DIRS):
ifndef MAKECMDGOALS
	$(eval MAKECMDGOALS=)
endif
	$(Q) $(MAKE) -C $@ $(MAKECMDGOALS) tex_debug=false

clean: $(SUB_TARGET_DIRS)

rebuild: all

run: $(SUB_TARGET_DIRS)



lint:
	$(Q) echo $(LINT_FILES) | xargs $(LINTER) -i

lint-check:
	$(Q) echo $(LINT_FILES) | xargs $(LINTER) --dry-run --Werror
