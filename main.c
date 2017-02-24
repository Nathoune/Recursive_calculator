/*


To Add :
- gestion des erreurs
- multiples operateurs suivits sans parenth�ses et/ou ajout de parenth�ses selon les priorit�s
- gestion des priorit�s
- autres operateurs binaires
- operateurs unaires / ternaires



Last modifications :
24/02/17 : 	R�daction des fonctions isol_parenthese, calcul et char_to_float (d�composition du programme)
			Ajout de gestion des virgules/points
			Arrondi du r�sultat � la 3�me d�cimale + troncature de l'affichage � la 3�me d�cimale
20/02/17 : 	Ajout des op�rateurs * et /
19/02/17 : 	Cr�ation du programme, gestion des op�rateurs + et -


by Nathoune

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float calcul(float res1, float res2, char* string, int ind);
float char_to_float(char* string, int ind, int* nbc1);
void isol_parenthese(char* string, char* stringRes, int ind, int* nbc1);
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
 /* Fonction r�cursive g�n�rale de calcul
	Input : string
	Output : float r�sultat du calcul
*/

float calc_rec(char* string){
	float res1, res2, res;
	int nbc1, nbc2;
	char* stringInter=calloc(1,1);


/*////////////////////////////////
//////traitement terme1///////////
////////////////////////////////*/

	/*isolation du terme parenth�s�*/
	if(string[0]=='('){
		isol_parenthese(string, stringInter, 0, &nbc1);

		res1=calc_rec(stringInter);
		free(stringInter);
	}
	/*Si pas de terme parenth�s�, conversion de la valeur jusqu'� l'operateur en float.*/
	else{
		res1=char_to_float(string, 0, &nbc1);
	}



/*////////////////////////////////
//////traitement terme2///////////
////////////////////////////////*/


	/*isolation du terme parenth�s�*/
	if(string[nbc1+2]=='('){

		isol_parenthese(string, stringInter, nbc1+2, &nbc2);

		/*Recursion*/
		res2=calc_rec(stringInter);
		free(stringInter);
	}
	/*Si pas de terme parenth�s�, conversion de la valeur jusqu'� l'operateur ou fin de ligne en float.*/
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
 *	Input :  1er membre, 2eme membre, string, emplacement de l'op�rateur.
 *	Output : resultat
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
/*	Conversion de la chaine de characteres en float.
 *	Input : string, indice de d�part du terme analys�, pointeur vers le nombre de caract�res du terme
 *	Output : float
 */
/* Attentions surement des modifs sur la gestion des virgules */
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
	else{ /* Attention � v�rifier */
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
/*	Isolation du terme parenth�s�
 *	Input : original string, string resultante, indice de la premi�re parenth�se, nombre de caract�res du terme
 *	Output : string terme parenth�s�
 */
void isol_parenthese(char* string, char* stringRes, int ind, int* nbc){

		int i, j;
		int bracketCount=0;


		/*Recherche de la ')' correspondante ressort nbc nombre de characters incluant les ()*/
		for(i=ind;i<strlen(string);i++){
			if(string[i]=='('){
				bracketCount++;
			}
			else if(string[i]==')'){
				bracketCount--;
			}

			/*sortie de la boucle*/
			if((i>0)&&(bracketCount==0)){
				*nbc=i-ind;
				break;
			}
		}


		/*export de la chaine patenth�s�e dans stringRes en dynamique*/
		stringRes=(char*)realloc((void*)stringRes,*nbc);
		for(i=ind+1;i<ind+*nbc;i++){
			stringRes[i-ind-1]=string[i];
			j=i;
		}
		/*fin de la chaine de characteres*/
		stringRes[j+1]=0;


}

