CC = gcc
CFLAGS =
LDFLAGS =

.SUFFIXES : .c .o	# 처리할 파일 확장자를 지정함
.c.o :			# .c 파일을 .o 파일로 변환하는 패턴 규칙
	$(CC) -c $(CFLAGS) $<

ALL = hello output input args string	# 빌드할 모든 실행 파일 목록

all: $(ALL)		# 기본 타겟: 모든 실행 파일 빌드

# 프로그램별 빌드 규칙
hello: hello.o
	$(CC) -o $@ $< $(LDFLAGS)

output: output.o
	$(CC) -o $@ $< $(LDFLAGS)

input: input.o
	$(CC) -o $@ $< $(LDFLAGS)

args: args.o
	$(CC) -o $@ $< $(LDFLAGS)

string: string.o
	$(CC) -o $@ $< $(LDFLAGS)

# 정리 타겟: 생성된 모든 오브젝트 파일과 실행파일 삭제
clean :
	rm -rf *.o $(ALL)