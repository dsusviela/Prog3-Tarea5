#ifndef _CONGRESO_H
#define _CONGRESO_H

typedef unsigned int uint;

struct charla
    // La duracion (= fin - inicio) es mayor que 0.
    {
  uint inicio;
  uint fin;
  uint asistentes;
};

struct sala
    // La dispinibilidad (" fin - inicio) es mayor que 0.
    {
  uint inicio;
  uint fin;
};

uint *max_asistentes_m(charla *charlas, uint n, sala *salas, uint m);
/*
'charlas' es un arreglo de tamaño 'n + 1' y 'salas' es un arreglo de tamaño 'm +
1'.
Devuelve un array de tamaño 'n + 1' que representa la sala a la que es
asignada cada charla.
En todos los arreglos se ignora la posición 0.
La i-esima posicion del array devuelto corresponde a la i-esima charla.
Es la sala a la que fue asignada, que es un número entre 1 y m,
o 0 si no fue asignada.
La asignación debe maximizar la cantidad de asistentes a las charlas.
Los intervalos de desarrollo de dos charlas asignadas a la misma sala
no pueden superponerse.
El intervalo de tiempo de una charla debe estar contenido en la de la
sala a la que sea asignada.
*/

#endif /* congreso */
