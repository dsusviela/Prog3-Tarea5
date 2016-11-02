#include "../include/test_helper.hpp"
#include <stdio.h>
#include <assert.h>

static bool hay_solapamiento(bool *solucion, charla *charlas, uint n) {
  bool solapa = false;
  for (uint i = 1; (i <= n - 1) && (!solapa); i++)
    if (solucion[i])
      for (uint j = i + 1; ((j <= n) && (!solapa)); j++)
        if (solucion[j] && (charlas[i].fin > charlas[j].inicio) &&
            (charlas[j].fin > charlas[i].inicio))
          solapa = true;

  return solapa;
} // hay_solapamiento

static bool hay_solapamiento_m(uint *solucion, charla *charlas, uint n,
                               uint m) {
  bool solapa = false;

  // vector para pasar a la fucnion usada para el caso de una sala
  bool *solucion_h = new bool[n + 1];

  for (uint i = 1; (i <= m) && (!solapa); i++) {
    for (uint j = 1; j <= n; j++) {
      solucion_h[j] = (solucion[j] == i);
    }
    solapa = hay_solapamiento(solucion_h, charlas, n);
  }

  delete[] solucion_h;
  return solapa;
} // hay_solapamiento_m

static bool hay_desborde_m(uint *solucion, charla *charlas, uint n, sala *salas,
                           uint m)
// devuelve true si alguna charla es desarrollada en una sala con un intervalo
// que no contiene al de la tarea
{
  bool desborde = false;

  for (uint i = 1; ((i <= n) && (!desborde)); i++) {
    assert(solucion[i] <= m);
    (void)m; // para evitar el warning al compilar con -NDEBUG
    if ((solucion[i] != 0) &&
        ((charlas[i].inicio < salas[solucion[i]].inicio) ||
         (charlas[i].fin > salas[solucion[i]].fin)))
      desborde = true;
  }

  return desborde;
} // hay_desborde_m

static uint asistentes_total_m(uint *solucion, charla *charlas, uint n) {
  uint result = 0;
  for (uint i = 1; i <= n; i++)
    if (solucion[i] > 0)
      result += charlas[i].asistentes;
  return result;
} // asistentes_total_m

void check_asistentes_m(uint *solucion, charla *charlas, uint n, sala *salas,
                        uint m) {
  printf("Solucion %s. asistentes: %d. \n",
         (hay_solapamiento_m(solucion, charlas, n, m)) ||
                 (hay_desborde_m(solucion, charlas, n, salas, m))
             ? "NO-Valida"
             : "Valida",
         asistentes_total_m(solucion, charlas, n));
}
