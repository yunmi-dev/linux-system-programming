# 컴파일러 지정
CC = gcc
# 컴파일러 플래그 (필요시 -Wall 등 추가 가능)
CFLAGS =
# 링커 플래그 (-L.: 현재 디렉토리에서 라이브러리 검색, -lmine: libmine 라이브러리 링크)
LDFLAGS = -L. -lmine

# 빌드할 최종 실행 파일 이름
TARGET = hello
# 필요한 오브젝트 파일 목록
OBJS = hello.o 

# 인식할 파일 확장자 지정
.SUFFIXES : .c .o

# .c 파일을 .o 파일로 변환하는 규칙
.c.o :
	$(CC) -c $(CFLAGS) $<

# 최종 타겟 빌드 규칙
$(TARGET) : $(OBJS) libmine.a
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# 정적 라이브러리 생성 규칙
libmine.a : mystrcpy.o
	ar ruv libmine.a mystrcpy.o

# 빌드 결과물 정리를 위한 규칙 (make clean으로 실행)
clean :
	rm -rf libmine.a $(TARGET) *.o