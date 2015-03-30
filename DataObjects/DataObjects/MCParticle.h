#ifndef MCParticle_H 
#define MCParticle_H

// Reference to the vertex in which the particle disappeared.
// author: C. Bernet, B. Hegner

#include "DataObjects/BareParticle.h"
#include "DataObjects/GenVertexHandle.h"
#include "DataObjects/GenVertexHandle.h"


class MCParticle {
public:
  BareParticle Core; //Basic particle information. 
  GenVertexHandle StartVertex; //Reference to the vertex in which the particle was created. 
  GenVertexHandle EndVertex; //Reference to the vertex in which the particle disappeared. 

};

#endif