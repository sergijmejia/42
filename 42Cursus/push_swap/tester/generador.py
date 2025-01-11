# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    generador.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 12:52:15 by smejia-a          #+#    #+#              #
#    Updated: 2025/01/09 13:07:34 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Esta programa genera listas aleatorias de numeros para testear el push_swap#

from random import randint
from random import shuffle

vector_numeros = set()
while len(vector_numeros) < 100:
    vector_numeros.add(randint(1, 100))

vector_numeros = list(vector_numeros)

shuffle(vector_numeros)

print(" ".join(map(str, vector_numeros)))
