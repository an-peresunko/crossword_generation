#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>

/*  1) �������� � ���������� ������������, ��������� ������ ����� �������� ���� �� ����� (��� amount_same > 2)
	2) ����� ����������� ������������ ����/������� ��� �������� ������ ����������� (�� ���� ��� ������� definitions)
	3) ���������, ��� ������� ������������� ����������
	*/







typedef struct base_of_words {
	char words[100][100];
	char definitions[100][1000];
}base;

int poisk(char symbol, char* word, int n) {  //����� ������� � �����
	for (int i = 0; i < n; i++) {
		if (word[i] == symbol) return 1; //�����
	}
	return 0;
}

int attempt_to_place_vert(int i, int j, int n, char symbol, char* word, char** arr) { //������� �������� ����� � ��������� �����������
	int k = 0; //������ �� �����
	int amount_same = 0;
	for (int i = 0; i < strlen(word); i++) {
		if (word[i] == symbol) break;
		k++;  //�� ����� ����� � ����� ����� ������ �����
	}
	int start = i - k;
	int end = i + strlen(word) - k;
	if (start < 0 || end - 1 >= n) return 0; //�������
	k = 0;
	for (int i = start; i < end; i++) {
		if (word[k] == arr[i][j]) amount_same++;
		if (amount_same > 2) return 0;
		k++;
	}
	k = 0;
	for (i = start; i < end; i++) {
		if (arr[i][j] != '.' && arr[i][j] != word[k]) return 0;
		if (j - 1 > -1)
			if (arr[i][j - 1] != '.' && arr[i][j] != word[k]) return 0;
		if (j + 1 > -1)
			if (arr[i][j + 1] != '.' && arr[i][j] != word[k]) return 0;
		k++;
	}
	if (arr[end][j] != '.') return 0;
	if (start - 1 > -1)
		if (arr[start - 1][j] != '.') return 0;
	return 1; //�����
}

int attempt_to_place_horiz(int i, int j, int m, char symbol, char* word, char** arr) { //������� �������� ����� � ��������� �������������
	int k = 0; //������ �� �����
	int amount_same = 0;
	for (int i = 0; i < strlen(word); i++) {
		if (word[i] == symbol) break;
		k++;
	}
	int start = j - k;
	int end = j + strlen(word) - k;
	if (start < 0 || end - 1 >= m) return 0; //�������
	k = 0;
	for (int j = start; j < end; j++) {
		if (word[k] == arr[i][j]) amount_same++;
		if (amount_same > 2) return 0;
		k++;
	}
	k = 0;
	for (j = start; j < end; j++) {
		if (arr[i][j] != '.' && arr[i][j] != word[k]) return 0;
		if (i - 1 > -1)
			if (arr[i - 1][j] != '.' && arr[i][j] != word[k]) return 0;
		if (i + 1 > -1)
			if (arr[i + 1][j] != '.' && arr[i][j] != word[k]) return 0;
		k++;
	}
	if (arr[i][end] != '.') return 0;
	if (start - 1 > -1)
		if (arr[i][start - 1] != '.') return 0;
	return 1; //�����
}


int main() {
	SetConsoleCP(1251); //��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleOutputCP(1251); //��������� ������� �������� win-cp 1251 � ����� ������

	base base = {
		.words = {"������������", "������", "�������", "�����", "������", "������", "���", "������", "������", "�������", "����������"},
		.definitions = {"����� ������", "��� ���� ������", "�������", "����� � ��������", "������� �����", "������� �� ����", "��� ����� �� �����", \
		"������� ��������", "�� ���� ����", "homo sapiens", "������� �������"}
	};

	char definitions[100][1000];
	int N, M;
	int i, j; // i - ������
	int count = 0;
	int tmp = 0;
	char temporary1[100], temporary2[100];
	int count_def = 0;

	// ���������� ���� ���� �� �������� �����
	for (i = 0; i < 11; i++) {
		for (j = 0; j < 10; j++) {
			if (strlen(base.words[j]) < strlen(base.words[j + 1])) {
				strcpy(temporary1, base.words[j]);
				strcpy(base.words[j], base.words[j + 1]);
				strcpy(base.words[j + 1], temporary1);

				strcpy(temporary2, base.definitions[j]);
				strcpy(base.definitions[j], base.definitions[j + 1]);
				strcpy(base.definitions[j + 1], temporary2);
			}
		}
	}

	/*for (i = 0; i < 11; i++) {
		printf("%s - %s\n", base.words[i], base.definitions[i]);
	}

	return 0; */

	printf("������� ������ ����:");
	scanf("%d", &N);//������
	printf("������� ������ ����:");
	scanf("%d", &M);//�������
	char** crossword = (char**)malloc(N * sizeof(char*));
	for (i = 0; i < N; i++) {
		crossword[i] = (char*)malloc(M * sizeof(char));
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			crossword[i][j] = '.';
		}
	}

	//������ ������ �����

	i = N / 4;
	int start = N / 4;
	int end = N / 4 + strlen(base.words[0]);
	for (j = start; j < end; j++) {
		crossword[i][j] = base.words[0][tmp];
		tmp++;
	}
	strcpy(definitions[count_def], base.definitions[0]);
	count_def++;


	//������ ��������� �����

	for (count = 1; count < 11; count++) { //count - ���������� ������������� ����
		for (i = 0; i < N; i++) {
			for (j = 0; j < M; j++) {
				if (crossword[i][j] != '.') {
					if (poisk(crossword[i][j], base.words[count], N) == 1) {
						if (attempt_to_place_vert(i, j, N, crossword[i][j], base.words[count], crossword) == 1) {
							int k = 0; //������ �� �����
							for (int m = 0; m < strlen(base.words[count]); m++) {
								if (base.words[count][m] == crossword[i][j]) break;
								k++;
							}
							start = i - k;
							end = i + strlen(base.words[count]) - k;
							k = 0;
							for (i = start; i < end; i++) {
								crossword[i][j] = base.words[count][k];
								k++;
							}
							strcpy(definitions[count_def], base.definitions[count]);
							count_def++;
							for (i = 0; i < strlen(base.words[count]); i++) {
								base.words[count][i] = '0';
							}
						}
						else if (attempt_to_place_horiz(i, j, M, crossword[i][j], base.words[count], crossword) == 1) {
							int k = 0; //������ �� �����
							for (int m = 0; m < strlen(base.words[count]); m++) {
								if (base.words[count][m] == crossword[i][j]) break;
								k++;
							}
							start = j - k;
							end = j + strlen(base.words[count]) - k;
							k = 0;
							for (j = start; j < end; j++) {
								crossword[i][j] = base.words[count][k];
								k++;
							}
							strcpy(definitions[count_def], base.definitions[count]);
							count_def++;
							for (j = 0; j < strlen(base.words[count]); j++) {
								base.words[count][j] = '0';
							}
						}
					}
				}
			}
		}
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			printf("%c  ", crossword[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (i = 0; i < count_def; i++) {
		printf("%d - %s\n", i, definitions[i]);
	}

	for (i = 0; i < N; i++) {   //������������ ������
		free(crossword[i]);
	}
	free(crossword);

	return 0;
}