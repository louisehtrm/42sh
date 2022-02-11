#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

void free_list(struct list *lst)
{
    if (lst == NULL)
        return;
    struct list *tmp = lst->next;
    while (tmp)
    {
        free(lst);
        lst = tmp;
        tmp = tmp->next;
    }
    free(lst);
}

void single_quote(size_t *start, size_t *end, char *str)
{
    size_t i = *start;
    size_t mid = 0;
    while (i < *end)
    {
        if (str[i] == '\'')
        {
            if (mid)
                mid = 0;
            else if (i == 0 || (i > 0 && str[i - 1] != '\\'))
                mid = 1;
        }
        i++;
    }
    if (mid == 1)
        errx(2, "Syntax error");
}

void redirection(size_t *start, size_t *end, size_t *i, char *str)
{
    if (str[(*i) - 1] != ' ')
    {
        size_t j = *start;
        while (j < *i)
        {
            if (str[j] < '0' || str[j] > '9')
            {
                *end = *i;
                return;
            }
            j++;
        }
    }
    (*i)++;
    char c = str[*i];
    if (c == '&' || c == '>' || (c == '|' && str[(*i) - 1] == '>'))
        *end = ++(*i);
    else
        *end = *i;
    return;
}

void pipe_or(size_t *start, size_t *end, size_t *i, char *str)
{
    if (*start == *i)
    {
        (*i)++;
        if (str[*i] == '|')
            *end = ++(*i);
        else
            *end = *i;
    }
    *end = *i;
}

void or_esp(size_t *start, size_t *end, size_t *i, char *str)
{
    if (*start == *i)
    {
        (*i)++;
        if (str[*i] == '&')
            *end = ++(*i);
        else
            *end = *i;
    }
    *end = *i;
}

struct list *token(char *str, size_t *length, size_t size)
{
    struct list *lst = my_malloc(sizeof(struct list));
    struct list *first = lst;
    size_t i = 0;
    size_t is_sq = 0;
    size_t one_sq;
    while (i < size && str[i] == ' ')
        i++;
    while (i < size)
    {
        struct list *new = my_malloc(sizeof(struct list));
        lst->next = new;
        lst = lst->next;
        *length = *length + 1;
        char c = str[i];
        size_t start = i;
        size_t end = i;
        while ((i < size && is_sq)
               || (i < size && c != ' ' && c != ';' && c != '&' && c != '!'
                   && c != '|' && c != '\n' && c != '{' && c != '}' && c != '>'
                   && c != '<' && c != '(' && c != ')'))
        {
            if (c == '\'')
            {
                one_sq = 1;
                if (is_sq)
                    is_sq = 0;
                else if (i == 0 || (i > 0 && str[i - 1] != '\\'))
                    is_sq = 1;
            }
            i++;
            c = str[i];
        }
        if (c == '>' || c == '<')
            redirection(&start, &end, &i, str);
        else if (c == '|')
            pipe_or(&start, &end, &i, str);
        else if (c == '&')
            or_esp(&start, &end, &i, str);
        else if (start == i)
            end = ++i;
        else
            end = i;
        if (one_sq)
            single_quote(&start, &end, str);
        char *tok = my_malloc(end - start + 1);
        int k = start;
        for (size_t j = 0; j < end - start; j++)
            tok[j] = str[k++];
        tok[end - start] = '\0';
        lst->value = tok;
        lst->next = NULL;
        while (str[i] == ' ')
            i++;
    }
    struct list *start = first->next;
    free(first);
    return start;
}

struct list *lexer_list(char *str, size_t *length)
{
    size_t size = strlen(str);
    struct list *lst = token(str, length, size);
    return lst;
}
