# 커스텀 쉘 (Custom Shell)

> 리눅스 시스템 콜을 활용한 간단한 쉘 구현 프로젝트

## 프로젝트 개요

이 프로젝트는 리눅스 시스템 콜을 직접 활용하여 기본적인 쉘 기능을 구현하는 것을 목표로 합니다. 쉘은 사용자와 운영체제 사이의 인터페이스 역할을 하며, 프로세스 생성 및 관리, 입출력 리다이렉션, 파이프 등 다양한 시스템 콜을 활용하는 좋은 예제입니다.

## 구현 기능

- **명령어 파싱**: 사용자 입력을 토큰화하여 명령어와 인자 분리
- **명령어 실행**: fork(), exec() 시스템 콜을 사용한 외부 명령어 실행
- **내장 명령어**: cd, exit 등의 내장 명령어 구현
- **입출력 리다이렉션**: `>`, `<`, `>>` 등의 리다이렉션 연산자 지원
- **파이프**: `|` 연산자를 사용한 파이프 구현
- **백그라운드 프로세스**: `&`를 사용한 백그라운드 프로세스 실행
- **시그널 처리**: Ctrl+C 등의 시그널 핸들링
- **환경 변수**: 환경 변수 설정 및 사용

## 주요 시스템 콜

이 프로젝트에서 사용된 핵심 시스템 콜과 그 역할은 다음과 같습니다:

| 시스템 콜 | 역할 | 사용 예시 |
|----------|------|----------|
| `fork()` | 새로운 프로세스 생성 | 명령어 실행을 위한 자식 프로세스 생성 |
| `execvp()` | 프로그램 실행 | 자식 프로세스에서 명령어 실행 |
| `wait()`, `waitpid()` | 자식 프로세스 대기 | 명령어 실행 완료 대기 |
| `pipe()` | 파이프 생성 | 명령어 간 데이터 파이프라인 구성 |
| `dup2()` | 파일 디스크립터 복제 | 입출력 리다이렉션 구현 |
| `open()`, `close()` | 파일 열기/닫기 | 리다이렉션 시 파일 처리 |
| `chdir()` | 디렉토리 변경 | cd 명령어 구현 |
| `signal()` | 시그널 핸들러 등록 | Ctrl+C 등의 시그널 처리 |
| `getenv()`, `setenv()` | 환경 변수 관리 | 환경 변수 설정 및 접근 |

## 구현 상세

### 명령어 파싱

사용자 입력을 토큰화하여 명령어와 인자, 특수 연산자(파이프, 리다이렉션)를 식별합니다.

```c
char *input = NULL;
size_t bufsize = 0;
getline(&input, &bufsize, stdin);

// 토큰화 및 파싱 로직
```

### 명령어 실행

fork()와 exec() 시스템 콜을 사용하여 명령어를 실행합니다.

```c
pid_t pid = fork();
if (pid == 0) {
    // 자식 프로세스
    execvp(args[0], args);
    perror("execvp");
    exit(EXIT_FAILURE);
} else if (pid > 0) {
    // 부모 프로세스
    if (!background) {
        waitpid(pid, &status, 0);
    }
}
```

### 파이프 구현

pipe() 시스템 콜을 사용하여 명령어 간 파이프를 구현합니다.

```c
int pipefd[2];
pipe(pipefd);

pid_t pid1 = fork();
if (pid1 == 0) {
    // 첫 번째 명령어 실행 (출력을 파이프에 연결)
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    execvp(cmd1[0], cmd1);
    exit(EXIT_FAILURE);
}

pid_t pid2 = fork();
if (pid2 == 0) {
    // 두 번째 명령어 실행 (입력을 파이프에서 받음)
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    execvp(cmd2[0], cmd2);
    exit(EXIT_FAILURE);
}

// 부모 프로세스에서 파이프 닫기
close(pipefd[0]);
close(pipefd[1]);
```

## 시스템 콜 직접 사용의 의미

이 프로젝트에서는 고수준 라이브러리가 아닌 저수준 시스템 콜을 직접 사용하였습니다.

1. **OS 내부 동작 이해**: 프로세스 생성과 관리, 파일 디스크립터 조작 등 OS 내부 동작 방식을 직접 경험
2. **자원 제어의 세밀함**: 파일 디스크립터, 프로세스 상태 등을 세밀하게 제어 가능
3. **성능 최적화 가능성**: 필요한 기능만 최소한으로 사용하여 효율적인 구현 가능

## 빌드 및 실행 방법

```bash
# 빌드
make

# 실행
./custom-shell
```

## 사용 예시

```
$ ./custom-shell
myshell> ls -la
# ls 명령 실행 결과 출력

myshell> echo "Hello" > output.txt
# output.txt 파일에 "Hello" 저장

myshell> cat < output.txt
Hello

myshell> ls -la | grep .c
# .c 확장자 파일만 필터링하여 표시

myshell> sleep 10 &
# 백그라운드에서 sleep 명령 실행

myshell> cd /tmp
# 디렉토리 변경

myshell> exit
# 쉘 종료
```

## 한계 및 개선 가능성

현재 구현에는 다음과 같은 한계가 있으며, 향후 개선할 수 있습니다.

1. **복잡한 명령어 파싱 제한**: 따옴표 처리, 이스케이프 문자 등 복잡한 파싱 기능 미흡
2. **작업 제어 기능 부족**: fg, bg 등의 작업 제어 명령어 미구현
3. **다중 파이프 제한**: 현재는 단일 파이프만 지원

## 배운 점

이 프로젝트를 통해 다음과 같은 핵심 개념을 깊이 이해할 수 있었습니다.

1. **프로세스 생성 및 관리 메커니즘**: fork(), exec(), wait() 시스템 콜의 정확한 동작 방식
2. **파일 디스크립터와 리다이렉션**: 파일 디스크립터의 개념과 dup2()를 통한 리다이렉션 구현
3. **파이프 통신 원리**: 프로세스 간 통신을 위한 파이프의 작동 원리
4. **시그널 처리 메커니즘**: 시그널 핸들러 등록 및 처리 방법