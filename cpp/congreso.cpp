#include <congreso.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/*
Spaghetti code is a pejorative phrase for source code
that has a complex and tangled control structure,
especially one using many GOTO statements, exceptions,
threads, or other "unstructured" branching constructs.
It is named such because program flow is conceptually
like a bowl of spaghetti, i.e. twisted and tangled.

                      -From Wikipedia, the free Encyclopedia
*/

struct info {
  uint *solaux;
  uint *sol;
  uint *sorting_map; //mapeo de charlas ordenadas por audiencia
  uint solauxAsist, solAsist;
  charla *charlas, ordenadas;
  sala *salas;
  uint cantSalas, cantCharlas, restoAsist;
};
static bool hay_s(bool *solucion, charla *charlas, uint n) {
  bool solapa = false;
  for (uint i = 1; (i <= n - 1) && (!solapa); i++)
    if (solucion[i])
      for (uint j = i + 1; ((j <= n) && (!solapa)); j++)
        if (solucion[j] && (charlas[i].fin > charlas[j].inicio) &&
            (charlas[j].fin > charlas[i].inicio))
          solapa = true;

  return solapa;
} // hay_solapamiento

static bool hay_solap(uint *solucion, charla *charlas, uint n,
                               uint m) {
  bool solapa = false;

  // vector para pasar a la fucnion usada para el caso de una sala
  bool *solucion_h = new bool[n + 1];

  for (uint i = 1; (i <= m) && (!solapa); i++) {
    for (uint j = 1; j <= n; j++) {
      solucion_h[j] = (solucion[j] == i);
    }
    solapa = hay_s(solucion_h, charlas, n);
  }

  delete[] solucion_h;
  return solapa;
} // hay_solapamiento_m

static bool hay_desb(uint *solucion, charla *charlas, uint n, sala *salas,
                           uint m)
// devuelve true si alguna charla es desarrollada en una sala con un intervalo
// que no contiene al de la tarea
{
  bool desborde = false;

  for (uint i = 1; ((i <= n) && (!desborde)); i++) {
    //assert(solucion[i] <= m);
    (void)m; // para evitar el warning al compilar con -NDEBUG
    if ((solucion[i] != 0) &&
        ((charlas[i].inicio < salas[solucion[i]].inicio) ||
         (charlas[i].fin > salas[solucion[i]].fin)))
      desborde = true;
  }

  return desborde;
} // hay_desborde_m

static bool compatible (info res, int position) {
  bool ret = true;
  uint s = res.solaux[position-1];
  if (position > 1 && s != 0) {
    //charla entra en la sala
    if(res.charlas[position-1].inicio >= res.salas[s].inicio &&
       res.charlas[position-1].fin    <= res.salas[s].fin) {
      int i = 1;
      //compatible con todas las charlas de la sala
      while(i < position-1) {
        if(res.solaux[i] == s) {
          if ((res.charlas[position-1].inicio >= res.charlas[i].inicio &&
               res.charlas[position-1].inicio < res.charlas[i].fin)    ||
              (res.charlas[position-1].fin    > res.charlas[i].inicio  &&
               res.charlas[position-1].fin    <= res.charlas[i].fin))  {
            ret = false;
          }
        }
        i++;
      }
    } else {
      ret = false;
    }
  }
  return ret;
}
//predicado de poda
static bool viable (info res, int position) {
  return res.solauxAsist + res.restoAsist > res.solAsist;
}

static void copiar_array(uint *source, uint *&destination, uint size){
  for(uint i=1; i<=size; i++){
    destination[(int)i] = source[(int)i];
  }
}

static void max_asistentes_m_aux(info &res, int position) {
  if (compatible(res, position) && viable(res, position)) {
    uint s = 0;
    while(s <= res.cantSalas && position <= (int)res.cantCharlas) {
      res.solaux[position] = s;
      /*solo preciso updatear el campo solauxassit cuando pongo la sala
        o la quito*/
      if(s != 0) {
        res.solauxAsist = res.solauxAsist + res.charlas[position].asistentes;
        res.restoAsist = res.restoAsist - res.charlas[position].asistentes;
      }
      max_asistentes_m_aux(res, position + 1);
      if(s != 0) {
        res.solauxAsist = res.solauxAsist - res.charlas[position].asistentes;
        res.restoAsist = res.restoAsist + res.charlas[position].asistentes;
      }
      s++;
    }
    if (/*(int)res.cantCharlas+1 == position && */
         !hay_solap(res.solaux, res.charlas, res.cantCharlas, res.cantSalas) &&
         !hay_desb(res.solaux, res.charlas, res.cantCharlas, res.salas, res.cantSalas)&&
         res.solauxAsist >= res.solAsist) {
      copiar_array(res.solaux, res.sol, res.cantCharlas);
      res.solAsist = res.solauxAsist;
    }
  }
}
/*
devuelve true si un elemento ya se encuentra insertado en
un array objetivo.
*/
static bool inserted(uint *target, int j, uint size){
  bool res = false;
  for (int i=1; i< (int)size; i++){
    if((int)target[i] == j){
      res = true;
      i = size++;
    }
  }
  return res;
}
/*
Dada un array de charlas, devuelve un mapeo de estas
de manera tal que se encuentren ordenados de mayor a menor
asistentes. tiene orden n cubo. esta hech de manera chancha
y todavia por alguna razon no anda...
*/
static uint *sorting(charla *source, uint size){
  uint *destination_map = new uint[(int)size+1];
  //inicializacion
  for(int i = 0; i<=(int)size; i++){
    destination_map[i] = 0;
  }
  charla max = source[1];
  for(int i = 1; i<=(int)size; i++){
    max = source[1];
    for(int j = 1; j<=(int)size; j++){
      if ((source[j].asistentes >= max.asistentes) && (!inserted(destination_map, j, size))){
        max = source[j];
        destination_map[i] = j;
      }
    }
  }
  return destination_map;
}

uint *max_asistentes_m(charla *charlas, uint n, sala *salas, uint m) {
  info res;
  res.sol = new uint[(int)n+1];
  res.solaux = new uint[(int)n+1];
  res.restoAsist = 0;
  res.cantSalas = m;
  res.cantCharlas = n;
  res.charlas = charlas;
  res.salas = salas;
  res.solAsist = 0;
  res.solauxAsist = 0;
  for (int i = 0; i <= (int)n; i++) {
    res.solaux[i] = 0;
    res.sol[i] = 0;
    if (i != 0) {
      res.restoAsist = res.restoAsist + res.charlas[i].asistentes;
    }
  }

  res.sorting_map = sorting(res.charlas, n);

  max_asistentes_m_aux(res, 1);

  //uint *ret = res.sol;
  delete[] res.solaux;
  delete[] res.sorting_map;
  //delete res;

  return res.sol;
  //return ret;
}
