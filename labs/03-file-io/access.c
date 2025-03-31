/*
학생 레드 파일 처리 프로그램
*/ 

#include <stdio.h>
#include <unistd.h>
#include "record.h"

void print_record(Record *rp)
{
	puts(rp->stud);	// 학생 이름 출력
	puts(rp->num);	// 학번 출력
	puts(rp->dept);	// 학과 출력
}

int main(int argc, char *argv[])
{
	FILE	*fp;	// 파일 포인터
	Record	rec;	// 레코드 구조체 변수

	if (argc != 2)  {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}

	if ((fp = fopen(argv[1], "r+b")) == NULL)  {	// r+b: 읽기와 쓰기가 모두 가능한 이진파일 모드
		perror("fopen");	// 파일열기 실패 시 에러 메시지 출력
		exit(1);
	}

	printf("-----Ordered Record List-----\n");

	// 파일의 모든 레코드를 순차적으로 읽어서 출력
	while (fread(&rec, sizeof(rec), 1, fp))  {
		print_record(&rec);
	}

	// 파일 포인터를 파일의 시작 위치로 되돌림
	rewind(fp);

	// 사용자 입력 대기 (Enter 키를 누를 때까지)
	getchar();

	printf("-----Shuffled Record List-----\n");

	// fseek 함수를 사용하여 파일 내 특정 위치로 이동 후 레코드 읽음
	fseek(fp, sizeof(rec)*2L, SEEK_SET);	// SEEK_SET: 파일의 시작 위치 기준
	fread(&rec, sizeof(rec), 1, fp);		// 레코드 읽기
	print_record(&rec);						// 레코드 출력

	// 다른 위치의 레코드들을 순서를 바꿔가며 읽고 출력
	fseek(fp, sizeof(rec)*5L, SEEK_SET);	// 6번째 레코드
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);

	fseek(fp, sizeof(rec)*1L, SEEK_SET);	// 2번째 레코드
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);

	fseek(fp, sizeof(rec)*3L, SEEK_SET);	// 4번째 레코드
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);

	fseek(fp, sizeof(rec)*0L, SEEK_SET);	// 1번째 레코드
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);

	fseek(fp, sizeof(rec)*4L, SEEK_SET);	// 5번째 레코드
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);

	// 사용자 입력 대기
	getchar();

	printf("-----Updated Record List-----\n");

	// 3번째 레코드의 학과정보를 'Movie'로 변경
	fseek(fp, sizeof(rec)*2L, SEEK_SET);	// 3번째 레코드 위치로 이동
	fread(&rec, sizeof(rec), 1, fp);		// 레코드 읽기
	strcpy(rec.dept, "Movie");				// 학과 정보 변경
	fseek(fp, sizeof(rec)*2L, SEEK_SET);	// 같은 위치로 다시 이동
	fwrite(&rec, sizeof(rec), 1, fp);		// 수정된 레코드 저장

	// 비슷하게 반복
	fseek(fp, sizeof(rec)*5L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	strcpy(rec.dept, "Baseball");
	fseek(fp, sizeof(rec)*5L, SEEK_SET);
	fwrite(&rec, sizeof(rec), 1, fp);

	// 파일 포인터를 파일의 시작 위치로 되돌림
	rewind(fp);

	// 수정된 모든 레코드 출력
	while (fread(&rec, sizeof(rec), 1, fp))  {
		print_record(&rec);
	}

	// 파일 닫기
	fclose(fp);

    return 0;
}