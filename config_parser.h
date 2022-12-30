#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <regex.h>
#include "helpers.h"
#include "configuration.h"

bool get_matched_group(char *source, char *regexString, char *match);

bool parse_config(char *config_path, Configuration *config);

bool serialize_config_str(char * config_str, Configuration * config);

bool serialize_child(char *source, const char *child_tag_name, int *value);

#endif