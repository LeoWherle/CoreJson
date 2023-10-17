/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** logs
*/

#ifndef LOGS_H_
    #define LOGS_H_

    #ifdef DEBUG
        #include <stdio.h>
        #define FLOG(fstream, fmt, ...) \
            fprintf(fstream, "%s:%d:%s(): " fmt "\n", __FILE__, \
            __LINE__, __func__, ##__VA_ARGS__)
        #define DERR(str) \
            perror(str)
    #else
        #define FLOG(fmt, ...)
        #define DERR(str)
    #endif

#endif /* !LOGS_H_ */
