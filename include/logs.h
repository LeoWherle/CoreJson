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
        #define WHERE __FILE__, __LINE__, __func__
        #define FM  "%s:%d:%s(): "
        #define FLOG(f, ft, ...) fprintf(f, FM ft "\n", WHERE , ##__VA_ARGS__)
        #undef WHERE
        #undef FM
        #define DERR(str) perror(str)
    #else
        #define FLOG(fmt, ...)
        #define DERR(str)
    #endif

#endif /* !LOGS_H_ */
