#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Node {
	char text[100];
	struct Node* next;

};
struct Node* undo_top = NULL;
struct Node* rendo_top = NULL;
char current_text[100] ="";
void push_undo(char* text) {
	struct Node* NewNode = (struct Node*)malloc(sizeof(struct Node));
	strcpy(NewNode->text, text);
	NewNode->next = undo_top;
	undo_top = NewNode;
}
void push_rendo(char* text) {
	struct Node* NewNode = (struct Node*)malloc(sizeof(struct Node));
	strcpy(NewNode->text, text);
	NewNode->next = rendo_top;
	rendo_top = NewNode;
}
char* PoP_undo() {
	if (undo_top == NULL)return NULL;
	char* text = (char*)malloc(100);
	
	struct Node* tmp = undo_top;
	strcpy(text, tmp->text);
    undo_top = undo_top->next;
	
	free(tmp);
	return(text);

}
char* PoP_rendo() {
	if (rendo_top == NULL)return NULL;
	struct Node* tmp = rendo_top;
	char* text1 = (char*)malloc(100);
	strcpy(text1, tmp->text);
	rendo_top = rendo_top->next;
	
	free(tmp);
	return(text1);
}
int isempty_undo() {  
	return (undo_top == NULL);  
}
int isempty_rendo() {  
	return (rendo_top == NULL);
}
void add_text() {
	push_undo(current_text);
	char new_text[100];
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	
	printf("Enter text(pealse make space for next word)\n");
	printf(">>>\t");
	gets_s(new_text, 100);
	printf("\n");
	
	strcat(current_text,new_text);
	
	while (rendo_top != NULL) {
		char* temp = PoP_rendo();
		free(temp);
	}
	
	printf("Your text:%s\n ", current_text);
	
	
	
}
void delete_last_n() {
	if (strlen(current_text) == 0) {  
		printf("Error: Nothing to delete - text is empty\n");
		return;
	}
	push_undo(current_text);
	int n;
	int len=0;
	char* p1;
	p1 = current_text;
	while (*p1 !='\0') {
		len++;
		p1++;

	}
	
	
	printf("Enter amount of symbols to delete\n");
	scanf_s("%d", &n);
	if (n > len) {
		n = len;
	}
	else if (n < 0) {
		printf("Invalid chooise\n");
		return;
	}
	
	
	current_text[len - n] = '\0';

	
	while (rendo_top != NULL) {
		char* temp = PoP_rendo();
		free(temp);
	}
	printf("Deleted %d symbols from the end\n", n);
	printf("Your text:%s", current_text);



}
void undo() {
	if (undo_top == NULL) {
		printf("Nothing to undo\n");
		return;
	}
	char* old_text;
	push_rendo(current_text);
	old_text= PoP_undo();
	strcpy(current_text, old_text);
	free(old_text);
	printf("Undo successful! Text: %s\n", current_text);






}
void rendo() {
	if (rendo_top == NULL) {
		printf("Nothing to rendo\n");
		return;
	}
	push_undo(current_text);
	char* temp;
	temp = PoP_rendo();
	strcpy(current_text, temp);
	free(temp);
	printf("Redo successful! Text: %s\n", current_text);

}
void show_history() {
	if (undo_top == NULL) {
		printf("Empty\n");
		

	}
	else {
		printf(" === UNDO HISTORY === \n");
		struct Node* tmp = undo_top;
		int count = 1;
		while (tmp != NULL) {
			printf("%d. \"%s\"\n", count, tmp->text);
			count++;
			tmp = tmp->next;

		}
	}
	if (rendo_top == NULL) {
		printf("Empty\n");
		

	}
	else {
		printf(" === Rendo HISTORY === \n");
		struct Node* tmp1 = rendo_top;
		int count1 = 1;
		while (tmp1 != NULL) {
			printf("%d. \"%s\"\n", count1, tmp1->text);
			count1++;
			tmp1 = tmp1->next;

		}
	}
	


	

}   
void save_data_to_file() {
	FILE* fp;
	fp = fopen("text_edit.txt", "w");
	if (fp == NULL) {
		printf(" Error: Could not open file for writing!\n");
		return;
	}
	fprintf(fp,"%s", current_text);
	printf("Data saved successfully!\n");
	fclose(fp);




}
void load_data_from_file() {
	FILE* fp;
	fp = fopen("text_edit.txt", "r");
	if (fp == NULL) {
		printf(" Error: Could not open file for reading!\n");
		return;
	}
	push_undo(current_text);
	fgets(current_text, 100, fp);
	while (rendo_top != NULL) {
		char* temp = PoP_rendo();
		free(temp);
	}
	printf("Data loaded successfully!\n");
	fclose(fp);



}
void free_all() {
	while (undo_top != NULL) {
		char* tmp = PoP_undo();
		free(tmp);

	}
	while (rendo_top != NULL) {
		char* tmp1 = PoP_rendo();
		free(tmp1);


	}
}
int main() {
		int choice;
		char pp[4];

		
		while (1) {
			printf("============================================\n");
			printf("           TEXT EDITOR WITH UNDO/REDO      \n");
			printf("============================================\n");
			printf("Current text: [%s]\n\n", current_text);
			printf("1. Add text\n");
			printf("2. Delete last N characters\n");
			printf("3. Undo\n");
			printf("4. Redo\n");
			printf("5. Show history\n");
			printf("6. Save to file\n");
			printf("7. Load from file\n");
			printf("0. Exit\n");
			printf(">> ");
			scanf_s("%d", &choice);
			
			switch (choice) {
			case 1:
				add_text();
				break;
			case 2:
				delete_last_n();
				break;
			case 3:
				undo();
				break;
			case 4:
				rendo();
				break;
			case 5:
				show_history();
				break;
			
			case 6:
				load_data_from_file();
				break;
			case 0:
				printf("Save before exit?(y/n)\n");
				scanf_s("%3s", pp, 4);
				if (strcmp(pp, "Yes") == 0 || strcmp(pp, "yes") == 0) {
					save_data_to_file();
				}
			 	free_all();
				printf("Goodbye!\n");
				return 0;
				


				


			}
			
		

			
		}

		
}
	
		

