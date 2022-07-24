
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
#define THEN  257;
#define ELSE  258;
#define AND  259;
#define BREAK  260;
#define DO  261;
#define ELSEIF  262;
#define END  263;
#define FALSE  264;
#define FOR  265;
#define FUNCTION  266;
#define IN  267;
#define LOCAL  268;
#define NIL  269;
#define NOT  270;
#define OR  271;
#define REPEAT  272;
#define RETURN  273;
// #define THEN  274;
#define UNTIL  274;
#define WHILE  275;
#define RELOP  276;
#define ID  277;
#define NUM  278;
#define LITERAL 279;
#define COMENT_CURTO 280;
#define COMENT_LONGO 281;


//ATRIBUTOS
#define LE 282;
#define GE 283;
#define LT 284;
#define GT 285;
#define EE 286;
#define EQ 287;
#define NE 288;
#define ADD 289;
#define SUB 290;
#define MULT 291;
#define DIV 292;
#define EXP 293;
#define PARENTESES 294;
#define CHAVES 295;
#define COLCHETES 296;
#define PONTO_VIRGULA 297;
#define DOIS_PONTOS 298;
#define PONTO 399;
#define VIRGULA 300;
#define CONCAT 301;

//using namespace std;
std::string lexema;

struct Token{
 int nome_token;
 int atributo;
};


int estado = 1;
int partida = 0;
int cont_sim_lido = 0;
char *code;
std::string tabela_simbolos[];
int pos_tabela_simbolos = 0;

char *readFile(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	char *code;
	int n = 0;
	int c;

	if(file == NULL) return NULL;

	fseek(file, 0, SEEK_END);
	long f_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	code = new char (f_size);

	while ((c = fgetc(file))!= EOF)
	{
		code[n++] = (char) c;
	}
	code[n] = '\0';
	return code;
}




int falhar()
{
	switch(estado)
	{
	case 1: partida = 6; break;

	case 6: partida = 9; break;

	case 9: partida = 21; break;

	case 21: partida = 24; break;

	case 24: partida = 27; break;

	case 27:
		//retornar msg de erro
		printf("Erro encontrado no código\n");
		cont_sim_lido++;
		break;

	default: printf("Erro do compilador");
	}
	return(partida);
}

Token proximo_token()
{
	Token token;
	char c;
	while(code[cont_sim_lido] != EOF)
	{
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
				cont_sim_lido++;
				c = code[cont_sim_lido];

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
				cont_sim_lido++;
				c = code[cont_sim_lido];

				if(isdigit(c)) {
					lexema += c;
					estado = 4;
				}
				break;

			case 4:
				cont_sim_lido++;
				c = code[cont_sim_lido];

				if(isdigit(c)) {
					lexema += c;
					estado = 4;
				}
				else {
					estado = 5;
				}
				break;
			
			case 5:
				cont_sim_lido++;
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
				cont_sim_lido++;
				c = code[cont_sim_lido];

				if(c == '_' || isalpha(c) || isdigit(c)) {
					lexema += c;
					estado = 7;
				} else {
					estado = 8;
				}
				break;

			case 8:
				cont_sim_lido++;
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
				cont_sim_lido++;
				c = code[cont_sim_lido];

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
				printf("<relop, LE>");
				token.nome_token = RELOP;
				token.atributo = LE;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;

			case 12:
				cont_sim_lido++;
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<relop, LT>");
				token.nome_token = RELOP;
				token.atributo = LT;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;

			case 13:
				cont_sim_lido++;
				c = code[cont_sim_lido];

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
				printf("<relop, EE>");
				token.nome_token = RELOP;
				token.atributo = EE;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;
			
			case 15:
				cont_sim_lido++;
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<relop, EQ>");
				token.nome_token = RELOP;
				token.atributo = EQ;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;

			case 16:
				cont_sim_lido++;
				c = code[cont_sim_lido];

				if(c == '=') {
					estado = 18;
				} else {
					estado = 17;
				}
				break;

			case 17:
				cont_sim_lido++;
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<relop, GT>");
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
				printf("<relop, GE>");
				token.nome_token = RELOP;
				token.atributo = GE;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;
			
			case 19:
				cont_sim_lido++;
				c = code[cont_sim_lido];

				if(c == '=') {
					estado = 20;
				}
				break;

			case 20:
				cont_sim_lido++;
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<relop, NE>");
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
				cont_sim_lido++;
				c = code[cont_sim_lido];

				if(isdigit(c) || isalpha(c) || '\a' || '\b' || '\f' || '\n' || '\r' || '\t', '\v' || '\\' || '\"' ){
					lexema += c;
					estado = 22;
				}

				else if (c == '"'){
					lexema += c;
					estado = 23;
				}
				break;

			case 23:
				cont_sim_lido++;
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
				else if(c == '--') {
					estado = 25;
				} else {
					estado = falhar();
				}
				break;
			
			case 25:
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if(isdigit(c) || isalpha(c)) {
					estado = 25;
				} else {
					estado = 26;
				}
				break;
			
			case 26:
				cont_sim_lido++;
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<coment_curto, -1");
				token.nome_token = COMENT_CURTO;
				token.atributo = -1;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;

			case 27:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 1;
					cont_sim_lido++;
				}
				if(c == '--[[') {
					estado = 28;
				} else {
					estado = falhar();
					token.nome_token = -1;
					token.atributo = -1;
					return(token);
				}
				break;
			
			case 28:
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if(isdigit(c) || isalpha(c) || c == '\n') {
					estado = 28;
				} else if(c == ']]') {
					estado = 29;
				}
				break;
			
			case 29:
				cont_sim_lido++;
				// tabela_simbolos[pos_tabela_simbolos] = lexema;					
				//printf("<relop, " + lexema + ">\n");
				printf("<coment_longo, -1");
				token.nome_token = COMENT_LONGO;
				token.atributo = -1;
				/* pos_tabela_simbolos++; */
				estado = 1;
				/* lexema = ""; */
				return(token);
				break;


			/*case 8:
				cont_sim_lido++;
				printf("<relop, GT>\n");
				token.nome_token = RELOP;
				token.atributo = GT;
				//ATENÇÃO - CORREÇÃO: foi acrescentado o comando "estado = 0;"
				estado = 0;
				return(token);
				break;

			case 9:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else
				{
					/*implementar ações referentes aos estado 
					estado = falhar();
				}

				break;

				/*implementar ações para os estados 10, 11, 12

			case 12:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else
				{
					/*implementar ações referentes aos estado 
					estado = falhar();
				}
				break;

				/*implementar ações para os estados 13-19

			case 20:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else
				{
					/*implementar ações referentes aos estado 
					estado = falhar();
				}
				break;

				/*implementar ações para os estados 21-24

			case 25:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else
				{
					/*implementar ações referentes aos estado 
					estado = falhar();
					token.nome_token = -1;
					token.atributo = -1;
					return(token);
				}
				break;*/
		}

	}
	token.nome_token = EOF;
	token.atributo = -1;
	return(token);
}




int main ()
{
	Token token;
    code = readFile("programa.txt");
    token = proximo_token();
    token = proximo_token();
    //...


}
