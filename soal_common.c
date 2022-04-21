#include <stdio.h> // mendefinisikan fungsi input dan output inti
#include <stdlib.h> // mendefinisikan fungsi konversi numerik, pseudo-random network generator, dan alokasi memori
#include <string.h> // mendefinisikan fungsi handling string
#include <ctype.h> //ctype.h digunakan untuk testing dan mapping character (penggunaan pada function isspace)

int datainput_1[99999],datainput_2[99999],datainput_3[99999]; // array integer dengan elemen sebanyak 99999 baris
int number_data;
char *txtResult = NULL; //menyimpan address yang di pointer
char datain1[200],dataraw[999999][200]; //data input dengan elemen sebanyak 200 dan data raw dengan elemen 999999x200

/*struct dari dataInput*/
typedef struct{
 char **Input1; //pointer to pointer untuk Input1
 char **Input2; //pointer to pointer untuk Input2
 char **Input3; //pointer to pointer untuk Input3
 int ndata;
} dataInput;


/*
 * Fungsi replace string ke bentuk string lain
 * diketahui terdapat 3 variable yaitu s, oldW dan newW
 * berisikan result dari address sebelumnya 
 * - parameter pertama address dari variable result (diambil dari data)
 * - parameter kedua length dari char variable newW (input comma)
 * - parameter length dari char var oldW (input white-space)
 * 
 */ 
char* replaceWordInString(const char* s, const char* oldW, const char* newW){ 
    char* result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW);
	//menghitung oldW yang ada dalam string 
    for (i = 0; s[i] != '\0'; i++) { 
        if (strstr(&s[i], oldW) == &s[i]) { 
            cnt++; 
            i += oldWlen - 1; //meneruskan ke indeks i setelah oldW
        } 
    } 
	//Membuat data string baru
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1); 
  
    i = 0; 
    while (*s) {
		//compare substring tadi dengan hasilnya 
        if (strstr(s, oldW) == s) { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
  
    result[i] = '\0'; 
    return result; 
}

/*
 * 
 */
char *trim(char *s) {
	int count = -1;
	for(int i=0;i<strlen(s)+1;i++){
		if(isspace(s[i])==0){
			count = i;
			break;
		}
	}
	
	char *result = calloc((strlen(s)+1),sizeof(char));
	int count1 = -1;
	for(int i=count;i<strlen(s)+1;i++){
		count1++;
		result[count1] = s[i];
	}
	
	return result;
}

/*
 * Counting length character yang terdapat pada variable s
 * Jika hasil dari count terdapat white-space char maka kurangi value range
 * kemudian masukkan hasil ke variable di function "trim(result)"
 * 
 *
 */
char *shift_trim(char *s) {
	int count;
	for(int i=1;i<strlen(s)+1;i++){
		count = strlen(s)-i;
		if(isspace(s[count])==0){
			count = strlen(s)-i;
			break;
		}
	}
	char *result = calloc((strlen(s)+1),sizeof(char));
	int count1 = -1;
	for(int i=0;i<count+1;i++){
		count1++;
		result[count1] = s[i];
	}
	
	result = trim(result);
	return result;
}

char *IntToStr(int x){
	char *str=(char *)malloc(1 * sizeof (char));
	sprintf(str, "%d", x);
	return str;
}


/*
 * Fungsi untuk melakukan baca file dengan parameter address namefile yang diambil dari variable.
 * 
 * Isi dari fungsi "read file" menjelaskan variable fileinput melakukan read 
 * dari FILE yang diberikan parameter kemudian pada looping while,
 * tidak melakukan searching FILE(eof) ketika file input sudah sesuai dan sudah dapat diakses
 * dan jika file dapat di akses maka lakukan perintah yang ada di while
 */
void read_file(char *namafile){
	FILE *fileinput = fopen(namafile, "r");
    	
	int i = 0;
	int j = 0;
	while(!feof(fileinput)){
		i++;
		/*lakukan read nilai string dari datain1, sebesar 200 character, bersumber di file input*/
		fgets(datain1,200,fileinput); 		
		strcpy(dataraw[i], shift_trim(datain1)); //jadikan isi dataraw[i] yang dicopy dari var shift trim
		/*jika length dataraw[i] lebih besar sama dengan nol maka simpan dan copy ke dataraw*/
		if(strlen(dataraw[i])>=0){j++;strcpy(dataraw[j], shift_trim(datain1));} 
	}
	
	fclose(fileinput); //close file
	number_data = j; //ambil number data dari j

	if(strlen(dataraw[number_data]) == strlen(dataraw[number_data-1])){number_data=j-1;}
	else{number_data = j;}
}

/* 
 *Fungsi pengambilan data dari raw data
 *dibuat 3 variable data raw sebagai data input
 *
 *
 */ 
void get_data_from_rawdata(){
	char datain1[100],datain2[100],datain3[100];
	for(int i=1;i<number_data+1;i++){
		txtResult = replaceWordInString(dataraw[i],","," ");
		sscanf(txtResult,"%s  %s  %s ",datain1,datain2, datain3);
		datainput_1[i] = atoi(datain1);
		datainput_2[i] = atoi(datain2);
		datainput_3[i] = atoi(datain3);
	}
}

void save_data_file(char *namafile, dataInput datatulis){
	FILE *fileoutput = fopen(namafile, "w"); 
    for (int i = 1;i < (datatulis.ndata+1);i++){
		fprintf(fileoutput, "%s %s %s \n",  datatulis.Input1[i], datatulis.Input2[i],datatulis.Input3[i]);
	}
    fclose(fileoutput);
}

int c_round(double x){
	return x < 0 ? x - 0.5 : x + 0.5;
}

double c_modulus(double a,double b){
	double tempres;
	tempres = c_round(b*((double)(a/b)-(int)(a/b)));
	return tempres;
}

int isGanjil(int num)
{
	if (num == 0 || num == 1)
		return 1;
	else
		return (c_modulus(num,2) == 0 ? 0 : 1) ;
}
