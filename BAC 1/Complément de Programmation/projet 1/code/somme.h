/**
 * \file somme.h
 * \brief Header pour la somme min-max d'un tableau
 * \author Benoit Donnet, Géraldine Brieven -- Université de Liège (ULiège)
 * \version 0.1
 * \date 03/12/2022
 *
 * Implémente la somme min-max d'un tableau T.
 */

#ifndef __SOMME__
#define __SOMME__

/*
 * @pre: T initialisé ∧ N > 0 ∧ min_pos != NULL ∧ max_pos != NULL
 * @post: T = T_0 ∧ N = N_0 ∧ sum = SUM(T,inf,sup) ∧ min_pos = MINPOS(T,0,N) ∧ max_pos = MAXPOS(T,0,N)
 */
int somme(int *T, int N,  int *min_pos, int *max_pos);

#endif
