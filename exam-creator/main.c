#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RESULT_FILE_NAME 	"exam.txt"
#define MAX_NUMBER_OF_QUESTION 1000
#define MAX_NUMBER_OF_ANSWER 	5

struct Question {
	char content[255];
	char answers[MAX_NUMBER_OF_ANSWER][255];
};

void initQuestionArray(struct Question* questionList, int numberOfQuestion, int numberOfAnswer) {
	for (int i = 0; i < numberOfQuestion; i++) {
		strcpy(questionList[i].content, "");
		for (int j = 0; j < numberOfAnswer; j++) {
			strcpy(questionList[i].answers[j], "");
		}
	}
}

int saveQuestionFileToArray(char* questionFileName, struct Question* questionList) {
	FILE *questionFile = fopen(questionFileName, "r");
	
	if (!questionFile || !questionList) return 0;
	
	char spam[100], content[255];
	char c;
	int numberOfQuestion = 0;
	
	do {
		fscanf(questionFile, "%[^:]s", spam);
		fgetc(questionFile);
		fgetc(questionFile);
		fscanf(questionFile, "%[^\n]s", questionList[numberOfQuestion].content);
		fgetc(questionFile);
		
		c = fgetc(questionFile);
		int i = 0;
		while (c != '\n' && c != EOF) {
			fgetc(questionFile);
			fgetc(questionFile);
			fscanf(questionFile, "%[^\n]s", questionList[numberOfQuestion].answers[i++]);
			fgetc(questionFile);
			c = fgetc(questionFile);
		}
		numberOfQuestion += 1;
	} while (c != EOF);

	fclose(questionFile);
	
	return numberOfQuestion;
}

void saveQuestionArrayToFile(struct Question* questionList, int numberOfQuestion, char* resultFileName) {
	FILE *resultFile = fopen(resultFileName, "w");
	char expression[5] = {'a', 'b', 'c', 'd', 'e'};
	
	if (!resultFile) return;
	
	for (int i = 0; i < numberOfQuestion; i++) {
		fprintf(resultFile, "Câu %d : %s\n", i+1, questionList[i].content);
		for (int j = 0; strlen(questionList[i].answers[j]) > 0; j++) {
			fprintf(resultFile, "%c. %s\n", expression[j], questionList[i].answers[j]);
		}
		fputc('\n', resultFile);
	}
	
	fclose(resultFile);
}

int addToArrayIfNotExists(int* array, int arraySize, int value) {
	for (int i = 0; i < arraySize; i++) {
		if (value == array[i]) return 0;
	}
	array[arraySize] = value;
	
	return 1;
}

void selectRandomQuestionFromQuestionList(struct Question *questionList, int numberOfQuestion, 
				struct Question *selectedQuestions, int numberOfSelect) {
	int questionSelected[1000] = {-1};
	int numberOfQuestionSelected = 0;
	
	if (!questionList || !selectedQuestions) return;
	
	while (numberOfQuestionSelected < numberOfSelect) {
		srand(time(NULL));
		int random = rand() % numberOfQuestion;
		if (addToArrayIfNotExists(questionSelected, numberOfQuestionSelected, random)) {
			selectedQuestions[numberOfQuestionSelected++] = questionList[random];
		}
	}
}

void createExam(char* questionFileName, int numberOfQuestion) {
	struct Question questionList[MAX_NUMBER_OF_QUESTION];
	struct Question exam[MAX_NUMBER_OF_QUESTION];
		
	initQuestionArray(questionList, MAX_NUMBER_OF_QUESTION, MAX_NUMBER_OF_ANSWER);
	initQuestionArray(exam, numberOfQuestion, MAX_NUMBER_OF_ANSWER);
	
	int n = saveQuestionFileToArray(questionFileName, questionList);
	
	if (n < numberOfQuestion) {
		printf("ERROR : number of question in %s less than %d\n", questionFileName, numberOfQuestion);
		return;
	}
	
	selectRandomQuestionFromQuestionList(questionList, n, exam, numberOfQuestion);
	saveQuestionArrayToFile(exam, numberOfQuestion, RESULT_FILE_NAME);
}

int main(int argc, char** argv) {
	if (argc == 4 && !strcmp(argv[1], "create_exam")) {
		createExam(argv[2], atoi(argv[3]));
	} else {
		printf("ERROR : enter create_exam question_file_name number_of_question_in_exam\n");
		printf("example : create_exam question.txt 30\n");
	}
}


























