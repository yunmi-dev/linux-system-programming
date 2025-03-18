#include <stdio.h>

/*
문자열 처리 함수 구현
*/

// 포인터 연산을 이용한 문자열 길이 계산 함수
int strlen_p(char *str)
{
	int	len = 0;

	// 문자열의 끝(NULL 문자)까지 포인터를 이동하며 길이 계산
	while (*str++)  {
		len++;
	}
	return len;
}

// 배열 인덱싱을 이용한 문자열 길이 계산 함수
int strlen_a(char str[])
{
	int i;

    // NULL 문자를 만날 때까지 인덱스 증가
	for (i = 0 ; str[i] != '\0' ; i++)
		;	// 빈 문장 (카운팅만 수행)
	return i;
}

// 포인터 연산을 이용한 문자열 복사 함수
void strcpy_p(char *dst, char *src)
{
	while (*src)  {
		*dst++ = *src++;
	}	// src의 모든 문자를 dst로 복사 (여기까지는 NULL 문자 제외)

	// NULL 문자도 복사하면서 문자열 종료 (교수님 강조)
	*dst = *src;
}

// 배열 인덱싱을 이용한 문자열 복사 함수
void strcpy_a(char dst[], char src[])
{
	int i;

	for (i = 0 ; src[i] != '\0' ; i++)
		dst[i] = src[i];	// NULL 문자 전까지 모든 문자 복사

	// NULL 문자도 복사하고 문자열 종료
	dst[i] = src[i];
}

// 포인터 연산을 이용한 문자열 연결 함수
void strcat_p(char *dst, char *src)
{
	// dst의 끝(NULL 문자)을 찾음
	while (*dst++)
		;

	dst--;	// NULL 문자 위치로 포인터 이동


	// src의 모든 문자를 dst 끝에 복사
	while (*src)  {
		*dst++ = *src++;
	}
	*dst = *src;	// NULL 문자로 새 문자열 종료
}	

// 배열 인덱싱을 이용한 문자열 연결 함수
void strcat_a(char dst[], char src[])
{
	int i, j;

	// dst의 끝(NULL 문자) 위치 찾기
	for (i = 0 ; dst[i] != '\0' ; i++)
		;
	
	// src의 모든 문자를 dst 끝에 복사
	for (j = 0 ; src[j] != '\0' ; j++)
		dst[i+j] = src[j];
	
	// NULL 문자로 새 문자열 종료
	dst[i+j] = src[j];
}

int main()
{
	int		len1, len2;
	char	str1[20], str2[20];

	// 문자열 길이 함수 테스트
	len1 = strlen_p("Hello");
	len2 = strlen_a("Hello");
	printf("strlen: p=%d, a=%d\n", len1, len2);

	// 문자열 복사 함수 테스트
	strcpy_p(str1, "Hello");
	strcpy_a(str2, "Hello");
	printf("strcpy: p=%s, a=%s\n", str1, str2);

	// 문자열 연결 함수 테스트
	strcat_p(str1, ", World!");
	strcat_a(str2, ", World!");
	printf("strcat: p=%s, a=%s\n", str1, str2);

	return 0;
}