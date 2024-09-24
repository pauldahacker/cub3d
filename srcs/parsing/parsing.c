/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:35:32 by pde-masc          #+#    #+#             */
/*   Updated: 2024/09/23 15:35:34 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Implementing following logic:
    i.      find first wall from top-left
    ii.     face right
    iii.    - if there is a wall to the left, turn left and go there
                e.g.    -   1   1   1
                            |             
                        1   1   1   1

                        1   1   0   1
            - else if there is a wall in front, go there
                        -   -   1   1
                        
                        1   1---1   1

                        1   1   0   1
            - else if there is a wall to the right, turn right and go there.
                        -   -   -   -
                        
                        1   1   -   1
                            |
                        1   1   1   1
    iv.     repeat step iii until back at initial wall
*/
void test(void)
{
    printf("test\n");
}
