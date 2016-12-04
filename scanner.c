#include "scanner.h"
#include "err.h"

int init_string(string *s){
	s->str = (char *)malloc(8*sizeof(char));
	if(s->str == NULL)
		return ERR_INTERNAL_ERR;
	s->length = 0;
	s->alloc  = 8;
	s->str[0] = '\0';
	return TRUE;
}

int add_char_to_String(string *s,char c){
	if(s->length+1 >= s->alloc){
		s->alloc = s->alloc + 8;
		s->str = (char *)realloc(s->str,s->alloc * sizeof(char));
		if(s->str == NULL)
			return ERR_INTERNAL_ERR;
	}
	s->str[s->length] = c;
	s->length = s->length+1;
	s->str[s->length] = '\0';
	return TRUE;
}
void clear_string(string *s){
	if(s->length != 0){
		for(unsigned int i = 0; i < (s->length); i++){
			s->str[i] = '\0';
		}
	}
}

void free_string(string *s){
	for(unsigned int i = 0; i < (s->length); i++){
		s->str[i] = '\0';
	}
	s->length = 0;
	s->alloc  = 0;
	free(s->str);
}

int compare_keywords(string *s){
	if(!strcmp(s->str,"boolean"))
		return kw_true;
	if(!strcmp(s->str,"break"))
		return kw_break;
	if(!strcmp(s->str,"class"))
		return kw_class;
	if(!strcmp(s->str,"continue"))
		return kw_continue;
	if(!strcmp(s->str,"do"))
		return kw_do;
	if(!strcmp(s->str,"double"))
		return kw_double;
	if(!strcmp(s->str,"else"))
		return kw_else;
	if(!strcmp(s->str,"false"))
		return kw_false;
	if(!strcmp(s->str,"for"))
		return kw_for;
	if(!strcmp(s->str,"if"))
		return kw_if;
	if(!strcmp(s->str,"int"))
		return kw_int;
	if(!strcmp(s->str,"return"))
		return kw_return;
	if(!strcmp(s->str,"String"))
		return kw_string;
	if(!strcmp(s->str,"static"))
		return kw_static;
	if(!strcmp(s->str,"true"))
		return kw_true;
	if(!strcmp(s->str,"void"))
		return kw_void;
	if(!strcmp(s->str,"while"))
		return kw_while;
	return FALSE;
}

int get_token(FILE *f,string *str){
	int state =  State_for_start;
	int c;
	int returnVal=1;
	int read = TRUE;
	clear_string(str);
	init_string(str);
	while(read){
		c = fgetc(f);
		switch(state){
			case State_for_start:
				if(isspace(c)){}
				else if(isalpha(c)){
					add_char_to_String(str,c);
					read = TRUE;
					state = State_for_kw;
					break;
				}
				else if(c == '_' || c == '$' || c == '.'){
					add_char_to_String(str,c);
					read = TRUE;
					state = State_for_id;
				}
				else{
					switch(c){
						case EOF:	read = FALSE; 	break;

						case '/':	read = TRUE;	state = char_slash;				break;
						case '{':	read = FALSE;	returnVal = char_LMZatvorka;	break;
						case '}': 	read = FALSE;	returnVal = char_PMZatvorka;	break;
						case '(':	read = FALSE;	returnVal = char_LZatvorka;		break;
						case ')':	read = FALSE;	returnVal = char_PZatvorka;		break;
						case '[':	read = FALSE;	returnVal = char_LHZatvorka;	break;
						case ']':	read = FALSE;	returnVal = char_PHZatvorka;	break;
						case '.': 	read = FALSE; 	returnVal = char_bodka; 		break;
        			    case ',': 	read = FALSE; 	returnVal = char_ciarka;		break;
       				    case '+': 	read = FALSE; 	returnVal = char_plus; 			break;
         			  	case '-': 	read = FALSE; 	returnVal = char_minus;			break;
						case '*': 	read = FALSE; 	returnVal = char_star;			break;
						case ':':	read = FALSE;	returnVal = char_dvoj_bodka;	break;
						case ';':	read = FALSE;	returnVal = char_bod_ciarka;	break;
						case '%':	read = FALSE;	returnVal = char_percento;		break;
						case '\'':	read = FALSE;	returnVal = char_apostrof;		break;
						case '\"':	read = FALSE;	returnVal = char_uvodzovky;		break;
						case '<':	read = TRUE;	state = char_mensi;				break;
						case '>':	read = TRUE;	state = char_vacsi;				break;
						case '=':	read = TRUE;	state = char_rovnasa;			break;
						case '!':	read = TRUE;	state = char_vykricnik;			break;
						case '|':	read = TRUE;	state = char_pipe;				break;
						case '&':	read = TRUE;	state = char_amperesand;		break;
						case '\\':	read = TRUE;	state = char_backslash;			break;
						default :	read = FALSE;	returnVal =	ERR_LEX_ERR;		break;
					}
					break;
				}
			case char_slash:
				if(c == '/'){
					returnVal = komentar1;
				}else if(c == '*'){
					returnVal = komentar2;
				}else if(returnVal != komentar2 && returnVal != komentar1){
					state = State_for_start;
					returnVal = char_slash;
					ungetc(c,f);
				}

				if(returnVal == komentar1){
					c = fgetc(f);
					if(c == '\n'){
						state = State_for_start;
					}
					if(c == EOF){
						returnVal = State_for_start;
					}
				}
				if(returnVal == komentar2 && c == '*'){
					if((c = fgetc(f)) == '/'){
						state = State_for_start;
					}
					if(c == EOF){
						read = FALSE;
						returnVal = ERR_SYNTAX_ERR;
					}
				}
				break;

			case char_mensi :
				if( c == '='){
					read = FALSE;
					returnVal = char_mensirovny;
				}else{
					read = FALSE;
					returnVal = char_mensi;
					ungetc(c,f);
				}
				break;

			case char_vacsi :
				if(c == '='){
					read = FALSE;
					returnVal = char_vacsirovny;
				}else{
					read = FALSE;
					returnVal = char_vacsi;
					ungetc(c,f);
				}
				break;

			case char_rovnasa :
				if(c == '='){
					read = FALSE;
					returnVal = char_rovny;
				}else{
					read = FALSE;
					ungetc(c,f);
					returnVal = char_rovnasa;
				}
				break;

			case char_vykricnik :
				if(c == '='){
					read = FALSE;
					returnVal = char_nerovny;
				}else{
					read = FALSE;
					returnVal = char_vykricnik;
					ungetc(c,f);
				}
				break;
			case char_pipe :
				if(c == '|'){
					returnVal = char_or;
					read = FALSE;
				}else{
					read = FALSE;
					ungetc(c,f);
					returnVal = char_pipe;
				}
				break;
			case char_amperesand :
				if( c =='&'){
					read = FALSE;
					returnVal = char_and;
				}else{
					read = FALSE;
					ungetc(c,f);
					returnVal = char_amperesand;
				}
				break;

			case char_backslash :
				if(c == '\\'){
					returnVal = char_backslash;
					read = FALSE;
				}
				else if(c == 't'){
					read = FALSE;
					returnVal = char_tab;
				}
				else if(c == 'n'){
					read = FALSE;
					returnVal = char_line;
				}
				else if(c == '\"'){
					read = FALSE;
					returnVal = print_uvodzovky;
				}
				else if(c == '\''){
					read = FALSE;
					returnVal = print_apostrof;
				}else{
					read = FALSE;
					ungetc(c,f);
					returnVal = ERR_SYNTAX_ERR;
				}
				break;
			case State_for_kw :
				if(c == EOF){
					read = FALSE;
					returnVal = ERR_LEX_ERR;
				}
				if(c != '\0' && !isspace(c) && c != EOF){
					read = TRUE;
					add_char_to_String(str,c);
				}else{
					read = FALSE;
					if(compare_keywords(str)){
						returnVal = compare_keywords(str);
					}else{
						returnVal = retazec;
					}
				}
				break;
		}
	}
	return returnVal;
}
int main(void)
{
	FILE *f = fopen("test.txt","r");
	string *s;

	s = malloc(sizeof(string));
	if(f == NULL || s == NULL)
		return -1;
	init_string(s);
	int x;
	while(x  != EOF	){
		x = get_token(f,s);
		printf("%i\n", x);
		
	}
	return 0;
}