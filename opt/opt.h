//  Partie interface du module opt (gestion d'option).
//
//  Ce module permet de mettre en place au sein d'un programme, une gestion
//    d'options pour son utilisateur.

#ifndef OPT__H
#define OPT__H

#include <stdbool.h>
#include <stdlib.h>

//  struct optparam optparam : type et nom de type d'un contrôleur regroupant
//    les informations nécessaire pour gérer une option.
typedef struct optparam optparam;

//  optreturn : enumaration des valeurs de retours possible de la fonctions
//    opt_init. (chaque utilisation des valeurs des enumes est spécifier dans la
//    spécification de la fonction opt_init)
typedef enum {
  STOP_PROCESS,
  ERROR_FUN,
  ERROR_PARAM,
  DONE,
} optreturn;

//  opt_gen : Tente d'allouer les resources néssaires pour gérer une options.
//    Avec valeur initiale les champs optshort, optlong représente
//    respectivement les version courte et longue de l'option. desc est une
//    chaine de carractère, la description de l'option. le booléen vaut vrai si
//    l'option demande un paramètre et faux sinon. la fonction fun représente
//    les actions l'ors de l'appel de l'option. Renvoie NULL en cas de
//    dépassement de capacité. Renvoie sinon un pointer vers la structure
//    associé a cette option.
extern optparam *opt_gen(const char *optshort, const char *optlong,
    const char *desc, bool arg, int (*fun)(void *cntxt, const char *value));

//  opt_init : Pour toutes les options représenté dans le tableau argv de
//    longueur argc, qui sont présente dans le talbeau d'option aopt, effectue
//    effectue le traitement adequatement definie a la création de l'option
//    (avec comme paramettre a ce traitement cntxt et si l'option necessite un
//    argument alors passe la chaine suivante en argument, sinon la chaine
//    représentant l'option). Si ce traitement echoue par manque d'un paramettre
//    à l'option actuellement executer, alors la fonction retourne ERROR_PARAM.
//    Si le traitement de l'option echoue alors, la fonction retourne ERROR_FUN.
//    Sinon en cas de succés du traitement de toutes les options, retourne DONE.
//    Une options par default existe, celle du "help" (-h et --help pour y
//    accéder) si cette options est appeler la fonction retourne STOP_PROCESS et
//     n'a donc pas effectuer le traitement des options pas encore traiter
//    (usage et desc correspondes respectivements une descriptions de la façcon
//    dont il faut utiliser le programme et ce qu'il produit). Pour toutes
//    chaine de caractère présente dans argv qui ne correspont ni à une options
//    ni a l'arguments d'une options, le traitement de cette chaine est assurer
//    par la fonction other qui prend en paramettre cntxt
//    (un pointeur sur un context).
extern optreturn opt_init(char **argv, int argc, optparam **aopt,
    size_t nmemb, void (*other)(void *cntxt, const char *value), void *cntxt);

#endif
