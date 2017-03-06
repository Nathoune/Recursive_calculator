/*


To Add :
- Error handler
- Multiple operators
- Precedence handler
- Automatic bracket handler
- Other binary operators
- Unary / ternary operators



Last modifications :
24/02/17 : 	Rédaction des fonctions isol_brackets, calcul et char_to_float (décomposition du programme)
			Ajout de gestion des virgules/points
			Arrondi du résultat à la 3ème décimale + troncature de l'affichage à la 3ème décimale
20/02/17 : 	Ajout des opérateurs * et /
19/02/17 : 	Création du programme, gestion des opérateurs + et -


by Nathoune

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float calcul(float res1, float res2, char* string, int ind);
float char_to_float(char* string, int ind, int* nbc1);
void isol_brackets(char* string, char* stringRes, int ind, int* nbc1);
float calc_rec(char* string);

 int main(void)
 {
 	float res;
 	char string[1000];

 	scanf("%s", string);

	/*Recursion*/
 	res=calc_rec(string);

 	printf("\n%.3f\n",res);

 	return 0;
 }




/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
 /* General recursion to compute
	Input : string
	Output : float result of calculation
*/

float calc_rec(char* string){
	float res1, res2, res;
	int nbc1, nbc2;
	char* stringInter=(char*)calloc(1,1);


/*////////////////////////////////
//////1st term computing//////////
////////////////////////////////*/

	/*1st term isolation (brackets)*/
	if(string[0]=='('){
		isol_brackets(string, stringInter, 0, &nbc1);

		res1=calc_rec(stringInter);
		free(stringInter);
	}
	/*If no brackets, char to float.*/
	else{
		res1=char_to_float(string, 0, &nbc1);
	}



/*////////////////////////////////
/////2nd term computing///////////
////////////////////////////////*/


	/*2nd term isolation (brackets)*/
	if(string[nbc1+2]=='('){

		isol_brackets(string, stringInter, nbc1+2, &nbc2);

		/*Recursion*/
		res2=calc_rec(stringInter);
		free(stringInter);
	}
	/*If no brackets, char to float.*/
	else{
		res2=char_to_float(string, nbc1+2, &nbc2);
	}



/*////////////////////////////////
////////////Calcul////////////////
////////////////////////////////*/
	res=calcul(res1, res2, string, nbc1+1);

	return res;
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*	Calcul
 *	Input :  1st term, 2nd term, string, opérateur emplacement.
 *	Output : result
 */
float calcul(float res1, float res2, char* string, int indOp){
	float res;


		if(string[indOp]=='+'){
			res=res1+res2;
		}
		else if(string[indOp]=='-'){
			res=res1-res2;
		}
		else if(string[indOp]=='/'){
			res=res1/res2;
		}
		else if(string[indOp]=='*'){
			res=res1*res2;
		}

    /* Round to 3rd decimal */
    res=roundf(res*1000)/1000;

	return res;
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*	Conversion form char to float.
 *	Input : string, emplacement to analysed term, ptr to nbs of char of the term
 *	Output : float
 */
/* May be modification on comma handler */
float char_to_float(char* string, int ind, int* nbc){

int i, j, comma=0, iComma;
float res=0;

	for(i=ind;i<strlen(string)+1;i++){
		if((string[i]=='+')||(string[i]=='-')||(string[i]=='*')||(string[i]=='/')||(string[i]==0)){
			*nbc=i-1-ind;
			break;
		}
		if((string[i]==',')||(string[i]=='.')){
			comma=1;
			iComma=i;
		}
	}

	if(!comma){
		for(i=ind;i<=ind+*nbc;i++){
			res+=(string[i]-'0')*(float)pow(10,*nbc-i+ind);
		}
	}
	else{ /* To check */
		for(i=ind;i<=ind+*nbc;i++){
			if(i<iComma){
                j=iComma-i-1;
				res+=(string[i]-'0')*(float)pow(10,j);
			}
			else if(i>iComma){
			    j=iComma-i;
				res+=(string[i]-'0')*(float)pow(10,j);
			}
		}
	}

	return res;
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*	Isolation of bracketed term
 *	Input : original string, string result, 1st bracket emplacement, nbs of char of the term
 *	Output : string bracketed term
 */
void isol_brackets(char* string, char* stringRes, int ind, int* nbc){

		int i, j;
		int bracketCount=0;


		/*seek of the corresponding ')', output nbc nbs of char including "()"*/
		for(i=ind;i<strlen(string);i++){
			if(string[i]=='('){
				bracketCount++;
			}
			else if(string[i]==')'){
				bracketCount--;
			}

			/*loop break*/
			if((i>0)&&(bracketCount==0)){
				*nbc=i-ind;
				break;
			}
		}


		/*export of bracketed string into stringRes (dynamical)*/
		stringRes=(char*)realloc((void*)stringRes,*nbc);
		for(i=ind+1;i<ind+*nbc;i++){
			stringRes[i-ind-1]=string[i];
			j=i;
		}
		/*end of string*/
		stringRes[j+1]=0;


}

