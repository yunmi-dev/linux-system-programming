# 시스템 모니터링 도구 (System Monitor)

> /proc 파일시스템을 활용한 리눅스 시스템 모니터링 도구

## 프로젝트 개요

이 프로젝트는 리눅스의 /proc 가상 파일시스템을 직접 활용하여 시스템 자원 사용 현황과 프로세스 정보를 실시간으로 모니터링하는 도구를 구현합니다. 파일 I/O 시스템 콜을 통해 커널이 제공하는 시스템 정보에 직접 접근하고 이를 사용자 친화적으로 표시합니다.

## 구현 기능

- **CPU 사용량 모니터링**: 코어별 CPU 사용률, 부하 평균 표시
- **메모리 사용량 모니터링**: 물리 메모리, 가상 메모리, 스왑 사용 현황
- **디스크 I/O 모니터링**: 디스크 읽기/쓰기 작업 통계
- **네트워크 트래픽 모니터링**: 인터페이스별 송수신 패킷 및 바이트 통계
- **프로세스 목록 및 상세 정보**: 실행 중인 프로세스 목록 및 자원 사용 현황
- **시스템 정보 요약**: 커널 버전, 업타임, 로드 평균 등 기본 시스템 정보

## 주요 시스템 콜 및 /proc 파일

이 프로젝트에서 활용한 핵심 시스템 콜과 접근하는 /proc 파일들은 다음과 같습니다.

| 시스템 콜 | 역할 | 사용 예시 |
|----------|------|----------|
| `open()` | 파일 열기 | /proc 파일 시스템 접근 |
| `read()` | 파일 읽기 | 시스템 정보 읽기 |
| `close()` | 파일 닫기 | 리소스 해제 |
| `lseek()` | 파일 포인터 이동 | 파일 내 위치 이동 |
| `stat()` | 파일 정보 조회 | 파일 크기, 수정 시간 등 확인 |
| `opendir()`, `readdir()` | 디렉토리 탐색 | /proc/pid 디렉토리 탐색 |

| /proc 파일 | 제공 정보 | 활용 |
|------------|----------|------|
| `/proc/stat` | CPU 사용량, 인터럽트 등 | CPU 사용률 계산 |
| `/proc/meminfo` | 메모리 사용 정보 | 메모리 사용량 모니터링 |
| `/proc/loadavg` | 시스템 부하 평균 | 부하 모니터링 |
| `/proc/diskstats` | 디스크 I/O 통계 | 디스크 활동 모니터링 |
| `/proc/net/dev` | 네트워크 인터페이스 통계 | 네트워크 트래픽 모니터링 |
| `/proc/[pid]/stat` | 프로세스 상태 정보 | 프로세스 CPU, 메모리 사용량 |
| `/proc/[pid]/cmdline` | 프로세스 실행 명령어 | 프로세스 식별 정보 |

## 구현 상세

### CPU 사용량 모니터링

/proc/stat 파일을 읽고 분석하여 CPU 사용률을 계산합니다.

```c
void monitor_cpu_usage() {
    FILE *fp;
    char buffer[1024];
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    unsigned long long total_jiffies1, total_jiffies2, work_jiffies1, work_jiffies2;
    float cpu_usage;
    
    // 첫 번째 측정
    fp = fopen("/proc/stat", "r");
    fgets(buffer, sizeof(buffer), fp);
    sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu", 
           &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);
    fclose(fp);
    
    work_jiffies1 = user + nice + system + irq + softirq + steal;
    total_jiffies1 = work_jiffies1 + idle + iowait;
    
    // 측정 간격을 두고 다시 측정
    usleep(500000); // 0.5초 대기
    
    fp = fopen("/proc/stat", "r");
    fgets(buffer, sizeof(buffer), fp);
    sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu", 
           &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);
    fclose(fp);
    
    work_jiffies2 = user + nice + system + irq + softirq + steal;
    total_jiffies2 = work_jiffies2 + idle + iowait;
    
    // CPU 사용률 계산
    cpu_usage = 100.0 * (work_jiffies2 - work_jiffies1) / (total_jiffies2 - total_jiffies1);
    
    printf("CPU Usage: %.2f%%\n", cpu_usage);
}
```

### 프로세스 정보 수집

/proc/[pid] 디렉토리를 스캔하여 모든 실행 중인 프로세스 정보를 수집합니다.

```c
void collect_process_info() {
    DIR *dir;
    struct dirent *entry;
    char path[256];
    char buffer[1024];
    FILE *fp;
    int pid;
    
    dir = opendir("/proc");
    if (!dir) {
        perror("opendir");
        return;
    }
    
    printf("%-6s %-15s %-8s %-8s %-8s %s\n", "PID", "USER", "CPU%", "MEM%", "VSZ", "COMMAND");
    
    while ((entry = readdir(dir)) != NULL) {
        // 숫자(PID)인 디렉토리만 처리
        if (entry->d_type == DT_DIR && isdigit(entry->d_name[0])) {
            pid = atoi(entry->d_name);
            
            // /proc/[pid]/stat 파일 읽기
            snprintf(path, sizeof(path), "/proc/%d/stat", pid);
            fp = fopen(path, "r");
            if (fp) {
                // 프로세스 stat 정보 파싱
                // ... 프로세스 정보 추출 및 처리 로직 ...
                fclose(fp);
                
                // 프로세스 정보 출력
                printf("%-6d %-15s %-8.1f %-8.1f %-8ld %s\n", 
                       pid, user, cpu_percent, mem_percent, vmsize/1024, cmdline);
            }
        }
    }
    
    closedir(dir);
}
```

## 사용자 인터페이스

ncurses 라이브러리를 활용하여 터미널 기반의 대화형 사용자 인터페이스를 구현했습니다. 실시간으로 업데이트되는 정보를 보기 쉽게 표시합니다.

```c
void init_ui() {
    initscr();             // ncurses 초기화
    start_color();         // 색상 지원 활성화
    cbreak();              // 라인 버퍼링 비활성화
    noecho();              // 사용자 입력 에코 비활성화
    keypad(stdscr, TRUE);  // 특수 키 활성화
    curs_set(0);           // 커서 숨기기
    timeout(1000);         // getch() 타임아웃 설정 (1초)
    
    // 색상 쌍 초기화
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
}
```

## 시스템 콜 직접 사용의 의미

이 프로젝트에서 고수준 라이브러리 대신 저수준 시스템 콜과 /proc 파일시스템을 직접 활용함으로써 다음과 같은 이점을 얻었습니다.

1. **커널 정보 직접 접근**: 커널이 제공하는 원시 정보에 직접 접근하여 가공되지 않은 데이터 획득
2. **최소한의 오버헤드**: 불필요한 추상화 계층 없이 필요한 정보만 효율적으로 수집
3. **리눅스 커널 내부 이해**: 시스템 통계가 어떻게 수집되고 관리되는지 이해

## 빌드 및 실행 방법

```bash
# 필요한 라이브러리 설치 (Ubuntu/Debian 기준)
sudo apt-get install libncurses5-dev

# 빌드
make

# 실행
./system-monitor
```

## 사용 예시

```
$ ./system-monitor

System Monitor v1.0
---------------------------------
Uptime: 5 days, 3 hours, 27 minutes
Kernel: Linux 5.4.0-42-generic
Load Average: 0.52, 0.58, 0.59

CPU Usage: 23.5%
[##########..................] 23.5%

Memory Usage: 3.2 GB / 15.6 GB (20.5%)
[########....................] 20.5%

Swap Usage: 0.1 GB / 2.0 GB (5.0%)
[##..........................] 5.0%

Disk I/O (sda):
  Read: 12.5 MB/s  Write: 3.2 MB/s

Network (eth0):
  RX: 1.2 MB/s    TX: 0.4 MB/s

[Process List]
PID    USER           CPU%    MEM%    VSZ     COMMAND
1234   root           3.2     2.1     128M    systemd
5678   alice          15.6    5.3     256M    firefox
...

Press 'q' to quit, 'p' to sort by CPU, 'm' to sort by memory
```

## 한계 및 개선 가능성

현재 구현에는 다음과 같은 한계가 있으며, 향후 개선할 수 있습니다.