#ifndef _TEST_HELPER_H
#define _TEST_HELPER_H

#include "congreso.hpp"

void check_asistentes_m(uint *solucion, charla *charlas, uint n, sala *salas,
                        uint m);
/*
'charlas' es un array de tamaño 'n + 1' y 'salas' es un array de tamaño 'm + 1'.
Comprueba que 'solucion' es una solución válida para max_asistentes_m dados
los parámetros. Imprime la cantidad de asistentes de 'solucion'.
*/

#endif /* TEST_HELPER */
