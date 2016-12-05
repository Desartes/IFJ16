#include "scanner.h"
#include "err.h"
int isspecific(char c){
	switch(c){
		case '+':	return 0;
		case '-':	return 0;
		case '*':	return 0;
		case '%':	return 0;
		case '/':	return 0;
		case '(':	return 0;
		case ')':	return 0;
		case '{':	return 0;
		case '}':	return 0;
		case '[':	return 0;
		case ']':	return 0;
		case '.':	return 0;
		case '&':	return 0;
		case '|':	return 0;
		case '>':	return 0;
		case '<':	return 0;
		case '=':	return 0;
		case '!':	return 0;
		case ',':	return 0;
		case ':':	return 0;
		case ';':	return 0;
		case '\\':	return 0;
		case '\'':	return 0;
	}
	return 1;
}
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
	s->length = 0;
	s->alloc  = 0;
	free(s->str);
}

int compare_keywords(string *s){
	if(!strcmp(s->str,"boolean"))
		return kw_boolean;
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
	if(!strcmp(s->str,"run"))
		return kw_run;
	if(!strcmp(s->str,"Main"))
		return kw_main;
	return FALSE;
}

int get_token(FILE *f,string *str){
	int state =  State_for_start;
	int c;
	int next_char = 0;
	int next_double = 0;
	int returnVal=1;
	int read = TRUE;
	clear_string(str);
	free_string(str);
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
				}
				else if (isdigit(c)){
					read = TRUE;
					state = State_for_digit;
					add_char_to_String(str,c);
				}
				else if(c == '_' || c == '$'){
					add_char_to_String(str,c);
					read = TRUE;
					state = State_for_id;
				}
				else{
					switch(c){
						case EOF:	read = FALSE; 	returnVal = EOF; 				break;
						case '/':	read = TRUE;	state = char_slash;				break;
						case '{':	read = FALSE;	returnVal = char_LMZatvorka;	break;
						case '}': 	read = FALSE;	returnVal = char_PMZatvorka;	break;
						case '(':	read = FALSE;	returnVal = char_LZatvorka;		break;
						case ')':	read = FALSE;	returnVal = char_PZatvorka;		break;
						case '[':	read = FALSE;	returnVal = char_LHZatvorka;	break;
						case ']':	read = FALSE;	returnVal = char_PHZatvorka;	break;
						case '.': 	read = FALSE; 	returnVal = char_bodka; 		break;
        			    case ',': 	read = FALSE; 	returnVal = char_ciarka;		break;
       				    case '+': 	read = TRUE;	state = char_plus; 				break;
         			  	case '-': 	read = TRUE; 	state = char_minus;				break;
						case '*': 	read = FALSE; 	returnVal = char_star;			break;
						case ':':	read = FALSE;	returnVal = char_dvoj_bodka;	break;
						case ';':	read = FALSE;	returnVal = char_bod_ciarka;	break;
						case '%':	read = FALSE;	returnVal = char_percento;		break;
						case '\'':	read = FALSE;	returnVal = char_apostrof;		break;
						case '\"':	read = TRUE;	state = char_uvodzovky;			break;
						case '<':	read = TRUE;	state = char_mensi;				break;
						case '>':	read = TRUE;	state = char_vacsi;				break;
						case '=':	read = TRUE;	state = char_rovnasa;			break;
						case '!':	read = TRUE;	state = char_vykricnik;			break;
						case '|':	read = TRUE;	state = char_pipe;				break;
						case '&':	read = TRUE;	state = char_amperesand;		break;
						case '\\':	read = TRUE;	state = char_backslash;			break;
						default :	read = FALSE;	returnVal =	ERR_LEX_ERR;		
					}
				}
				break;

			case char_plus :
				if(c == '+'){
					read = FALSE;
					returnVal = char_inc;
				}else{
					read = FALSE;
					returnVal = char_plus;
					ungetc(c,f);
				}
				break;

			case char_minus :
				if(c == '-'){
					read = FALSE;
					returnVal = char_dec;
				}else{
					read = FALSE;
					returnVal = char_minus;
					ungetc(c,f);
				}
				break;

			case char_slash:
				if(c == '/'){
					returnVal = komentar1;
					break;
				}else if(c == '*'){
					returnVal = komentar2;
					break;
				}else if(returnVal != komentar2 && returnVal != komentar1){
					state = State_for_start;
					returnVal = char_slash;
					ungetc(c,f);
				}

				if(returnVal == komentar1){
					if(c == '\n'){
						state = State_for_start;
					}
					if(c == EOF){
						returnVal = State_for_start;
					}
					break;
				}
				if(returnVal == komentar2){ 
					if(c == '*'){
						c = fgetc(f);
						if(c == '/'){
							state = State_for_start;
						}
						if(c == EOF){
							read = FALSE;
							returnVal = ERR_SYNTAX_ERR;
						}
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
/**************************************************************************/
/**************************************************************************/

			case State_for_kw :
				if(c == EOF){
					read = FALSE;
					returnVal = ERR_LEX_ERR;
				}
				if(c != '\0' && !isspace(c) && c != EOF){
					add_char_to_String(str,c);
					if(!isspecific(c)){
					str->str[str->length-1] ='\0';

						if(compare_keywords(str)){
							returnVal = compare_keywords(str);
						}else{
							returnVal = is_id;
						}
						read = FALSE;
						ungetc(c,f);
					}
				}else{
					read = FALSE;
					if(compare_keywords(str)){
						returnVal = compare_keywords(str);
					}else{
						returnVal = is_id;
					}
				}
				break;
/**************************************************************************/
/**************************************************************************/

				case State_for_id :
					if(c == EOF){
						read = FALSE;
						returnVal = ERR_LEX_ERR;
					}
					if(c != '\0' && !isspace(c) && c != EOF){
						add_char_to_String(str,c);
						if(!isspecific(c)){
							str->str[str->length-1] ='\0';
							
							returnVal = is_id;
							read = FALSE;
							ungetc(c,f);
						}
					}else{
						read = FALSE;
						returnVal = is_id;
					}
					break;

/**************************************************************************/
/**************************************************************************/

			case State_for_digit :
				add_char_to_String(str,c);
				if(c == 'e' || c == 'E'){
						read = TRUE;
						state = is_double;
						break;
					}
				if(!isdigit(c)){
					if(c == '.')
						next_double++;
					next_char++;
				}
				if(c == EOF){
					read = FALSE;
					returnVal = ERR_LEX_ERR;
				}
				if(c == '\0' || isspace(c) || c == ';' || !isspecific(c) || c == EOF){
					if( c == ';' || !isspecific(c) || c == EOF)
						next_char--;
					read = FALSE;
					if(next_char == 1 && next_double == 1){
						returnVal = is_double;
					}
					else if(next_char == 0){
						returnVal = is_int;
					}	
					else{
						returnVal = is_id;
					}
					str->str[str->length-1] ='\0';
					ungetc(c,f);
				}
				break;
/**************************************************************************/
/**************************************************************************/

			case is_double :
				if(c == '+' || c == '-' || isdigit(c) || c == '.'){
					next_char++;
					add_char_to_String(str,c);
					if(next_char == 1){
						if(c == '+'){
							returnVal = kladny_exp;
						}else if(c == '-'){
							returnVal = zaporny_exp;
						}else if(isdigit(c)){
							returnVal = kladny_exp;
						}else{
							read = FALSE;
							returnVal = ERR_LEX_ERR;
						}
					}
					if(next_char != 1 && (c == '+' || c == '-' )){
						read = FALSE;
						ungetc(c,f);
						str->str[str->length-1] ='\0';
						break;
					}
					if(c == '.'){
						next_double++;
						break;
					}
					if(next_char == 1){
						break;
					}
					if(next_double == 1){
						printf("%i\n",returnVal );
						if( returnVal == kladny_exp || returnVal == kladny_exp_I){
							returnVal = kladny_exp_D;
						}
						if(returnVal == zaporny_exp || returnVal == zaporny_exp_I){
							returnVal = zaporny_exp_D;
						}
					}else if(next_char != 1 && isdigit(c) && next_double == 0){
						if( returnVal == kladny_exp){
							returnVal = kladny_exp_I;
						}
						if(returnVal == zaporny_exp) {
							returnVal = zaporny_exp_I;
						}
					}else if(c == '.' && next_double != 1){
						ungetc(c,f);
						str->str[str->length-1] ='\0';
						read = FALSE;
					}
					
				}else{
					ungetc(c,f);
					read = FALSE;
				}
				break;
/**************************************************************************/
/**************************************************************************/
			case char_uvodzovky :
				if(c != '"'){
					read = TRUE;
					add_char_to_String(str,c);
				}else{
					read = FALSE;
					returnVal = is_string;
				}
				break;
		}
	}
	if(returnVal == kladny_exp){
		returnVal = kladny_exp_I;
	}
	return returnVal;
}
