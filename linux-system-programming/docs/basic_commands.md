# 리눅스 기본 개념 및 명령어

이 섹션에서는 리눅스 시스템 프로그래밍의 기초가 되는 리눅스 기본 개념과 명령어를 다룹니다. 백엔드/클라우드 개발자로서 리눅스 환경에 대한 깊은 이해는 필수적입니다.

## 목차

1. [리눅스 개요](#리눅스-개요)
2. [파일 시스템 기본 명령어](#파일-시스템-기본-명령어)
3. [텍스트 처리 명령어](#텍스트-처리-명령어)
4. [프로세스 관리 명령어](#프로세스-관리-명령어) 
5. [네트워크 관련 명령어](#네트워크-관련-명령어)
6. [사용자 및 권한 관리](#사용자-및-권한-관리)
7. [쉘 스크립팅 기초](#쉘-스크립팅-기초)
8. [시스템 모니터링 및 관리](#시스템-모니터링-및-관리)

## 리눅스 개요

리눅스는 1991년 리누스 토발즈가 개발한 오픈 소스 운영체제입니다. 현재 서버 시장의 대부분을 차지하고 있으며, 클라우드 인프라의 기반이 되는 운영체제입니다.

### 리눅스의 주요 특징

- **오픈 소스**: 소스 코드가 공개되어 있어 누구나 수정, 배포 가능
- **다중 사용자, 다중 태스킹**: 여러 사용자가 동시에 다양한 작업 수행 가능
- **높은 안정성과 보안성**: 서버 환경에 적합한 안정적인 시스템
- **유연성**: 다양한 하드웨어와 용도에 맞게 구성 가능
- **표준화된 인터페이스**: POSIX 표준을 따라 다양한 시스템 간 호환성 제공

### 주요 리눅스 배포판

- **Ubuntu**: 사용자 친화적, 데스크탑과 서버 모두 인기
- **CentOS/RHEL**: 기업 환경에서 많이 사용, 안정성 중시
- **Debian**: 안정성과 자유 소프트웨어 철학 강조
- **Fedora**: 최신 기술 빠르게 도입, RHEL의 테스트베드
- **Alpine**: 경량화에 중점, 컨테이너 환경에 많이 사용

## 파일 시스템 기본 명령어

리눅스에서 파일과 디렉토리를 관리하는 기본 명령어들입니다.

| 명령어 | 설명 | 주요 옵션 | 예제 |
|--------|------|-----------|------|
| `ls` | 디렉토리 내용 출력 | `-l`: 상세 정보<br>`-a`: 숨김 파일 포함<br>`-h`: 사람이 읽기 쉬운 크기 | `ls -la` |
| `cd` | 디렉토리 변경 | | `cd /home/user`<br>`cd ..` (상위 디렉토리) |
| `pwd` | 현재 작업 디렉토리 표시 | | `pwd` |
| `mkdir` | 디렉토리 생성 | `-p`: 경로상 없는 디렉토리 모두 생성 | `mkdir -p dir1/dir2` |
| `rmdir` | 빈 디렉토리 삭제 | | `rmdir dir1` |
| `rm` | 파일이나 디렉토리 삭제 | `-r`: 재귀적 삭제<br>`-f`: 강제 삭제 | `rm -rf dir1` |
| `cp` | 파일이나 디렉토리 복사 | `-r`: 재귀적 복사 | `cp -r src_dir dest_dir` |
| `mv` | 파일이나 디렉토리 이동/이름변경 | | `mv file1 file2`<br>`mv file1 dir1/` |
| `touch` | 빈 파일 생성 또는 수정 시간 갱신 | | `touch newfile.txt` |
| `find` | 파일이나 디렉토리 검색 | `-name`: 이름으로 검색<br>`-type`: 타입으로 검색 | `find . -name "*.c"` |

### 파일 시스템 구조

리눅스의 표준 디렉토리 구조와 각 디렉토리의 용도:

- `/bin`: 기본 실행 파일
- `/etc`: 시스템 설정 파일
- `/home`: 사용자 홈 디렉토리
- `/var`: 가변 데이터 (로그 등)
- `/usr`: 사용자 프로그램과 데이터
- `/tmp`: 임시 파일
- `/proc`: 프로세스 정보 (가상 파일 시스템)
- `/dev`: 장치 파일

## 텍스트 처리 명령어

리눅스에서 텍스트 파일을 다루는 명령어들입니다.

| 명령어 | 설명 | 주요 옵션 | 예제 |
|--------|------|-----------|------|
| `cat` | 파일 내용 출력 | `-n`: 라인 번호 표시 | `cat file.txt` |
| `less` | 파일 내용 페이지 단위로 보기 | | `less file.txt` |
| `head` | 파일 앞부분 출력 | `-n`: 라인 수 지정 | `head -n 20 file.txt` |
| `tail` | 파일 뒷부분 출력 | `-n`: 라인 수 지정<br>`-f`: 파일 실시간 모니터링 | `tail -f log.txt` |
| `grep` | 문자열 패턴 검색 | `-i`: 대소문자 무시<br>`-r`: 재귀적 검색 | `grep -r "error" .` |
| `sed` | 스트림 편집기 | `-i`: 파일 직접 수정 | `sed 's/old/new/g' file.txt` |
| `awk` | 패턴 검색 및 처리 언어 | | `awk '{print $1}' file.txt` |
| `sort` | 텍스트 파일 정렬 | `-n`: 숫자 정렬<br>`-r`: 역순 정렬 | `sort -n file.txt` |
| `wc` | 라인, 단어, 문자 수 계산 | `-l`: 라인 수만 표시 | `wc -l file.txt` |
| `diff` | 파일 비교 | | `diff file1.txt file2.txt` |

### 텍스트 편집기

- **vi/vim**: 가장 많이 사용되는 텍스트 편집기, 모든 리눅스 시스템에 기본 설치
- **nano**: 초보자에게 친숙한 간단한 편집기
- **emacs**: 강력한 기능을 갖춘 확장 가능한 편집기

## 프로세스 관리 명령어

프로세스를 모니터링하고 제어하는 명령어들입니다.

| 명령어 | 설명 | 주요 옵션 | 예제 |
|--------|------|-----------|------|
| `ps` | 프로세스 상태 표시 | `-ef`: 모든 프로세스 상세 정보<br>`-aux`: BSD 스타일로 모든 프로세스 | `ps -ef` |
| `top` | 실시간 프로세스 모니터링 | | `top` |
| `htop` | 향상된 top (설치 필요) | | `htop` |
| `kill` | 프로세스 종료 신호 전송 | `-9`: 강제 종료 | `kill -9 1234` |
| `pkill` | 이름으로 프로세스 종료 | | `pkill firefox` |
| `killall` | 모든 동일 이름 프로세스 종료 | | `killall firefox` |
| `nice` | 프로세스 우선순위 지정 실행 | | `nice -n 10 ./program` |
| `renice` | 실행 중 프로세스 우선순위 변경 | | `renice -n 10 -p 1234` |
| `nohup` | 로그아웃 후에도 프로세스 유지 | | `nohup ./program &` |
| `bg` | 프로세스 백그라운드로 보내기 | | `bg` |
| `fg` | 백그라운드 프로세스 포그라운드로 가져오기 | | `fg` |
| `jobs` | 백그라운드 작업 목록 표시 | | `jobs` |

### 프로세스 관련 개념

- **PID (Process ID)**: 각 프로세스의 고유 식별자
- **PPID (Parent Process ID)**: 부모 프로세스 ID
- **데몬 (Daemon)**: 백그라운드에서 실행되는 서비스 프로세스
- **좀비 프로세스**: 종료되었지만 부모가 wait()를 호출하지 않은 프로세스
- **시그널**: 프로세스 간 통신 메커니즘 (SIGTERM, SIGKILL 등)

## 네트워크 관련 명령어

네트워크 구성과 모니터링을 위한 명령어들입니다.

| 명령어 | 설명 | 주요 옵션 | 예제 |
|--------|------|-----------|------|
| `ifconfig` | 네트워크 인터페이스 설정 (레거시) | | `ifconfig eth0` |
| `ip` | 네트워크 인터페이스 설정 (최신) | | `ip addr show` |
| `ping` | ICMP 에코 요청으로 연결 확인 | `-c`: 패킷 수 제한 | `ping -c 4 google.com` |
| `traceroute` | 패킷 경로 추적 | | `traceroute google.com` |
| `netstat` | 네트워크 연결, 라우팅 테이블 등 표시 | `-tuln`: TCP/UDP 리스닝 포트 | `netstat -tuln` |
| `ss` | 소켓 통계 (netstat 대체) | | `ss -tuln` |
| `dig` | DNS 조회 | | `dig google.com` |
| `nslookup` | 이름 서버 조회 | | `nslookup google.com` |
| `curl` | URL로 데이터 전송/수신 | `-O`: 원본 파일명으로 저장 | `curl -O https://example.com/file` |
| `wget` | 네트워크를 통한 파일 다운로드 | `-r`: 재귀적 다운로드 | `wget -r https://example.com` |

### 방화벽 명령어 (iptables/firewalld)

- **iptables**: 리눅스 커널 방화벽 설정
  ```bash
  iptables -L  # 현재 규칙 목록
  iptables -A INPUT -p tcp --dport 80 -j ACCEPT  # HTTP 트래픽 허용
  ```

- **firewalld** (CentOS/RHEL 기본):
  ```bash
  firewall-cmd --list-all  # 현재 설정 표시
  firewall-cmd --permanent --add-service=http  # HTTP 서비스 허용
  ```

## 사용자 및 권한 관리

사용자 계정과 파일 권한을 관리하는 명령어들입니다.

| 명령어 | 설명 | 주요 옵션 | 예제 |
|--------|------|-----------|------|
| `useradd` | 사용자 계정 생성 | `-m`: 홈 디렉토리 생성 | `useradd -m username` |
| `userdel` | 사용자 계정 삭제 | `-r`: 홈 디렉토리 함께 삭제 | `userdel -r username` |
| `passwd` | 사용자 비밀번호 변경 | | `passwd username` |
| `groupadd` | 그룹 생성 | | `groupadd groupname` |
| `usermod` | 사용자 계정 수정 | `-a -G`: 그룹 추가 | `usermod -a -G groupname username` |
| `chmod` | 파일 권한 변경 | | `chmod 755 file.txt`<br>`chmod u+x file.sh` |
| `chown` | 파일 소유자 변경 | `-R`: 재귀적 변경 | `chown -R user:group dir1` |
| `chgrp` | 파일 그룹 변경 | | `chgrp groupname file.txt` |
| `sudo` | 다른 사용자 권한으로 명령 실행 | `-u`: 사용자 지정 | `sudo -u user command` |
| `su` | 다른 사용자로 전환 | `-`: 환경변수 포함 전환 | `su - username` |

### 파일 권한 시스템

리눅스 파일 권한은 소유자(u), 그룹(g), 기타(o)에 대한 읽기(r), 쓰기(w), 실행(x) 권한으로 구성됩니다.

- **권한 표기 방식**:
  - 기호 표기: `rwxrw-r--`
  - 숫자 표기: `764` (4=읽기, 2=쓰기, 1=실행)

- **특수 권한**:
  - SetUID (4000): 실행 시 소유자 권한으로 실행
  - SetGID (2000): 실행 시 그룹 권한으로 실행
  - Sticky Bit (1000): 공유 디렉토리에서 다른 사용자의 파일 삭제 방지

## 쉘 스크립팅 기초

쉘 스크립팅은 리눅스 환경에서 자동화와 시스템 관리에 필수적인 도구입니다.

### 기본 스크립트 구조

```bash
#!/bin/bash
# 이것은 주석입니다

echo "Hello, World!"

# 변수 선언 및 사용
NAME="Linux"
echo "Hello, $NAME"

# 조건문
if [ "$NAME" = "Linux" ]; then
    echo "Name is Linux"
else
    echo "Name is not Linux"
fi

# 반복문
for i in {1..5}; do
    echo "Iteration: $i"
done

# 함수 정의 및 호출
function greet() {
    echo "Hello, $1"
}

greet "Friend"

# 명령어 실행 결과 저장
CURRENT_DIR=$(pwd)
echo "Current directory: $CURRENT_DIR"

# 종료 상태 코드 반환
exit 0
```

### 주요 쉘 스크립팅 기능

- **변수**: 값 저장 및 참조
- **조건문**: `if`, `case` 등으로 조건 분기
- **반복문**: `for`, `while`, `until`로 반복 작업
- **함수**: 재사용 가능한 코드 블록
- **입출력 리다이렉션**: `>`, `>>`, `<`, `|` 등으로 입출력 제어
- **명령어 치환**: `$(command)` 또는 `` `command` ``로 명령어 결과 사용
- **인자 처리**: `$1`, `$2`, `$@` 등으로 스크립트 인자 접근

## 시스템 모니터링 및 관리

시스템 상태를 모니터링하고 관리하는 명령어들입니다.

| 명령어 | 설명 | 주요 옵션 | 예제 |
|--------|------|-----------|------|
| `df` | 디스크 공간 사용량 표시 | `-h`: 사람이 읽기 쉬운 형식 | `df -h` |
| `du` | 디렉토리 공간 사용량 표시 | `-sh`: 요약, 읽기 쉬운 형식 | `du -sh /var` |
| `free` | 메모리 사용량 표시 | `-h`: 읽기 쉬운 형식 | `free -h` |
| `vmstat` | 가상 메모리 통계 | `-s`: 요약 정보 | `vmstat 1 5` |
| `iostat` | CPU 및 I/O 통계 | | `iostat` |
| `sar` | 시스템 활동 보고서 | `-u`: CPU 사용량 | `sar -u 1 5` |
| `uptime` | 시스템 가동 시간 및 부하 | | `uptime` |
| `w` | 로그인 중인 사용자 및 활동 | | `w` |
| `who` | 로그인 중인 사용자 | | `who` |
| `last` | 최근 로그인 기록 | | `last` |
| `dmesg` | 커널 메시지 출력 | | `dmesg | grep -i error` |
| `journalctl` | systemd 저널 로그 조회 | `-u`: 유닛별 필터링 | `journalctl -u nginx` |
| `systemctl` | systemd 서비스 관리 | | `systemctl status sshd` |

### 서비스 관리 (systemd)

현대 리눅스 배포판은 대부분 systemd를 사용하여 서비스를 관리합니다.

```bash
# 서비스 상태 확인
systemctl status nginx

# 서비스 시작/중지/재시작
systemctl start nginx
systemctl stop nginx
systemctl restart nginx

# 부팅 시 서비스 자동 시작 설정
systemctl enable nginx
systemctl disable nginx

# 모든 서비스 목록 표시
systemctl list-unit-files --type=service
```

## 유용한 팁 및 트릭

### 명령어 히스토리 활용
```bash
history         # 명령어 히스토리 표시
!42             # 히스토리의 42번 명령어 실행
!!              # 직전 명령어 반복
!grep           # 최근 grep 명령어 반복
Ctrl+R          # 히스토리 검색
```

### 작업 제어
```bash
command &       # 백그라운드로 실행
Ctrl+Z          # 현재 작업 일시 중지
bg              # 중지된 작업 백그라운드로 계속
fg              # 백그라운드 작업 포그라운드로 가져오기
```

### 파일 압축 및 아카이브
```bash
tar -czf archive.tar.gz directory/   # 디렉토리 압축 (gzip)
tar -xzf archive.tar.gz              # 압축 해제 (gzip)
tar -cjf archive.tar.bz2 directory/  # 디렉토리 압축 (bzip2)
tar -xjf archive.tar.bz2             # 압축 해제 (bzip2)
zip -r archive.zip directory/        # 디렉토리 zip 압축
unzip archive.zip                    # zip 압축 해제
```

### 효율적인 파일 탐색
```bash
find . -name "*.log" -mtime -7       # 7일 이내 수정된 로그 파일 찾기
find . -size +100M                   # 100MB 이상 파일 찾기
find . -name "*.tmp" -delete         # tmp 파일 찾아서 삭제
```

## 결론

리눅스 기본 명령어와 개념에 대한 이해는 시스템 프로그래밍의 기초가 되며, 백엔드 및 클라우드 개발자에게 필수적인 역량입니다. 이 문서에서 다룬 내용은 앞으로의 리눅스 시스템 프로그래밍 학습의 기반이 될 것입니다.

다음 섹션에서는 이러한 기본 명령어와 개념을 바탕으로 파일 입출력, 프로세스 관리, 스레드 프로그래밍 등 고급 시스템 프로그래밍 주제를 살펴보겠습니다.