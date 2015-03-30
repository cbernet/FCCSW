#include "HepMCConverter.h"

#include "DataObjects/LorentzVector.h"

DECLARE_COMPONENT(HepMCConverter)

HepMCConverter::HepMCConverter(const std::string& name, ISvcLocator* svcLoc):
  GaudiAlgorithm(name, svcLoc)
{
  declareInput("hepmc", m_hepmchandle);
  declareOutput("genparticles", m_genphandle);
  declareOutput("genvertices", m_genvhandle);
}

StatusCode HepMCConverter::initialize() {
  return GaudiAlgorithm::initialize();
}

StatusCode HepMCConverter::execute() {
  HepMCEntry* theEvent = m_hepmchandle.get();
  const HepMC::GenEvent* event = theEvent->getEvent();
  MCParticleCollection* particles = new MCParticleCollection();
  GenVertexCollection* vertices = new GenVertexCollection();

  //    std::cout<<"Nvtx = "<<hepmcevt->vertices_size()<<std::endl;
  typedef std::map<HepMC::GenVertex*, GenVertexHandle > VertexMap;
  VertexMap vtx_map;
  for ( HepMC::GenEvent::vertex_const_iterator iv = event->vertices_begin();
	iv != event->vertices_end(); ++iv ) {
    //      (*iv)->print();
    // std::cout<<"hepmc vertex "<<(*iv)<<endl;
    const HepMC::FourVector& vpos = (*iv)->position();
    GenVertexHandle vtx = vertices->create();
    // std::cout<<"vertex "<<vtx.index()<<"/"<<vtx.containerID()<<std::endl;
    vtx.mod().Position.X = vpos.x();
    vtx.mod().Position.Y = vpos.y();
    vtx.mod().Position.Z = vpos.z();
    vtx.mod().Ctau = vpos.t();
    vtx_map.emplace(*iv, vtx);
    // std::cout<<" in map "<<vtx_map[*iv].index()<<"/"<<vtx_map[*iv].containerID()<<std::endl;
  }

  typedef HepMC::GenEvent::particle_const_iterator Ipart;
  for(Ipart ipart=event->particles_begin(); 
      ipart!=event->particles_end(); ++ipart) {
    const HepMC::GenParticle& ptc = **ipart; 
    // if(ptc.status()==1) { 
    // ptc.print();
    MCParticleHandle outptc = particles->create();
    BareParticle& core = outptc.mod().Core;
    core.Type = ptc.pdg_id();
    core.Status = ptc.status(); 
    core.P4.Pt = ptc.momentum().perp();
    core.P4.Eta = ptc.momentum().eta();
    core.P4.Phi = ptc.momentum().phi();
    core.P4.Mass = ptc.momentum().m();
  

    typedef VertexMap::const_iterator IVM;
    IVM prodvtx = vtx_map.find(ptc.production_vertex());
    if(prodvtx!=vtx_map.end()) {
      outptc.mod().StartVertex = prodvtx->second;
      std::cout<<"prod vertex found "
      <<ptc.production_vertex()<<" "
      <<prodvtx->first<<" "
      <<prodvtx->second.index()<<"/"
      <<prodvtx->second.containerID()<<std::endl;	
    }
    else{
      std::cout<<"no prod vertex found"<<std::endl;
      ptc.print();
    }
    IVM endvtx = vtx_map.find(ptc.end_vertex());
    if(endvtx!=vtx_map.end()) {
      outptc.mod().EndVertex = endvtx->second;
    }
    else{
      std::cout<<"no end vertex found"<<std::endl;
      ptc.print();
    }
  }
  m_genvhandle.put(vertices);
  m_genphandle.put(particles);
  return StatusCode::SUCCESS;
}

StatusCode HepMCConverter::finalize() {
  return GaudiAlgorithm::finalize();
}
