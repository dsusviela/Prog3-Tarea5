#include <congreso.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>


struct info {
  uint *solaux;
  uint *sol;
  uint solauxAsist, solAsist;
  charla *charlas;
  sala *salas;
  int cantSalas, cantCharlas, restoAsist;
};

bool compatible (info res, int position) {
  bool ret = true;
  uint s = res.solaux[position-1];
  if (position > 1 && s != 0) {
    if(res.charlas[position-1].inicio >= res.salas[s].inicio &&
        res.charlas[position-1].fin <= res.salas[s].fin) {
      int i = 1;
      while(i < position-1) {
        if(res.solaux[i] == s) {
          if ((res.charlas[position-1].inicio >= res.charlas[i].inicio &&
              res.charlas[position-1].inicio < res.charlas[i].fin) ||
              (res.charlas[position-1].fin > res.charlas[i].inicio &&
                  res.charlas[position-1].fin <= res.charlas[i].fin)) {
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

bool viable (info res, int position) {

  return res.solauxAsist + res.restoAsist > res.solAsist;
}



void max_asistentes_m_aux(info &res, int position) {
  if (compatible(res, position) && viable(res, position)) {
    if (position == res.cantCharlas+1 && res.solauxAsist >= res.solAsist) {
      memcpy(res.solaux, res.sol, sizeof(res.sol));
    }
    uint s = 0;
    while(s <= res.cantSalas && position <= res.cantCharlas) {
      res.solaux[position] = s;
      if(s != 0) {
        res.solauxAsist = res.solAsist + res.charlas[position].asistentes;
      }
      res.restoAsist = res.restoAsist + res.charlas[position].asistentes;
      max_asistentes_m_aux(res, ++position);
      if(s != 0) {
        res.solaux = res.solAsist - res.charlas[position].asistentes;
      }
      res.restoAsist = res.restoAsist - res.charlas[position].asistentes;
      s++;
    }
  }
}





uint *max_asistentes_m(charla *charlas, uint n, sala *salas, uint m) {
  info res = new info;
  res.sol = new uint[(int)n+1];
  res.solaux = new uint[(int)n+1];
  res.restoAsist = 0;
  for (int i = 0; i <= n; i++) {
    res.solaux[i] = 0;
    res.sol[i] = 0;
    if (i != 0) {
      res.restoAsist = res.restoAsist + res.charlas[i].asistentes;
    }
  }
  res.cantSalas = n;
  res.cantCharlas = m;
  res.charlas = charlas;
  res.salas = salas;
  res.solAsist = 0;
  res.solauxAsist = 0;
  max_asistentes_m_aux(res, 1);

  uint *ret = res.sol;
  delete[] res.solaux;
  delete res;

  return ret;
}
