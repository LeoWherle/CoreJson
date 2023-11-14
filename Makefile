##
## EPITECH PROJECT, 2023
## CoreJson [WSL: fedora]
## File description:
## Makefile
##

# output binary
BIN := jsonparse
LIBBIN := libcorejson.a
LIBSHAREDBIN := libcorejson.so
TEST_BIN := unit_tests

# Colors :
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[1;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
NC = \033[0m


# source files
SRC = 	src/builder/jsn_builder.c \
		src/builder/jsn_free.c \
		src/builder/jsn_create.c \
		src/builder/jsn_dup.c \
		src/builder/jsn_array/jsn_array_add_value.c \
		src/builder/jsn_array/jsn_array_add_null.c \
		src/builder/jsn_array/jsn_array_from_list.c \
		src/builder/jsn_object/jsn_object_add_value.c \
		src/builder/jsn_object/jsn_object_add_null.c \
		src/lexer/jsn_lexer_helper.c \
		src/lexer/jsn_lexer_match.c \
		src/lexer/jsn_lexer.c \
		src/lexer/jsn_tokens/jsn_tkn_bool.c \
		src/lexer/jsn_tokens/jsn_tkn_braces.c \
		src/lexer/jsn_tokens/jsn_tkn_brackets.c \
		src/lexer/jsn_tokens/jsn_tkn_colon.c \
		src/lexer/jsn_tokens/jsn_tkn_comma.c \
		src/lexer/jsn_tokens/jsn_tkn_end.c \
		src/lexer/jsn_tokens/jsn_tkn_null.c \
		src/lexer/jsn_tokens/jsn_tkn_number.c \
		src/lexer/jsn_tokens/jsn_tkn_string.c \
		src/parser/jsn_parser_array.c \
		src/parser/jsn_parser_object.c \
		src/parser/jsn_parser.c \
		src/parser/jsn_parse/jsn_parse_array.c \
		src/parser/jsn_parse/jsn_parse_object.c \
		src/parser/jsn_parse/jsn_parse_number.c \
		src/parser/jsn_parse/jsn_parse_string.c \
		src/parser/jsn_parse/jsn_parse_bool.c \
		src/parser/jsn_parse/jsn_parse_null.c \
		src/utils/print/jsn_print.c \
		src/utils/print/jsn_print_array.c \
		src/utils/print/jsn_print_object.c \
		src/utils/print/jsn_print_number.c \
		src/utils/print/jsn_print_string.c \
		src/utils/print/jsn_print_bool.c \
		src/utils/print/jsn_print_null.c

SRCS =   src/main.c \
			$(SRC)

SRC_TEST = 	tests/t_lexer.c \
			tests/t_parser.c \
			tests/t_parser_errors.c \
			tests/t_json_print.c \
			tests/t_json_add_value.c \
			tests/t_json_create.c \
			tests/t_json_dup.c \
			tests/t_json_create_from_list.c \
			$(SRC)

DISTFILES := $(BIN)
# filename of the tar archive generated by 'make dist'
DISTOUTPUT := $(BIN).tar.gz

BUILD_DIR = build

# intermediate directory for generated object files
OBJDIR := $(BUILD_DIR)/obj
# intermediate directory for generated dependency files
DEPDIR := $(BUILD_DIR)/dep

# object files, auto generated from source files
OBJS := $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRCS)))
OBJS_LIBS := $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRC)))
# dependency files, auto generated from source files
DEPS := $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

COMMITHASH := $(shell git describe --always --abbrev=0\
 --match "NOT A TAG" --dirty="*")
DATE := $(shell date "+%d-%b-%Y %Hh:%Mm:%Ss (UTC)" --utc)
# compilers don't create the subdirectories automatically
$(shell mkdir -p $(dir $(OBJS)) >/dev/null)
$(shell mkdir -p $(dir $(DEPS)) >/dev/null)

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
CXXFLAGS :=
# C/C++ flags
CPPFLAGS := -Wall -Wextra -Wformat=2 -Wswitch-default -Wcast-align \
     -Wpointer-arith -Wbad-function-cast -Wstrict-prototypes \
     -Winline -Wundef -Wnested-externs -Wcast-qual -Wshadow  \
     -Wwrite-strings -Wconversion -Wunreachable-code \
     -Wstrict-aliasing=2\
     -ffloat-store -fno-common -fstrict-aliasing \
     -pedantic -Wunused-macros

# linker flags
LDFLAGS :=
# linker flags: libraries to link (e.g. -lfoo)
LDLIBS :=
# flags required for dependency generation; passed to compilers
DEPFLAGS = -MT $@ -MD -MP -MF $(DEPDIR)/$*.Td

# release build flags (make release=1 ...)
ifdef release
	CFLAGS += -O2
	CXXFLAGS += -O2
else
	CFLAGS += -g3
	CXXFLAGS += -g3
endif

ifdef debug
	LDFLAGS += -DDEBUG
endif

ifdef native
	CFLAGS += -march=native
	CXXFLAGS += -march=native
endif

ifdef analysis
	CPPFLAGS += -fanalyzer
endif

# precompile step
PRECOMPILE =
# postcompile step
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

.PHONY: all
all: gen_version
all: $(BIN)

.PHONY: lib
lib: gen_version
lib: $(LIBBIN)

.PHONY: lib-shared
lib-shared: gen_version
lib-shared: $(LIBSHAREDBIN)

.PHONY: dist
dist: $(DISTFILES)
	$(TAR) -cvzf $(DISTOUTPUT) $^

.PHONY: clean
clean:
	$(RM) -r $(OBJDIR) $(DEPDIR)

.PHONY: fclean
fclean: clean tests_clean
	$(RM) $(BIN) $(DISTOUTPUT) $(LIBBIN) $(LIBSHAREDBIN)

.PHONY: re
re: fclean
re:
	@$(MAKE) all

.PHONY: tests_clean
tests_clean:
	$(RM) $(TEST_BIN) *.gcda *.gcno *.gcov

.PHONY: $(TEST_BIN)
$(TEST_BIN): LDLIBS += -lcriterion -lgcov
$(TEST_BIN): LDFLAGS += --coverage
$(TEST_BIN): $(SRC_TEST)
	@$(LD) $(LDFLAGS) $(LDLIBS) $(CFLAGS) -o $@ $^
	@echo -e "$(GREEN)linked\t$(WHITE)$@$(NC), \
	with CFLAGS: $(CYAN)$(CFLAGS)$(NC) \
	and LIB: $(YELLOW)$(LDLIBS)$(NC) \
	and LDFLAGS: $(BLUE)$(LDFLAGS)$(NC)"

.PHONY: tests_run
tests_run: $(TEST_BIN)
tests_run:
	@-./$(TEST_BIN)

coverage: tests_run
	@echo "Generating coverage report..."
	@gcovr -r . --html --html-details -o coverage/index.html --exclude tests

$(BIN): $(OBJS)
	@$(LD) $(LDFLAGS) $(LDLIBS) -o $@ $^
	@echo -e "$(GREEN)linked\t$(WHITE)$@$(NC), \
	with CFLAGS: $(CYAN)$(CFLAGS)$(NC) \
	and LIB: $(YELLOW)$(LDLIBS)$(NC) \
	and LDFLAGS: $(BLUE)$(LDFLAGS)$(NC)"


$(LIBBIN): $(OBJS_LIBS)
	@ar rcs $(LIBBIN) $^
	@echo -e "$(GREEN)linked\t$(WHITE)$@$(NC), \
	with CFLAGS: $(CYAN)$(CFLAGS)$(NC) \
	and LIB: $(YELLOW)$(LDLIBS)$(NC) \
	and LDFLAGS: $(BLUE)$(LDFLAGS)$(NC)"

$(LIBSHAREDBIN): CFLAGS += -fPIC
$(LIBSHAREDBIN): LDFLAGS += -shared
$(LIBSHAREDBIN): $(OBJS_LIBS)
	@if $(LD) $(LDFLAGS) $(LDLIBS) -o $@ $^; then \
		echo -e "$(GREEN)linked\t$(WHITE)$@$(NC), \
		with CFLAGS: $(CYAN)$(CFLAGS)$(NC) \
		and LIB: $(YELLOW)$(LDLIBS)$(NC) \
		and LDFLAGS: $(BLUE)$(LDFLAGS)$(NC)"; \
	else \
		echo -e "$(RED)failed\t$(WHITE)$@$(NC) \
		$(PURPLE)make fclean and try again$(NC)"; \
	fi
.PHONY: gen_version
gen_version:
	@echo "/*" > include/corejson/version.h
	@echo "** EPITECH PROJECT, 2023" >> include/corejson/version.h
	@echo "** CoreJson [WSL: fedora]" >> include/corejson/version.h
	@echo "** File description:" >> include/corejson/version.h
	@echo "** version.h file" >> include/corejson/version.h
	@echo "*/" >> include/corejson/version.h
	@echo "" >> include/corejson/version.h
	@echo "#ifndef VERSION_H" >> include/corejson/version.h
	@echo "    #define VERSION_H" >> include/corejson/version.h
	@echo "    #define VERSION_GIT  \"$(COMMITHASH)\""\
	 >> include/corejson/version.h
	@echo "    #define VERSION_DATE \"$(DATE)\""\
	 >> include/corejson/version.h
	@echo "#endif /* VERSION_H */" >> include/corejson/version.h

$(OBJDIR)/%.o: %.c
$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	$(PRECOMPILE)
	@$(CC) $(DEPFLAGS) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -c -o $@ $<
	@echo -e "$(GREEN)built\t$(WHITE)$<$(NC)"
	@$(POSTCOMPILE)

$(OBJDIR)/%.o: %.cpp
$(OBJDIR)/%.o: %.cpp $(DEPDIR)/%.d
	$(PRECOMPILE)
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(POSTCOMPILE)

$(OBJDIR)/%.o: %.cc
$(OBJDIR)/%.o: %.cc $(DEPDIR)/%.d
	$(PRECOMPILE)
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(POSTCOMPILE)

$(OBJDIR)/%.o: %.cxx
$(OBJDIR)/%.o: %.cxx $(DEPDIR)/%.d
	$(PRECOMPILE)
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(POSTCOMPILE)

.PRECIOUS: $(DEPDIR)/%.d
$(DEPDIR)/%.d: ;

-include $(DEPS)
