/*
학생 정보 저장하기 위한 구조체 정의
*/

#define	SMAX	20
#define	NMAX	10
#define	DMAX	15

typedef struct {
	char	stud[SMAX];
	char	num[NMAX];
	char	dept[DMAX];
} Record;