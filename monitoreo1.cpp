

recorrido viajar1985 (vertice v, grafo g) {
	bool encontrado = false;
	recorrido r = iniciarRecorrido();
	agregarRecorrido(v, r);
	v->visitado = true;                      //marcar v como visitado
	cola c = crearCola();
	encolarAdyacentesNoVisitados(v, c, r);   
	//en cada elemento de la cola se incluye el camino hasta ese vertice

 	while (!encontrado) {
 		if (tope(c)->visistado = false) {
	 		if (tope(c)->anio == 1985) {
	 			agregarRecorrido(tope(c), tope(c)->camino);
	 			encontrado = true;
	 			r = tope(c)->camino;
	 		} else {
	 		tope(c)->visitado = true;
	 		recorrido q = tope(c)->camino;
	 		agregarRecorrido(tope(c), q);
	 		encolarAdyacentesNoVisitados(tope(c), c, q);
	 		}
	 	}	 		
	 	desencolar(c);
 	}
 	return r;
}

bool existeCiclo (vertice v, grafo g) {
	bool encontrado = false;
	cola c = crearCola();
	encolarAdyacentesNoVisitados(v, c);
	while (!encontrado && !esColaVacia(c)) {
	 	if (tope(c)->visistado = false) 
		 	if (tope(c)->anio == v->anio) 
		 		encontrado = true;
			else {
				tope(c)->visitado = true;
				encolarAdyacentesNoVisitados(tope(c), c);
		}
		desencolar(c);
}