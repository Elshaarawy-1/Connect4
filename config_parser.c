#include "config_parser.h"

bool get_matched_group(char *source, char *regexString, char *match)
{
    size_t maxGroups = 2;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        return false;
    };

    if (regexec(&regexCompiled, source, maxGroups, groupArray, 0) == 0)
    {
        unsigned int g = 0;
        for (g = 0; g < maxGroups; g++)
        {
            if (groupArray[g].rm_so == (size_t)-1)
                return false; // if captured groups are less than 2 then the regex didn't match correctly

            char sourceCopy[strlen(source) + 1];
            strcpy(sourceCopy, source);
            sourceCopy[groupArray[g].rm_eo] = 0;
            strcpy(match, sourceCopy + groupArray[g].rm_so);
        }
    }
    regfree(&regexCompiled);
    return true;
}

// bool read_trimmed_config_str(char *config_path, char * )
// {
//     FILE *file;
//     char *config_str = 0;
//     long length;
//     if ((file = fopen(config_path, "r")))
//     {
//         fseek(file, 0, SEEK_END);
//         length = ftell(file);
//         fseek(file, 0, SEEK_SET);
//         config_str = malloc(length);
//         char *config_str_trimmed = malloc(length);
//         if (config_str)
//         {
//             fread(config_str, 1, length, file);
//             remove_spaces(config_str_trimmed, config_str);
//             printf("%s\n", config_str_trimmed);
//             fclose(file);
//             return true;
//         }
//         fclose(file);
//         return false;
//     }
//     return false;
// }

bool serialize_child(char *source, const char *child_tag_name, int *value)
{
    char regex_match_str[50];
    sprintf(regex_match_str, "<%s>([0-9]+)</%s>", child_tag_name,child_tag_name);

    char *match = calloc(strlen(source), sizeof(char));
    bool serialization_success = get_matched_group(source, regex_match_str, match);
    if (!serialization_success)
    {
        return false;
    }

    serialization_success = str_to_int(match, value);
    return serialization_success;
}

bool serialize_config_str(char *config_str, Configuration *config)
{
    char *match = calloc(strlen(config_str), sizeof(char));
    bool serialization_success = true;

    serialization_success = get_matched_group(config_str, "<Configurations>(.*?)</Configurations>", match);

    if (!serialization_success)
    {
        return false;
    }

    serialization_success = serialize_child(match, "Height", &(config->height));

    if (!serialization_success)
    {
        return false;
    }

    serialization_success = serialize_child(match, "Width", &(config->width));

    if (!serialization_success)
    {
        return false;
    }

    return serialize_child(match, "Highscores", &(config->highscore));
}

bool parse_config(char *config_path, Configuration *config)
{
    FILE *file;
    char *config_str = 0;
    long length;
    if ((file = fopen(config_path, "r")))
    {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        config_str = malloc(length);
        char *config_str_trimmed = malloc(length);
        if (config_str)
        {
            fread(config_str, 1, length, file);
            remove_spaces(config_str_trimmed, config_str);
            fclose(file);
            return serialize_config_str(config_str_trimmed, config);
        }
        fclose(file);
        return false;
    }
    return false;
}