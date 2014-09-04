// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxINIFile.h
 *
 *  $Id: FxINIFile.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _INI_FILE_H_
#define _INI_FILE_H_

#include <stdio.h>
#include <string.h>

#define MAX_FILE_SIZE 1024*16
#define LEFT_BRACE '['
#define RIGHT_BRACE ']'

/*
* This class read the config file for the program
*/

class INIFile
{
public:
    static int read_profile_string(const char *file,
                                    const char *section,
                                    const char *key,
                                    char *value,
                                    int size,
                                    const char *default_value);
    static int read_profile_int(const char *file,
                                const char *section,
                                const char *key,
                                int default_value);

    static int write_profile_string(const char *file,
                                    const char *section,
                                    const char *key,
                                    const char *value);
private:
    static int load_ini_file(const char *file,
                                char *buf,
                                int *file_size);
    static int newline(char c);
    static int end_of_string(char c);
    static int left_barce(char c);
    static int isright_brace(char c );
    static int parse_file(const char *section,
                            const char *key,
                            const char *buf,
                            int *sec_s,
                            int *sec_e,
                            int *key_s,
                            int *key_e,
                            int *value_s,
                            int *value_e);
};

#endif
