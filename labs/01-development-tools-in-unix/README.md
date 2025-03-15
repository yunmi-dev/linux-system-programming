# Development Tools in Linux

## 리눅스 개발 도구
### 여러 도구의 조합: 텍스트 편집(vi) -> 컴파일(gcc) -> 라이브러리 생성(ar) -> Linking -> 실행파일 생성 -> 디버깅(gdb)

### vi 편집기
- 모드 기반 Text Editor (명령 모드, 입력 모드, 명령행 모드)
- 시스템 관리 및 개발에 필수
- 주요 명령어
    - 커서 이동
        - l (right)
        - h (left)
        - j (down)
        - k (up)
        - $ (end of line)
        - ^ (behin of line)
        - ^F (nest page)
        - ^B (previous page)
        - ^D (next half-page)
        - ^U (previous half-page)
        - ]] (next function)
        - [[ (previous function)

    - 편집 명령어
        - x (character 하나 삭제)
        - dw (word 하나 삭제)
        - dd (line 한 줄 삭제), 5dd (5줄 한번에 삭제)
        - yy (line 한줄 copy), 3yy (3줄 한번에 copy), p (copy해놓은 것 paste)
        - u (undo)
        - . (repeat)

    - CLI 모드일 떄 명령어
        - :w (write)
        - :r _filename_ (read & insert a file)
        - :e _filename_ (edit a new file)
        - :n (edit next file, vi *.c로 여러 파일을 열었을 때)
        - /string (앞으로 검색)
        - ?string (뒤로 검색)
        - n (다음 검색 결과)
        - N (이전 검색 결과)
        - :1,$s/기존문자열/새문자열/g (전체 치환)
        - :!ls (쉘 명령어 실행)


### gcc 컴파일러
- GNU C 컴파일러로, c와 c++ 코드 컴파일
- 주요 옵션
    - -c: 컴파일만 수행 (링크 단계 생략)
    - -o: 출력 파일 이름 지정
    - -Dname[=def]: 심볼 정의
    - -g: 디버깅 정보 포함
    - -I경로: 헤더 파일 검색 경로 추가
    - -l라이브러리: 라이브러리와 링크
    - -L디렉토리: 라이브러리 검색 디렉토리 추가
    - -O[level]: 코드 최적화 수준 설정
    - -S: 어셈블리 소스 파일 생성
    - -w: 경고 메시지 출력 안함
    - -static: 정적 링킹 (기본값은 동적 링킹)

- 사용 예시
    ```bash
    $ gcc test.c                      # 기본 컴파일, a.out 생성
    $ gcc -o test test.c              # 이름 지정하여 컴파일
    $ gcc -c test1.c test2.c          # 컴파일만 수행하여 .o 파일 생성
    $ gcc -o test test.c test1.o test2.o libtmp.a  # 여러 파일과 라이브러리 링크
    $ gcc -I../include -L../lib math.c -lm  # 헤더/라이브러리 경로 지정
    ```

### ar (라이브러리 아카이브)
- 여러 개의 obj 파일을 하나의 아카이브 파일(정적 라이브러리(.a, archive))로 만들거나 관리하는 유닉스 계열 유틸리티
- 주요 옵션
    - r: 파일 교체 또는 추가
    - c: 아카이브 생성
    - v: 자세한 출력 (verbose)
    - u: 최신 파일만 교체
    - t: 아카이브 내용 목록 출력
    - x: 아카이브에서 파일 추출

- 사용 예시
    ```bash
    $ ar rcv libmine.a file1.o file2.o    # 정적 라이브러리 생성
    $ ar tv libmine.a                     # 라이브러리 내용 조회
    $ ar xv libmine.a file1.o             # 특정 파일 추출
    ```

### make (빌드 자동화)
- 여러 파일로 구성된 프로그램의 빌드 과정을 자동화
- Makefile 구성 요소
    - 의존성 라인: `타겟: [사전조건] [; 명령]`
    - 명령 라인: `탭 [@] 명령`
    - 매크로 정의: `이름 = 문자열`
    - 주석: `# 주석`

- 내부 매크로
    - $@: 현재 타겟의 이름
    - $<: 현재 사전조건의 이름
    - $^: 모든 사전조건 목록
    - $?: 타겟보다 새로운 사전조건 목록
    - $*: 접미사 없는 현재 사전조건의 이름

- 기본 Makefile 예시
    ```makefile
    CC = gcc
    CFLAGS = -I../inc -g
    LDFLAGS = -L. -lmine
    
    TARGET = hello
    OBJS = hello.o
    
    .SUFFIXES : .c .o
    .c.o :
        $(CC) -c $(CFLAGS) $
    
    $(TARGET) : $(OBJS) libmine.a
        $(CC) -o $@ $(OBJS) $(LDFLAGS)
    
    libmine.a : mystrcpy.o
        ar ruv libmine.a mystrcpy.o
    
    clean :
        rm -rf libmine.a $(TARGET) *.o
    ```

### gdb (디버거)
- GNU Source-Level Debugger
- Usage: ```$ gdb [options] obj-file```
- Options
    - -h: for help
    - -x file: execute GDB commands from _file_
    - -d directory: add _directory_ for source files
    - -q: do not print the introductory and copyright messages

- 실행 명령어
    - break [파일:]라인번호: 지정된 위치에 중단점 설정
    - break [파일:]함수이름: 지정된 함수 진입점에 중단점 설정
    - run [인자목록]: 프로그램 실행
    - print 표현식: 표현식 값 한 번만 출력
    - display 표현식: 중단점마다 표현식 값 계속 출력
    - cont: 실행 계속
    - next [n]: 다음 n줄 실행 (함수 호출 시 함수 내부로 들어가지 않음)
    - step: 다음 줄 실행 (함수 내부로 들어감)
    - quit: 디버깅 종료

## 실습 프로젝트: 문자열 복사 및 메모리 오류

### 문자열 복사 함수 구현
```c
// mystrcpy.c
#include <string.h>

void mystrcpy(char *dst, char *src) {
    while (*src) {
        *dst++ = *src++;
    }
    *dst = *src;
}
```

### 메인 프로그램
```c
// hello.c
#include <stdio.h>

int main() {
    char str[80];
    
    mystrcpy(str, "Hello, World!");
    puts(str);
    
    return 0;
}
```

### 라이브러리 생성 및 링킹

```bash
# mystrcpy.c를 컴파일하여 목적 파일 생성
$ gcc -c mystrcpy.c

# 목적 파일을 라이브러리로 아카이브
$ ar ruv libmine.a mystrcpy.o

# 라이브러리를 링크하여 실행 파일 생성
$ gcc -o hello -L. hello.c -lmine

# 실행
$ ./hello
Hello, World!
```

### 메모리 오류를 GDB를 사용한 디버깅 실습

```c
// bug.c
#include <stdio.h>
#include <string.h>

int main() {
    int i;
    double j;
    char *bug = NULL;
    
    for (i = 0; i < 5; i++) {
        j = i/2 + i;
        printf("j is %lf \n", j);
    }
    
    strcpy(bug, "hi");  // 메모리가 할당되지 않은 포인터에 쓰기 시도
    printf("bug is %s \n", bug);
    
    return 0;
}
```

```bash
# 디버깅 정보를 포함하여 컴파일
$ gcc -g bug.c

# GDB 디버거 실행
$ gdb a.out

# 실행 전 중단점 설정 (for 루프 시작 부분)
(gdb) break 10
Breakpoint 1 at 0x760: file bug.c, line 10.

# 프로그램 실행
(gdb) run
Starting program: /path/to/a.out
[Thread debugging using libthread_db enabled]

Breakpoint 1, main () at bug.c:10
10              int i;

# 한 줄씩 실행하며 변수 상태 확인
(gdb) next
11              double j;
(gdb) next
12              char *bug = NULL;
(gdb) next
...

# 변수 값 출력
(gdb) print i
$1 = 2
(gdb) print j 
$2 = 3.000000

# 포인터 변수 상태 확인
(gdb) print bug
$3 = 0x0

# 실행 계속하기
(gdb) continue
Continuing.
j is 6.000000 

Program received signal SIGSEGV, Segmentation fault.
0x0000aaaaaaaa07c8 in main () at bug.c:15
15              strcpy(bug, "hi");
```

- 이 디버깅 세션에서 확인할 수 있는 중요한 점
    - bug 포인터가 NULL(0x0)로 초기화되었음을 확인
    - strcpy(bug, "hi") 라인에서 세그멘테이션 폴트가 발생!!!
    - NULL 포인터에 데이터를 쓰려고 시도했기 때문

이 문제를 해결하려면 문자열을 복사하기 전에 메모리를 할당해야 한다. (메모리 할당 없이 포인터 사용할 때의 위험성)

```c
// 수정된 코드
char *bug = (char *)malloc(3); // "hi"와 널 종료 문자를 위한 공간
if (bug != NULL) {
    strcpy(bug, "hi");
    printf("bug is %s \n", bug);
    free(bug); // 메모리 해제
}
```
서버 애플리케이션에서 이런 메모리 관리 문제는 심각한 보안 취약점이나 시스템 불안정성을 초래할 수 있어 철저한 디버깅이 필수