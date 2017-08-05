#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	char *expression = NULL;
};

int isdigit(char c){
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

int calculate(int a, int b, char op){
	if (op == '+')
		return a + b;
	else if (op == '-')
		return a - b;
	else if (op == '*')
		return a*b;
	

}
//malloc does not intialize value
//calloc intialize values with null
int evaluate(struct node **excel_array,char *str){
	int dest_x, dest_y, sum, i, operand,total,operand2,op;
	//printf("%s", str);
	if (*str!=NULL){
		i = 0;
		sum = 0;
		if (isdigit(str[i])){
			while (isdigit(str[i]) == 1 && str[i] != '\0'){
				sum = sum * 10 + str[i] - '0';
				i++;
			}
			operand = sum;
		}
		else{
			dest_x = str[i++] - 'a';
			sum = 0;
			while (str[i] != '\0' && isdigit(str[i])){
				sum = sum * 10 + str[i] - '0';
				i++;
			}
			dest_y = sum;
			operand = evaluate(excel_array, excel_array[dest_x][dest_y].expression);

		}
		total = operand;
		if (str[i] != '\0'){
			while (str[i] != '\0'){
				op = str[i] ;
				i++;
				if (isdigit(str[i])){
					sum = 0;
					while (isdigit(str[i]) == 1 && str[i] != '\0'){
						sum = sum * 10 + str[i] - '0';
						i++;
					}
					operand2 = sum;
				}
				else{
					dest_x = str[i++] - 'a';
					sum = 0;
					while (str[i] != '\0' && isdigit(str[i])){
						sum = sum * 10 + str[i] - '0';
						i++;
					}
					dest_y = sum;
					operand2 = evaluate(excel_array, excel_array[dest_x][dest_y].expression);

				}
				total = calculate(total, operand2, op);
			}
		}
		return total;

	}
	else
		return 0;

}


void save_to_file(struct node** excel_array){
	FILE *fp = fopen("excel_write.txt", "w");
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++){
			if (strcmp(excel_array[i][j].expression, "") != 0){
				printf("\n%s", excel_array[i][j].expression);


				fprintf(fp, "%c%d=%s\n",i+97,j,excel_array[i][j].expression);
			}
		}
	fclose(fp);
}

void load_from_file(struct node **excel_array){
	char temp1_str[40];
	int dest_x = 0, dest_y = 0, sum = 0,k=0,temp_k,temp_index=0,i=0;
	FILE *fp = fopen("excel_write.txt", "r");
	while (!feof(fp)){
		k = 0;
		temp_index = 0;
		fscanf(fp, "%[^\n]\n", temp1_str);
		if (temp1_str[0] == 'S'&& temp1_str[3]=='F'){
			i = 5;
			if (temp1_str[7] == '='){
				dest_x = temp1_str[5] - 'a';
				dest_y = temp1_str[6] - '0';
				k = 8;
			}
			else{
				dest_x = temp1_str[5] - 'a';
				dest_y = temp1_str[6] - '0';
				dest_y = (dest_y * 10) + temp1_str[7] - '0';
				k = 9;



			}

		}
		else if (temp1_str[0] == 'S'){
			i = 4;
			if (temp1_str[6] == '='){
				dest_x = temp1_str[4] - 'a';
				dest_y = temp1_str[5] - '0';
				k = 7;
			}
			else{
				dest_x = temp1_str[4] - 'a';
				dest_y = temp1_str[5] - '0';
				dest_y = (dest_y * 10) + temp1_str[6] - '0';
				k = 8;



			}



		}
		else if (temp1_str[2] == '='){
			dest_x = temp1_str[0] - 'a';
			dest_y = temp1_str[1] - '0';
			k = k + 3;
		}
		else{
			dest_x = temp1_str[0] - 'a';
			dest_y = temp1_str[1] - '0';
			dest_y = (dest_y * 10) + temp1_str[2] - '0';
			k = k + 4;

		}
		printf("%c", temp1_str[7]);
		for (temp_k = k; temp1_str[temp_k] != '\0';temp_k++)
		excel_array[dest_x][dest_y].expression[temp_index++]=temp1_str[temp_k];
		excel_array[dest_x][dest_y].expression[temp_index] = '\0';

		printf("\n %s", excel_array[dest_x][dest_y].expression);
	}
	fclose(fp);
}

void main(){
	char str[100];
	int i=0, j, dest_x, dest_y, sum;
	struct node** excel_array = (struct node **)malloc(26*sizeof(struct node*));
	for (int i = 0; i < 26; i++){
		excel_array[i] = (struct node *)malloc(26 * sizeof(struct node));
	}
	for (int i = 0; i < 12; i++){
		printf("\n");
		for (int j = 0; j < 12; j++){
			excel_array[i][j].expression = (char *)calloc(15,sizeof(char));//if ptr==null str==""
			printf("%d ", evaluate(excel_array, excel_array[i][j].expression));
		}
	}
	int option;
	load_from_file(excel_array);
	for (int i = 0; i < 12; i++){
		printf("\n");
		for (int j = 0; j < 12; j++){

			printf("%s ",  excel_array[i][j].expression);
		}
	}
	while (1){
		scanf("%d", &option);
		if (option == 0)
			break;
		i = 0;
		printf("\n>>");
		scanf("%s", &str);
		dest_x = str[i++] - 'a';
		sum = 0;
		while (str[i] != '='){
			sum = sum * 10 + str[i] - '0';
			i++;
		}
		dest_y = sum;
		j = 0; i++;
		while (str[i] != '\0'){
			excel_array[dest_x][dest_y].expression[j++] = str[i];
			printf("%c", excel_array[dest_x][dest_y].expression[j - 1]);
			i++;

		}
		excel_array[dest_x][dest_y].expression[j] = '\0';
		for (int k = 0; k < 12; k++){
			printf("\n");
			for (int j = 0; j < 12; j++)
				printf("%3d ", evaluate(excel_array, excel_array[k][j].expression));
		}



	}
	save_to_file(excel_array);
	

}
