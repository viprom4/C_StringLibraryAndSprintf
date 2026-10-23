CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11
TEST_FLAGS = -Wall -Wextra -std=c11

LIB = s21_string.a
TEST = s21_string_test

LIBS = -lcheck -lsubunit -lm -lrt -pthread

SRCS = \
	chatayav/chatayav.c \
	dottedlu/dottedlu.c \
	jalfreza/jalfreza.c \
	sprintf/s21_sprintf.c

SRCS_CLANG = \
	chatayav/chatayav.c \
	chatayav/chatayav.h \
	dottedlu/dottedlu.c \
	dottedlu/dottedlu.h \
	jalfreza/jalfreza.c \
	jalfreza/jalfreza.h \
	sprintf/s21_sprintf.c \
	sprintf/s21_sprintf.h \
	s21_common.h \
	s21_string.h \
	Tests/test_s21_string.c\

TEST_SRC = Tests/test_s21_string.c

OBJS = $(SRCS:.c=.o)


all: $(LIB)


$(LIB): $(OBJS)
	ar rcs $(LIB) $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clang-format:
# 	clang-format -i $(SRCS_CLANG)
	clang-format -n $(SRCS_CLANG)

test: $(LIB)
	$(CC) $(TEST_FLAGS) $(TEST_SRC) $(LIB) -o $(TEST) $(LIBS)
	./$(TEST)


gcov_report:
	rm -f $(OBJS) $(LIB) $(TEST)
	rm -f $(SRCS:.c=.gcda)
	rm -f $(SRCS:.c=.gcno)
	rm -f $(SRCS:.c=.gcov)
	rm -f gcov_report.html

	$(CC) $(TEST_FLAGS) --coverage -c chatayav/chatayav.c -o chatayav/chatayav.o
	$(CC) $(TEST_FLAGS) --coverage -c dottedlu/dottedlu.c -o dottedlu/dottedlu.o
	$(CC) $(TEST_FLAGS) --coverage -c jalfreza/jalfreza.c -o jalfreza/jalfreza.o
	$(CC) $(TEST_FLAGS) --coverage -c sprintf/s21_sprintf.c -o sprintf/s21_sprintf.o

	ar rcs $(LIB) $(OBJS)

	$(CC) $(TEST_FLAGS) --coverage $(TEST_SRC) $(LIB) -o $(TEST) $(LIBS)
	./$(TEST)

	gcov $(SRCS)

	@echo "<html><head><meta charset='UTF-8'><title>GCOV Report</title></head><body>" > gcov_report.html
	@echo "<h1>GCOV Report</h1>" >> gcov_report.html
	@for file in $(notdir $(SRCS)); do \
		echo "<h2>$$file</h2>" >> gcov_report.html; \
		echo "<pre>" >> gcov_report.html; \
		if [ -f "$$file.gcov" ]; then \
			cat "$$file.gcov" >> gcov_report.html; \
		fi; \
		echo "</pre>" >> gcov_report.html; \
	done
	@echo "</body></html>" >> gcov_report.html

	@echo "Coverage report: gcov_report.html"

	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f chatayav/*.gcda chatayav/*.gcno chatayav/*.gcov
	rm -f dottedlu/*.gcda dottedlu/*.gcno dottedlu/*.gcov
	rm -f jalfreza/*.gcda jalfreza/*.gcno jalfreza/*.gcov
	rm -f sprintf/*.gcda sprintf/*.gcno sprintf/*.gcov
	rm -f $(OBJS)


clean:
	rm -f $(LIB)
	rm -f $(TEST)
	rm -f $(OBJS)
	rm -f gcov_report.html
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f chatayav/*.gcda chatayav/*.gcno chatayav/*.gcov
	rm -f dottedlu/*.gcda dottedlu/*.gcno dottedlu/*.gcov
	rm -f jalfreza/*.gcda jalfreza/*.gcno jalfreza/*.gcov
	rm -f sprintf/*.gcda sprintf/*.gcno sprintf/*.gcov

rebuild: clean all


.PHONY: all test gcov_report clean rebuild