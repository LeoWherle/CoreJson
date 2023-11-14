/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** logs
*/

#ifndef LOGS_H_
// clang-format off
    #define LOGS_H_

    #ifndef DEBUG
        #include <stdio.h>
        #define WHERE __FILE__, __LINE__, __func__
        #define FM  "%s:%d:%s(): "
        #define FLOG(f, ft, ...) fprintf(f, FM ft "\n", WHERE , ##__VA_ARGS__)
        #define DERR(str) perror(str)
    #else
        #define FLOG(fmt, ...)
        #define DERR(str)
    #endif
// clang-format on

#endif /* !LOGS_H_ */
