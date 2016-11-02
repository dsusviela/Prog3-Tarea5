#include <assert.h>
#include <stdio.h>

#include "include/congreso.hpp"
#include "include/test_helper.hpp"

/*
Lee desde la entrada estandar los datos de las charlas y las salas.
Los ejecuta y muestra resultados en la salida.
El formato de la entrada es


cantidadCharlas
<charlas>
cantidadSalas
<salas>


<charlas>
tiene una linea por cada charla con la forma
inicio-fin-asistentes

donde inicio, fin y asistentes son enteros no negativos y fin > inicio

<salas>
tiene una linea por cada sala con la forma
inicio-fin

donde inicio y fin son enteros no negativos y fin > inicio

*/

void imprimir(uint *solucion, int n) {
  for (int i = 1; i <= n; i++)
    printf("%d ", solucion[i]);
  printf("\n");
}

int main() {
  int res;

  uint cant_charlas;
  res = scanf("%u", &cant_charlas);
  assert(res == 1);
  (void)res; // para evitar el warning al compilar con -NDEBUG
  charla *charlas = new charla[cant_charlas + 1];
  // 0 es una posición no usada
  charlas[0].inicio = charlas[0].fin = charlas[0].asistentes = 0;
  for (uint i = 1; i <= cant_charlas; i++) {
    res = scanf("%u-%u-%u", &charlas[i].inicio, &charlas[i].fin,
                &charlas[i].asistentes);
    assert(res == 3);
    assert(charlas[i].inicio < charlas[i].fin);
  }

  uint cant_salas;
  res = scanf("%u", &cant_salas);
  assert(res == 1);
  sala *salas = new sala[cant_salas + 1];
  // 0 es una posición no usada
  salas[0].inicio = salas[0].fin = 0;
  for (uint i = 1; i <= cant_salas; i++) {
    res = scanf("%u-%u", &salas[i].inicio, &salas[i].fin);
    assert(res == 2);
    assert(salas[i].inicio < salas[i].fin);
  }

  uint *solucion_i = max_asistentes_m(charlas, cant_charlas, salas, cant_salas);
  check_asistentes_m(solucion_i, charlas, cant_charlas, salas, cant_salas);
  // imprimir (solucion_i, cant_charlas);

  delete[] solucion_i;
  delete[] charlas;
  delete[] salas;

  return 0;
}
