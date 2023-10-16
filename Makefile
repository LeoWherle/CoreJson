
# output binary
BIN := json
TEST_BIN := unit_tests

# source files
SRC = 	src/json_lexer.c \
		src/json_lexer_helper.c \
		src/json_parser.c \
		src/json_object_parser.c \
		src/json_array_parser.c \
		src/json_print.c \
		src/json_free.c

SRCS =   src/main.c \
			$(SRC)

SRC_TEST = 	tests/t_lexer.c \
			tests/t_parser.c \
			tests/t_json_print.c \
			$(SRC)

# files included in the tarball generated by 'make dist' (e.g. add LICENSE file)
DISTFILES := $(BIN)

# filename of the tar archive generated by 'make dist'
DISTOUTPUT := $(BIN).tar.gz

BUILD_DIR = build

# intermediate directory for generated object files
OBJDIR := build/obj
# intermediate directory for generated dependency files
DEPDIR := build/dep

# object files, auto generated from source files
OBJS := $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRCS)))
OBJS_TEST := $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRC_TEST)))
# dependency files, auto generated from source files
DEPS := $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
DEPS_TEST := $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRC_TEST)))

COMMITHASH := $(shell git describe --always --abbrev=0\
 --match "NOT A TAG" --dirty="*")
DATE := $(shell date "+%d-%b-%Y %Hh:%Mm:%Ss (UTC)" --utc)
# compilers (at least gcc and clang) don't create the subdirectories automatically
$(shell mkdir -p $(dir $(OBJS)) >/dev/null)
$(shell mkdir -p $(dir $(DEPS)) >/dev/null)
$(shell mkdir -p $(dir $(OBJS_TEST)) >/dev/null)
$(shell mkdir -p $(dir $(DEPS_TEST)) >/dev/null)

MAKEFLAGS += --no-print-directory
# C compiler
CC := gcc
# C++ compiler
CXX := gpp
# linker
LD := gcc
# tar
TAR := tar

# C flags
CFLAGS :=  -I./include
# C++ flags	
CXXFLAGS := -std=c++11
# C/C++ flags
CPPFLAGS := -g3 -Wall -Wextra -pedantic -Wwrite-strings -Winit-self -Wformat=2\
 -Wmissing-include-dirs -Wunreachable-code -Winline -Wundef\
 -Wno-missing-field-initializers
# linker flags
LDFLAGS :=
# linker flags: libraries to link (e.g. -lfoo)
LDLIBS := -lcriterion
# flags required for dependency generation; passed to compilers
DEPFLAGS = -MT $@ -MD -MP -MF $(DEPDIR)/$*.Td

# release build flags (make release=1 ...)
ifdef release
	CFLAGS += -O3
	CXXFLAGS += -O3
endif

# compile C source files
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c -o $@
# compile C++ source files
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@
# link object files to binary
LINK.o = $(LD) $(LDFLAGS) $(LDLIBS) -o $@
# precompile step
PRECOMPILE =
# postcompile step
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all: gen_version
all: $(BIN)

dist: $(DISTFILES)
	$(TAR) -cvzf $(DISTOUTPUT) $^

.PHONY: clean
clean:
	$(RM) -r $(OBJDIR) $(DEPDIR)

.PHONY: fclean
fclean: clean tests_clean
	$(RM) $(BIN) $(DISTOUTPUT)

.PHONY: re
re: fclean
re:
	@$(MAKE) all

.PHONY: tests_clean
tests_clean:
	$(RM) $(TEST_BIN)
	$(RM) *.gcda
	$(RM) *.gcno
	$(RM) *.gcov

.PHONY: $(TEST_BIN)
$(TEST_BIN): $(SRC_TEST)
	$(LD) $(LDFLAGS) -lcriterion $(CFLAGS) -o $@ --coverage $^

.PHONY: tests_run
tests_run: $(TEST_BIN)
tests_run:
	-./$(TEST_BIN)

$(BIN): $(OBJS)
	$(LINK.o) $^

.PHONY: gen_version
gen_version:
	@echo "#ifndef VERSION_H" > include/version.h
	@echo "    #define VERSION_H" >> include/version.h
	@echo "    #define VERSION_GIT  \"$(COMMITHASH)\"" >> include/version.h
	@echo "    #define VERSION_DATE \"$(DATE)\"" >> include/version.h
	@echo "#endif /* VERSION_H */" >> include/version.h

# .PHONY: release
# release: gen_version
# # release: $(COMPILE.c) += -O3
# # release: $(COMPILE.cc) += -O3
# release:
# 	echo $(COMPILE.c)
# 	$(MAKE) re

$(OBJDIR)/%.o: %.c
$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	$(PRECOMPILE)
	$(COMPILE.c) $<
	$(POSTCOMPILE)

$(OBJDIR)/%.o: %.cpp
$(OBJDIR)/%.o: %.cpp $(DEPDIR)/%.d
	$(PRECOMPILE)
	$(COMPILE.cc) $<
	$(POSTCOMPILE)

$(OBJDIR)/%.o: %.cc
$(OBJDIR)/%.o: %.cc $(DEPDIR)/%.d
	$(PRECOMPILE)
	$(COMPILE.cc) $<
	$(POSTCOMPILE)

$(OBJDIR)/%.o: %.cxx
$(OBJDIR)/%.o: %.cxx $(DEPDIR)/%.d
	$(PRECOMPILE)
	$(COMPILE.cc) $<
	$(POSTCOMPILE)

.PRECIOUS: $(DEPDIR)/%.d
$(DEPDIR)/%.d: ;

-include $(DEPS)
