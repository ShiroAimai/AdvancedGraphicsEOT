// pch.h: questo è un file di intestazione precompilata.
// I file elencati di seguito vengono compilati una sola volta, in modo da migliorare le prestazioni per le compilazioni successive.
// Questa impostazione influisce anche sulle prestazioni di IntelliSense, incluso il completamento codice e molte altre funzionalità di esplorazione del codice.
// I file elencati qui vengono però TUTTI ricompilati se uno di essi viene aggiornato da una compilazione all'altra.
// Non aggiungere qui file soggetti a frequenti aggiornamenti; in caso contrario si perderanno i vantaggi offerti in termini di prestazioni.

#ifndef PCH_H
#define PCH_H

// aggiungere qui le intestazioni da precompilare
#include "framework.h"
#include <iostream>
#include <math.h>

using std::cout;
using std::endl;

using Scalar = double;

const Scalar EPSILON = 0.0001;
const Scalar EPSILON2 = EPSILON * EPSILON;


#endif //PCH_H
