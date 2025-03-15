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

### gdb (디버거)
- GNU Source-Level Debugger
- Usage: ```$ gdb [options] obj-file```
- Options
    - -h: for help
    - -x file: execute GDB commands from _file_
    - -d directory: add _directory_ for source files
    - -q: do not print the introductory and copyright messages


## 실습 프로젝트에서 문자열 복사 및 메모리 오류

* 메모리 오류 디버깅

```c
char *bug = NULL;
strcpy(bug, "hi");  // 메모리가 할당되지 않은 포인터에 쓰는 걸 시도함.
```

이를 GDB를 통해 디버깅하는 과정을 배웠다.