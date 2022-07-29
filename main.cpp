
/*
 * ESTE CÓDIGO IMPLEMENTA UM ANALIZADOR LÉXICO PARA O EXEMPLO DE FRAGMENTO DE LINGUAGEM APRESENTADO EM SALA DE AULA (VEJA OS SLIDES DA AULA 4: ANÁLISE LÉXICA: PARTE 2)
 * E PODERÁ SER UTILIZADO COMO PONTO DE PARTIDA PARA IMPLEMENTAÇÃO DO ANALISADOR LÉXICO PARA LINGUAGEM ADOTADA NO TRABALHO PROPOSTO.
 * */

#include <stdio.h>
#include <string>
#include <cctype>
#include <cstdio>


//NOME TOKENS
#define IF  256;
#define TRUE  257;
#define THEN  258;
#define ELSE  259;
#define AND  260;
#define BREAK  261;
#define DO  262;
#define ELSEIF  263;
#define END  264;
#define FALSE  265;
#define FOR  266;
#define FUNCTION  267;
#define IN  268;
#define LOCAL  269;
#define NIL  270;
#define NOT  271;
#define OR  272;
#define REPEAT  273;
#define RETURN  274;
#define UNTIL  275;
#define WHILE  276;
#define RELOP  277;
#define ID  278;
#define NUM  279;
#define LITERAL 280;
#define COMENT_CURTO 281;
#define COMENT_LONGO 282;
#define OP 283;
#define DEL 284;


//ATRIBUTOS
#define LE 285;
#define GE 286;
#define LT 287;
#define GT 288;
#define EE 289;
#define EQ 290;
#define NE 291;
#define ADD 292;
#define SUB 293;
#define MULT 294;
#define DIV 295;
#define EXP 296;
#define PARENTESES 297;
#define CHAVES 298;
#define COLCHETES 299;
#define PONTO_VIRGULA 300;
#define DOIS_PONTOS 301;
#define PONTO 302;
#define VIRGULA 303;
#define CONCAT 304;

//using namespace std;
std::string lexema;

struct Token{
 int nome_token;
 int atributo;
};

int n = 0;
int estado = 1;
int cont_sim_lido = 0;
char *code;
std::string tabela_simbolos[99999];
int pos_tabela_simbolos = 0;

char *readFile(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	char *code;
	//int n = 0;
	int c;

	if(file == NULL) return NULL;

	fseek(file, 0, SEEK_END);
	long f_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	code = new char (f_size);

	while ((c = fgetc(file))!= EOF)
	{
		code[n] = (char) c;
		n++;
	}
	code[n] = '\0';
	return code;
}




int falhar()
{
	if (estado >= 1 && estado < 6) return 6;
	if(estado >= 6 && estado < 9) return 9;
	if(estado >= 9 && estado < 21) return 21;
	if(estado >= 21 && estado < 24) return 24;
	if(estado >= 24 && estado < 28) return 28;
	if(estado >= 28 && estado < 35) return 35;
	if(estado >= 35 && estado < 41) return 41;
	if(estado >= 41 && estado < 51) return 51;
	if(estado == 51) {
		printf("Erro encontrado no código\n");
		cont_sim_lido++;
	} else {
		printf("Erro do compilador\n");
	}
	return 1;

	
}

Token proximo_token()
{
	Token token;
	char c;
	
	while(code[cont_sim_lido] != '\0' || estado != 1)
	{
		/* printf("Index: %d Estado: %d Char: %c\n",cont_sim_lido,estado, code[cont_sim_lido]); */
		switch(estado)
		{
			case 1:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 1;
					cont_sim_lido++;
				}
				else if(isdigit(c)) {
					lexema += c;
					estado = 2;
				}
				else
					{
					 estado = falhar();
					}
				break;

			case 2:
				c = code[++cont_sim_lido];

				if(isdigit(c)){
					estado = 2;
					lexema += c;
				} 
				else if(c == '^') {
					lexema += c;
					estado = 3;
				}		
				else {
					estado = 5;
				}		
				break;

			case 3:
				c = code[++cont_sim_lido];

				if(isdigit(c)) {
					lexema += c;
					estado = 4;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 4:
				c = code[++cont_sim_lido];

				if(isdigit(c)) {
					lexema += c;
					estado = 4;
				}
				else {
					estado = 5;
				}
				break;
			
			case 5:
				tabela_simbolos[pos_tabela_simbolos] = lexema;				
				printf("<num, %s >\n", lexema.c_str());
				token.nome_token = NUM;
				token.atributo = pos_tabela_simbolos;
				pos_tabela_simbolos++;
				estado = 1;
				lexema = "";
				return(token);
				break;


			case 6:				
				c = code[cont_sim_lido];				

				if((c == ' ')||(c == '\n'))
				{
					estado = 1;
					cont_sim_lido++;
				}
				else if(isalpha(c) || c == '_') {
					lexema += c;
					estado = 7;
				} else {					
					estado = falhar();
				}
				break;
			
			case 7:
				c = code[++cont_sim_lido];

				if(c == '_' || isalpha(c) || isdigit(c)) {
					lexema += c;
					estado = 7;
				} else {
					estado = 8;
				}
				break;

			case 8:			
				tabela_simbolos[pos_tabela_simbolos] = lexema;					
				printf("<id, %s >\n", lexema.c_str());
				token.nome_token = ID;
				token.atributo = pos_tabela_simbolos;
				pos_tabela_simbolos++;
				estado = 1;
				lexema = "";
				return(token);
				break;

			case 9:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 1;
					cont_sim_lido++;
				}
				
				if(c == '<'){
					//lexema += c;
					estado = 10;
				} 
				else if(c == '=') {
					estado = 13;
				}
				else if(c == '>') {
					estado = 16;
				} 
				else if(c == '~') {
					estado = 19;
				}
				else {
					estado = falhar();
				}				
				break;

			case 10:
				c = code[++cont_sim_lido];

				if(c == '=') {
					estado = 11;
				}
				else {
					estado = 12;
				}
				break;
			
			case 11:
				cont_sim_lido++;
				/* tabela_simbolos[pos_tabela_simbolos] = lexema; */					
				//printf("<relop, " + lexema + ">\n");
				printf("<relop, LE>\n");
				token.nome_token = RELOP;
				token.atributo = LE;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;

			case 12:
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<relop, LT>\n");
				token.nome_token = RELOP;
				token.atributo = LT;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;

			case 13:
				c = code[++cont_sim_lido];

				if(c == '=') {
					estado = 14;
				} else {
					estado = 15;
				}
				break;
			
			case 14:
				cont_sim_lido++;
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<relop, EE>\n");
				token.nome_token = RELOP;
				token.atributo = EE;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;
			
			case 15:
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<relop, EQ>\n");
				token.nome_token = RELOP;
				token.atributo = EQ;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;

			case 16:
				c = code[++cont_sim_lido];

				if(c == '=') {
					estado = 18;
				} else {
					estado = 17;
				}
				break;

			case 17:
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<relop, GT>\n");
				token.nome_token = RELOP;
				token.atributo = GT;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;

			case 18:
				cont_sim_lido++;
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<relop, GE>\n");
				token.nome_token = RELOP;
				token.atributo = GE;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;
			
			case 19:
				c = code[++cont_sim_lido];

				if(c == '=') {
					estado = 20;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 20:
				cont_sim_lido++;
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<relop, NE>\n");
				token.nome_token = RELOP;
				token.atributo = NE;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;

			case 21:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 1;
					cont_sim_lido++;
				}
				else if (c == '"') {
					lexema += c;
					estado = 22;
				}else{
					estado = falhar();
				}
				break;

			case 22:
				c = code[++cont_sim_lido];
				
				if(isdigit(c) || isalpha(c) || 
				c == '\a' || c == '\b' || c == '\f' || 
				c == '\n' || c == '\r' || c == '\t' || 
				c == '\v' || c == '\\' || c == '\"' ){
					lexema += c;
					estado = 22;
				}

				else if (c == '"'){
					lexema += c;
					estado = 23;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 23:
				tabela_simbolos[pos_tabela_simbolos] = lexema;					
				printf("<literal, %s >\n", lexema.c_str());
				token.nome_token = LITERAL;
				token.atributo = pos_tabela_simbolos;
				pos_tabela_simbolos++; 
				estado = 1;				
				lexema = "";
				return(token);
				break;
			
			case 24:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 1;
					cont_sim_lido++;
				}
				else if(c == '-') {
					estado = 25;
				} else {
					estado = falhar();
				}
				break;
			

			case 25:
				c = code[++cont_sim_lido];
				if(c == '-'){
					estado = 26;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 26:
				c = code[++cont_sim_lido];
				if(c == '[') {
					estado = 31;
				}
				else if(isdigit(c) || isalpha(c) || c == ' ') {
					estado = 26;
				} else {
					estado = 27;
				}
				break;
			
			case 27:
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<coment_curto, -1>\n");
				token.nome_token = COMENT_CURTO;
				token.atributo = -1;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;

			case 28:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 1;
					cont_sim_lido++;
				}
				if(c == '-') {
					estado = 29;
				} else {
					estado = falhar();
				}
				break;
			
			case 29:
				c = code[++cont_sim_lido];
				if (c == '-'){
					estado = 30;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 30:
				c = code[++cont_sim_lido];
				if (c == '['){
					estado = 31;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 31:
				c = code[++cont_sim_lido];
				if (c == '['){
					estado = 32;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 32:
				c = code[++cont_sim_lido];
				if(isdigit(c) || isalpha(c) || c == '\n' || c == ' ') {
					estado = 32;
				} else if(c == ']') {
					estado = 33;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 33:
				c = code[++cont_sim_lido];
				if (c == ']'){
					estado = 34;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			case 34:
				cont_sim_lido++;
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<coment_longo, -1>\n");
				token.nome_token = COMENT_LONGO;
				token.atributo = -1;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;
			
			case 35:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 1;
					cont_sim_lido++;
				}
				if(c == '+') {
					estado = 36;
				} else if(c == '-') {
					estado = 37;
				} else if(c == '*') {
					estado = 38;
				} else if(c == '/') {
					estado = 39;
				} else if(c == '^') {
					estado = 40;
				}
				else {
					estado = falhar();
				}
				break;
			
			case 36:
				cont_sim_lido++;
				printf("<op, ADD>\n");
				token.nome_token = OP;
				token.atributo = ADD;
				estado = 1;
				return(token);
				break;
			
			case 37:
				cont_sim_lido++;
				printf("<op, SUB>\n");
				token.nome_token = OP;
				token.atributo = SUB;
				estado = 1;
				return(token);
				break;

			case 38:
				cont_sim_lido++;
				printf("<op, MULT>\n");
				token.nome_token = OP;
				token.atributo = MULT;
				estado = 1;
				return(token);
				break;

			case 39:
				cont_sim_lido++;
				printf("<op, DIV>\n");
				token.nome_token = OP;
				token.atributo = DIV;
				estado = 1;
				return(token);
				break;

			case 40:
				cont_sim_lido++;
				printf("<op, EXP>\n");
				token.nome_token = OP;
				token.atributo = EXP;
				estado = 1;
				return(token);
				break;


			case 41:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 1;
					cont_sim_lido++;
				}
				if(c == '[' || c == ']') {
					estado = 42;
				} else if(c == ';') {
					estado = 43;
				} else if(c == '(' || c == ')') {
					estado = 44;
				} else if(c == ',') {
					estado = 45;
				} else if(c == '{' || c == '}') {
					estado = 46;
				} else if(c == ':') {
					estado = 47;
				} else if(c == '.') {
					estado = 48;
				}
				else {
					estado = falhar();
				}
				break;

			case 42:
				cont_sim_lido++;
				printf("<del, COLCHETES>\n");
				token.nome_token = DEL;
				token.atributo = COLCHETES;
				estado = 1;
				return(token);
				break;

			case 43:
				cont_sim_lido++;
				printf("<del, PONTO_VIRGULA>\n");
				token.nome_token = DEL;
				token.atributo = PONTO_VIRGULA;
				estado = 1;
				return(token);
				break;

			case 44:
				cont_sim_lido++;
				printf("<del, PARENTESES>\n");
				token.nome_token = DEL;
				token.atributo = PARENTESES;
				estado = 1;
				return(token);
				break;

			case 45:
				cont_sim_lido++;
				printf("<del, VIRGULA>\n");
				token.nome_token = DEL;
				token.atributo = VIRGULA;
				estado = 1;
				return(token);
				break;

			case 46:
				cont_sim_lido++;
				printf("<del, CHAVES>\n");
				token.nome_token = DEL;
				token.atributo = CHAVES;
				estado = 1;
				return(token);
				break;

			case 47:
				cont_sim_lido++;
				printf("<del, DOIS_PONTOS>\n");
				token.nome_token = DEL;
				token.atributo = DOIS_PONTOS;
				estado = 1;
				return(token);
				break;

			case 48:
				c = code[++cont_sim_lido];
				if(c == '.') {
					estado = 50;
				} else {
					estado = 49;
				}
				break;

			case 49:
				
				printf("<del, PONTO>\n");
				token.nome_token = DEL;
				token.atributo = PONTO;
				estado = 1;
				return(token);
				break;

			case 50:
				printf("<del, CONCAT>\n");
				token.nome_token = DEL;
				token.atributo = CONCAT;
				estado = 1;
				return(token);
				break;

			case 51:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 1;
					cont_sim_lido++;
				}
				if(c == 'a') {
					estado = 52;
				} else if(c == 'b') {
					estado = 55;
				} else if(c == 'd') {
					estado = 60;
				} else if(c == 'e') {
					estado = 62;
				} else if(c == 'f') {
					estado = 71;
				} else if(c == 'i') {
					estado = 85;
				} else if(c == 'l') {
					estado = 88;
				} else if(c == 'n') {
					estado = 93;
				} else if(c == 'o') {
					estado = 98;
				} else if(c == 'r') {
					estado = 100;
				} else if(c == 't') {
					estado = 110;
				} else if(c == 'u') {
					estado = 117;
				} else if(c == 'w') {
					estado = 122;
				}
				else {
					estado = falhar();
				}
				break;

			case 52:
				c = code[++cont_sim_lido];
				if(c == 'n') {
					estado = 53;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 53:
				c = code[++cont_sim_lido];
				if(c == 'd') {
					estado = 54;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 54:
				printf("<and, -1>\n");
				token.nome_token = AND;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 55:
				c = code[++cont_sim_lido];
				if(c == 'r') {
					estado = 56;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			case 56:
				c = code[++cont_sim_lido];
				if(c == 'e') {
					estado = 57;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 57:
				c = code[++cont_sim_lido];
				if(c == 'a') {
					estado = 58;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 58:
				c = code[++cont_sim_lido];
				if(c == 'k') {
					estado = 59;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 59:
				printf("<break, -1>\n");
				token.nome_token = BREAK;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 60:
				c = code[++cont_sim_lido];
				if(c == 'o') {
					estado = 61;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 61:
				printf("<do, -1>\n");
				token.nome_token = DO;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;
			
			case 62:
				c = code[++cont_sim_lido];
				if(c == 'l') {
					estado = 63;
				} else if(c == 'n') {
					estado = 69;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 63:
				c = code[++cont_sim_lido];
				if(c == 's') {
					estado = 64;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 64:
				c = code[++cont_sim_lido];
				if(c == 'e') {
					estado = 65;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 65:
				c = code[++cont_sim_lido];
				if(c == 'i') {
					estado = 67;
				} else {
					estado = 66;
				}
				break;
			
			case 66:
				printf("<else, -1>\n");
				token.nome_token = ELSE;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;
			
			case 67:
				c = code[++cont_sim_lido];
				if(c == 'f') {
					estado = 68;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 68:
				printf("<elseif, -1>\n");
				token.nome_token = ELSEIF;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;
			
			case 69:
				c = code[++cont_sim_lido];
				if(c == 'd') {
					estado = 70;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 70:
				printf("<end, -1>\n");
				token.nome_token = END;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 71:
				c = code[++cont_sim_lido];
				if(c == 'a') {
					estado = 72;
				} else if(c == 'o') {
					estado = 76;
				} else if(c == 'u') {
					estado = 78;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 72:
				c = code[++cont_sim_lido];
				if(c == 'l') {
					estado = 73;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 73:
				c = code[++cont_sim_lido];
				if(c == 's') {
					estado = 74;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 74:
				c = code[++cont_sim_lido];
				if(c == 'e') {
					estado = 75;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 75:
				printf("<false, -1>\n");
				token.nome_token = FALSE;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 76:
				c = code[++cont_sim_lido];
				if(c == 'r') {
					estado = 77;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 77:
				printf("<for, -1>\n");
				token.nome_token = FOR;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 78:
				c = code[++cont_sim_lido];
				if(c == 'n') {
					estado = 79;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 79:
				c = code[++cont_sim_lido];
				if(c == 'c') {
					estado = 80;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 80:
				c = code[++cont_sim_lido];
				if(c == 't') {
					estado = 81;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 81:
				c = code[++cont_sim_lido];
				if(c == 'i') {
					estado = 82;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 82:
				c = code[++cont_sim_lido];
				if(c == 'o') {
					estado = 83;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 83:
				c = code[++cont_sim_lido];
				if(c == 'n') {
					estado = 84;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 84:
				printf("<function, -1>\n");
				token.nome_token = FUNCTION;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 85:
				c = code[++cont_sim_lido];
				if(c == 'f') {
					estado = 86;
				} else if(c == 'n') {
					estado = 87;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 86:
				printf("<if, -1>\n");
				token.nome_token = IF;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 87:
				printf("<in, -1>\n");
				token.nome_token = IN;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 88:
				c = code[++cont_sim_lido];
				if(c == 'o') {
					estado = 89;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 89:
				c = code[++cont_sim_lido];
				if(c == 'c') {
					estado = 90;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 90:
				c = code[++cont_sim_lido];
				if(c == 'a') {
					estado = 91;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 91:
				c = code[++cont_sim_lido];
				if(c == 'l') {
					estado = 92;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 92:
				printf("<local, -1>\n");
				token.nome_token = LOCAL;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 93:
				c = code[++cont_sim_lido];
				if(c == 'i') {
					estado = 94;
				} else if(c == 'o') {
					estado = 96;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 94:
				c = code[++cont_sim_lido];
				if(c == 'l') {
					estado = 95;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 95:
				printf("<nil, -1>\n");
				token.nome_token = NIL;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;
			
			case 96:
				c = code[++cont_sim_lido];
				if(c == 't') {
					estado = 97;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 97:
				printf("<not, -1>\n");
				token.nome_token = NOT;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 98:
				c = code[++cont_sim_lido];
				if(c == 'r') {
					estado = 99;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 99:
				printf("<or, -1>\n");
				token.nome_token = OR;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 100:
				c = code[++cont_sim_lido];
				if(c == 'e') {
					estado = 101;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 101:
				c = code[++cont_sim_lido];
				if(c == 'p') {
					estado = 102;
				} else if(c == 't') {
					estado = 106;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 102:
				c = code[++cont_sim_lido];
				if(c == 'e') {
					estado = 103;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 103:
				c = code[++cont_sim_lido];
				if(c == 'a') {
					estado = 104;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 104:
				c = code[++cont_sim_lido];
				if(c == 't') {
					estado = 105;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 105:
				printf("<repeat, -1>\n");
				token.nome_token = REPEAT;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 106:
				c = code[++cont_sim_lido];
				if(c == 'u') {
					estado = 107;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 107:
				c = code[++cont_sim_lido];
				if(c == 'r') {
					estado = 108;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 108:
				c = code[++cont_sim_lido];
				if(c == 'n') {
					estado = 109;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 109:
				printf("<return, -1>\n");
				token.nome_token = RETURN;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 110:
				c = code[++cont_sim_lido];
				if(c == 'h') {
					estado = 111;
				} else if(c == 'r') {
					estado = 114;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 111:
				c = code[++cont_sim_lido];
				if(c == 'e') {
					estado = 112;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 112:
				c = code[++cont_sim_lido];
				if(c == 'n') {
					estado = 113;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 114:
				c = code[++cont_sim_lido];
				if(c == 'u') {
					estado = 115;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 115:
				c = code[++cont_sim_lido];
				if(c == 'e') {
					estado = 116;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 116:
				printf("<true, -1>\n");
				token.nome_token = TRUE;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			case 117:
				c = code[++cont_sim_lido];
				if(c == 'n') {
					estado = 118;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
				
			case 118:
				c = code[++cont_sim_lido];
				if(c == 't') {
					estado = 119;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 119:
				c = code[++cont_sim_lido];
				if(c == 'i') {
					estado = 120;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 120:
				c = code[++cont_sim_lido];
				if(c == 'l') {
					estado = 121;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 121:
				printf("<until, -1>\n");
				token.nome_token = UNTIL;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;
			
			case 122:
				c = code[++cont_sim_lido];
				if(c == 'h') {
					estado = 123;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;
			
			case 123:
				c = code[++cont_sim_lido];
				if(c == 'i') {
					estado = 124;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 124:
				c = code[++cont_sim_lido];
				if(c == 'l') {
					estado = 125;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 125:
				c = code[++cont_sim_lido];
				if(c == 'e') {
					estado = 126;
				} else {
					cont_sim_lido--;
					estado = falhar();
				}
				break;

			case 126:
				printf("<while, -1>\n");
				token.nome_token = WHILE;
				token.atributo = -1;
				estado = 1;
				return(token);
				break;

			

		}

	}
	token.nome_token = EOF;
	token.atributo = -1;
	return(token);
}




int main ()
{
	printf("Início\n");
	Token token;
	code = readFile((char *)"programa.txt");
	// FILE *f = fopen("programa.txt", "r");
	// char c;
	// while ((c = fgetc(f)) != EOF){
	// 	token = proximo_token();
	// }
	while (token.nome_token != EOF){
		token = proximo_token();
	}

	
	//array de char com cada caracter do arquivo
	// printf("----------------\n");
	// for(int i = 0; i < n; i++){
	// 	printf("%c \n", code[i]); 
	// }
    

}
