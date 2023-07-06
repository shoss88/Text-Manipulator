#include "hw6.h"

int main(int argc, char *argv[]) {
    extern char *optarg;
    extern int optind;

    if (argc < 7){
        return MISSING_ARGUMENT;
    }

    int arg;
    int s_count = 0, r_count = 0, w_count = 0, l_count = 0;
    char *s_param, *r_param, *l_param;
    while ((arg = getopt(argc, argv, "s:r:wl:")) != -1){
        switch(arg){
            case 's':
                s_count++;
                s_param = optarg;
                break;
            case 'r':
                r_count++;
                r_param = optarg;
                break;
            case 'w':
                w_count++;
                break;
            case 'l':
                l_count++;
                l_param = optarg;
                break;
        }
    }
    if (s_count > 1 || r_count > 1 || w_count > 1 || l_count > 1){
        return DUPLICATE_ARGUMENT;
    }

    FILE *input = fopen(argv[argc - 2], "r");
    FILE *output = fopen(argv[argc - 1], "w");
    if (strstr(argv[argc - 2], ".txt") == NULL || input == NULL){
        return INPUT_FILE_MISSING;
    }
    else if (strstr(argv[argc - 1], ".txt") == NULL || output == NULL){
        return OUTPUT_FILE_UNWRITABLE;
    }

    if (s_count == 0 || s_param == NULL || s_param[0] == '-'){
        return S_ARGUMENT_MISSING;
    }
    else if (r_count == 0 || r_param == NULL || r_param[0] == '-'){
        return R_ARGUMENT_MISSING;
    }

    int start_line = 0, end_line = 0;
    if (l_count > 0){
        if (l_param == NULL){
            return L_ARGUMENT_INVALID;
        }
        char *to_parse = strtok(l_param, ",");
        if (to_parse == NULL){
            return L_ARGUMENT_INVALID;
        }
        start_line = strtol(to_parse, &to_parse, 10);
        to_parse = strtok(NULL, ",");
        if (to_parse == NULL){
            return L_ARGUMENT_INVALID;
        }
        end_line = strtol(to_parse, &to_parse, 10);
        if (start_line <= 0 || end_line <= 0 || start_line > end_line){
            return L_ARGUMENT_INVALID;
        }
    }
    if (w_count > 0){
        if (s_param[0] == '*' && s_param[strlen(s_param) - 1] == '*'){
            return WILDCARD_INVALID;
        }
        else if (strchr(s_param, '*') == NULL){
            return WILDCARD_INVALID;
        }
    }
    if (w_count == 0){
        int line = 1;
        if (l_count == 0){
            line = 0;
        }
        int ch;
        while (line < start_line){
            ch = fgetc(input);
            if (ch == '\n'){
                line++;
            }
            fputc(ch, output);
        }
        unsigned int matching = 0;
        char str[strlen(s_param)];
        while ((ch = fgetc(input)) != EOF && line <= end_line){
            for (unsigned int i = 0; i < strlen(s_param); i++){
                if (ch == '\n' && l_count > 0){
                    line++;
                }
                if (matching == 0 && ch != s_param[i]){
                    i = strlen(s_param);
                    fputc(ch, output);
                }
                else if (matching > 0 && ch != s_param[i]){
                    matching = 0;
                    if (ch == '\n' && l_count > 0){
                        line--;
                    }
                    ungetc(ch, input);
                    for (unsigned int j = 0; j < i; j++){
                        fputc(str[j], output);
                    }
                    i = strlen(s_param);
                }
                else if (ch == s_param[i]){
                    matching += 1;
                    str[i] = ch;
                    ch = fgetc(input);
                }
            }
            if (ch == EOF && matching == strlen(s_param)){
                fputs(r_param, output);
                line = end_line + 1;
            }
            else if (ch != EOF && matching == strlen(s_param)){
                fputs(r_param, output);
                fputc(ch, output);
                matching = 0;
            }
        }
        if (ch != EOF){
            fputc(ch, output);
            while ((ch = fgetc(input)) != EOF){
                fputc(ch, output);
            }
        }
    }
    else{
        int line = 1;
        if (l_count == 0){
            line = 0;
        }
        int ch;
        while (line < start_line){
            ch = fgetc(input);
            if (ch == '\n'){
                line++;
            }
            fputc(ch, output);
        }
        if (s_param[strlen(s_param) - 1] == '*'){
            unsigned int matching = 0;
            fpos_t current_pos;
            fgetpos(input, &current_pos);
            while ((ch = fgetc(input)) != EOF && line <= end_line){
                while (isspace(ch) || ispunct(ch)){
                    if (ch == '\n' && l_count > 0){
                        line++;
                    }
                    fputc(ch, output);
                    fgetpos(input, &current_pos);
                    ch = fgetc(input);
                }
                for (unsigned int i = 0; i < strlen(s_param) - 1; i++){
                    if (ch == '\n' && l_count > 0){
                        line++;
                    }
                    if (matching == 0 && ch != s_param[i]){
                        i = strlen(s_param);
                        fputc(ch, output);
                        ch = fgetc(input);
                        while (!isspace(ch) && !ispunct(ch) && ch != EOF){
                            fputc(ch, output);
                            ch = fgetc(input);
                        }
                        if (ch != EOF){
                            fputc(ch, output);
                        }
                        if (ch == '\n' && l_count > 0){
                            line++;
                        }
                        fgetpos(input, &current_pos);
                    }
                    else if (matching > 0 && ch != s_param[i]){
                        matching = 0;
                        if (ch == '\n' && l_count > 0){
                            line--;
                        }
                        fsetpos(input, &current_pos);
                        ch = fgetc(input);
                        while (!isspace(ch) && !ispunct(ch) && ch != EOF){
                            fputc(ch, output);
                            ch = fgetc(input);
                        }
                        if (ch != EOF){
                            fputc(ch, output);
                        }
                        i = strlen(s_param);
                        fgetpos(input, &current_pos);
                    }
                    else if (ch == s_param[i]){
                        matching += 1;
                        ch = fgetc(input);
                    }
                }
                if (ch == EOF && matching == strlen(s_param) - 1){
                    while (!isspace(ch) && !ispunct(ch)){
                        ch = fgetc(input);
                    }
                    fputs(r_param, output);
                    line = end_line + 1;
                }
                else if (ch != EOF && matching == strlen(s_param) - 1){
                    while (!isspace(ch) && !ispunct(ch) && ch != EOF){
                        ch = fgetc(input);
                    }
                    fputs(r_param, output);
                    if (ch != EOF){
                        fputc(ch, output);
                    }
                    else{
                        line = end_line + 1;
                    }
                    matching = 0;
                }
            }
        }
        else if (s_param[0] == '*'){
            unsigned int matching = 0;
            fpos_t current_pos;
            fgetpos(input, &current_pos);
            while ((ch = fgetc(input)) != EOF && line <= end_line){
                while (isspace(ch) || ispunct(ch)){
                    if (ch == '\n' && l_count > 0){
                        line++;
                    }
                    fputc(ch, output);
                    fgetpos(input, &current_pos);
                    ch = fgetc(input);
                }
                for (unsigned int i = 1; i < strlen(s_param); i++){
                    if (ch == '\n' && l_count > 0){
                        line++;
                    }
                    if (ch != s_param[i]){
                        matching = 0;
                        i = 1;
                        while (ch != s_param[i] && !isspace(ch) && !ispunct(ch) && ch != EOF){
                            ch = fgetc(input);
                        }
                        if (ch == s_param[i]){
                            matching += 1;
                            ch = fgetc(input);
                        }
                        else if (isspace(ch) || ispunct(ch) || ch == EOF){
                            if (ch == '\n' && l_count > 0){
                                line--;
                            }
                            fsetpos(input, &current_pos);
                            ch = fgetc(input);
                            while (!isspace(ch) && !ispunct(ch) && ch != EOF){
                                fputc(ch, output);
                                ch = fgetc(input);
                            }
                            if (ch != EOF){
                                fputc(ch, output);
                            }
                            i = strlen(s_param);
                            fgetpos(input, &current_pos);
                        }
                    }
                    else if (ch == s_param[i]){
                        matching += 1;
                        ch = fgetc(input);
                    }
                }
                if (ch == EOF && matching == strlen(s_param) - 1){
                    fputs(r_param, output);
                    line = end_line + 1;
                }
                else if (ch != EOF && matching == strlen(s_param) - 1){
                    if (isspace(ch) || ispunct(ch)){
                        fputs(r_param, output);
                        fputc(ch, output);
                        fgetpos(input, &current_pos);
                    }
                    else {
                        ungetc(ch, input);
                    }
                    matching = 0;
                }
            }
        }
        if (ch != EOF){
            fputc(ch, output);
            while ((ch = fgetc(input)) != EOF){
                fputc(ch, output);
            }
        }
    }
    fclose(input);
    fclose(output);
    
    return 0;
}
