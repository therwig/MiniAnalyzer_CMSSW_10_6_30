// -*- C++ -*-
//
// Package:    L1Trigger/L1TriggerAnalyzer
// Class:      L1TriggerAnalyzer
//
 
// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
// #include "CommonTools/UtilAlgos/interface/TFileService.h"
// #include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/L1Trigger/interface/L1JetParticle.h"

// #include "DataFormats/L1Trigger/interface/L1Candidate.h"
#include "DataFormats/L1Trigger/interface/BXVector.h"
#include "DataFormats/L1Trigger/interface/Jet.h"

//class to extract Vertex information
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

//class to extract Packed Candidate information
// #include "DataFormats/PatCandidates/interface/PackedCandidate.h"
// #include "DataFormats/VertexReco/interface/Vertex.h"
// #include "DataFormats/Candidate/interface/iterator.h"

//classes to save data
#include "TTree.h"
#include "TFile.h"
#include "TRandom3.h"
#include <vector>
using std::vector;

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.



class L1TriggerAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit L1TriggerAnalyzer(const edm::ParameterSet&);
      ~L1TriggerAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

    bool isData;
    edm::EDGetTokenT<vector<l1extra::L1JetParticle> > centralJetToken_;
    edm::EDGetTokenT<vector<l1extra::L1JetParticle> > forwardJetToken_;
    edm::EDGetTokenT<vector<l1extra::L1JetParticle> > isoTauToken_;
    edm::EDGetTokenT<vector<l1extra::L1JetParticle> > tauToken_;

    
    edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
    edm::EDGetTokenT<reco::BeamSpot> beamToken_;
    edm::EDGetTokenT<BXVector<l1t::Jet> > caloStage2DigisToken_;
    edm::EDGetTokenT<double> rhoToken_;
    
    // ----------member data ---------------------------
      
    TFile *mfile;
    TTree *mtree;
    TRandom3* rand;
    
    std::vector<float> jet_pt;
    std::vector<float> jet_ptSub;
    std::vector<float> jet_eta;
    std::vector<float> jet_phi;
    std::vector<float> fwdjet_pt;
    std::vector<float> isotau_pt;
    std::vector<float> tau_pt;
    float ht, htSub;
    int PV_npvs;
    float PV_npvs_smr1;
    float PV_npvs_smr3;
    int PV_npvsGood;
    float PV_npvsGood_smr1;
    float PV_npvsGood_smr3;

    unsigned long long fEvent;
    int fLumiBlock;
    int fRun;
    int fBx;
    int fOrbit;

    
    // int numCandidates; //number of particles
    // std::vector<float> packed_pt; // transverse momentum
    // std::vector<float> packed_eta; 
    // std::vector<float> packed_mass; // mass of the particle
    // std::vector<float> packed_energy;
    // std::vector<float> packed_phi; // momentum azimuthal angle
    // std::vector<float> packed_ch; // charge of particle
    // std::vector<float> packed_px; // x component of momentum
    // std::vector<float> packed_py; // y component of momentum
    // std::vector<float> packed_pz; // z component of momentum
    // std::vector<float> packed_theta; // polar angle momentum
    // std::vector<float> packed_vx; // x coordinate of vertex position
    // std::vector<float> packed_vy; // y coordinate of vertex position
    // std::vector<float> packed_vz; // z coordinate of vertex position
    // std::vector<float> packed_lostInnerHits;
    // std::vector<float> packed_PuppiWeight;
    // std::vector<float> packed_PuppiWeightNoLep;
    // std::vector<float> packed_hcalFraction;
    // std::vector<int> packed_pdgId;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

/*
vector<l1extra::L1EmParticle>         "l1extraParticles"          "Isolated"        "RECO"    
vector<l1extra::L1EmParticle>         "l1extraParticles"          "NonIsolated"     "RECO"    
vector<l1extra::L1EtMissParticle>     "l1extraParticles"          "MET"             "RECO"    
vector<l1extra::L1EtMissParticle>     "l1extraParticles"          "MHT"             "RECO"    
vector<l1extra::L1HFRings>            "l1extraParticles"          ""                "RECO"    
vector<l1extra::L1JetParticle>        "l1extraParticles"          "Central"         "RECO"    
vector<l1extra::L1JetParticle>        "l1extraParticles"          "Forward"         "RECO"    
vector<l1extra::L1JetParticle>        "l1extraParticles"          "IsoTau"          "RECO"    
vector<l1extra::L1JetParticle>        "l1extraParticles"          "Tau"             "RECO"    
vector<l1extra::L1MuonParticle>       "l1extraParticles"          ""                "RECO" 
 */

L1TriggerAnalyzer::L1TriggerAnalyzer(const edm::ParameterSet& iConfig):
    isData(iConfig.getParameter<bool>("isData")),
    centralJetToken_(consumes <vector<l1extra::L1JetParticle> > ( edm::InputTag("l1extraParticles","Central") )),
    // forwardJetToken_(consumes <vector<l1extra::L1JetParticle> > ( edm::InputTag("l1extraParticles","Forward") )),
    // isoTauToken_(consumes <vector<l1extra::L1JetParticle> > ( edm::InputTag("l1extraParticles","IsoTau") )),
    // tauToken_(consumes <vector<l1extra::L1JetParticle> > ( edm::InputTag("l1extraParticles","Tau") )),
    vtxToken_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"))),
    beamToken_(consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("beams"))),
    caloStage2DigisToken_(consumes<BXVector<l1t::Jet> >( edm::InputTag("caloStage2Digis","Jet") )),
    rhoToken_(consumes<double> (edm::InputTag("fixedGridRhoFastjetAll") ))
    // jetToken_(consumes <vector<l1extra::L1JetParticle> > ( "l1extraParticles","Central" ))
    // edm::EDGetTokenT<BXVector<l1t::Jet> > caloStage2DigisToken_;
    //jetToken_(consumes <vector<l1extra::L1JetParticle> > (iConfig.getParameter<edm::InputTag>("jet")))
{
   //now do what ever initialization is needed
    //usesResource("TFileService");

    //edm::Service<TFileService> fs;
    mfile = new TFile("ntuple.root","recreate");
    //mtree = fs->make<TTree>("Events", "Events");
    mtree = new TTree("Events", "Events");
    mtree->SetDirectory(mfile);
   rand = new TRandom3(2024);

   mtree->Branch("jet_pt",&jet_pt);
   mtree->Branch("jet_ptSub",&jet_ptSub);
   mtree->Branch("jet_eta",&jet_eta);
   mtree->Branch("jet_phi",&jet_phi);
   // mtree->Branch("fwdjet_pt",&fwdjet_pt);
   // mtree->Branch("isotau_pt",&isotau_pt);
   // mtree->Branch("tau_pt",&tau_pt);
   mtree->Branch("ht",&ht);
   mtree->Branch("htSub",&htSub);

   mtree->Branch("PV_npvs",&PV_npvs);
   mtree->Branch("PV_npvs_smr1",&PV_npvs_smr1);
   mtree->Branch("PV_npvs_smr3",&PV_npvs_smr3);
   mtree->Branch("PV_npvsGood",&PV_npvsGood);
   mtree->Branch("PV_npvsGood_smr1",&PV_npvsGood_smr1);
   mtree->Branch("PV_npvsGood_smr3",&PV_npvsGood_smr3);

   if(isData){
       mtree->Branch("evt",&fEvent);
       mtree->Branch("lumiBlock",&fLumiBlock);
       mtree->Branch("run",&fRun);
       mtree->Branch("bx",&fBx);
       mtree->Branch("orbit",&fOrbit);
   }

   // mtree->Branch("numCandidates",&numCandidates);
   // mtree->GetBranch("numCandidates")->SetTitle("number of packed particles");
   // mtree->Branch("packed_pt",&packed_pt);
   // mtree->GetBranch("packed_pt")->SetTitle("the flowing particle's transverse momentum");
   // mtree->Branch("packed_eta",&packed_eta);
   // mtree->GetBranch("packed_eta")->SetTitle("generator particle pseudorapidity");
   // mtree->Branch("packed_mass",&packed_mass);
   // mtree->GetBranch("packed_mass")->SetTitle("packed candidate mass");
   // mtree->Branch("packed_energy",&packed_energy);
   // mtree->GetBranch("packed_energy")->SetTitle("packed candidate energy");
   // mtree->Branch("packed_ch",&packed_ch);
   // mtree->GetBranch("packed_ch")->SetTitle("charge of the particle");
   // mtree->Branch("packed_phi",&packed_phi);
   // mtree->GetBranch("packed_phi")->SetTitle("packed candidate azimuthal angle of momentum vector");
   // mtree->Branch("packed_px",&packed_px);
   // mtree->GetBranch("packed_px")->SetTitle("packed candidate x coordinate of momentum vector");
   // mtree->Branch("packed_py",&packed_py);
   // mtree->GetBranch("packed_py")->SetTitle("packed candidate y coordinate of momentum vector");
   // mtree->Branch("packed_pz",&packed_pz);
   // mtree->GetBranch("packed_pz")->SetTitle("packed candidate z coordinate of momentum vector");
   // mtree->Branch("packed_theta", &packed_theta);
   // mtree->GetBranch("packed_theta")->SetTitle("polar angle of momentum");
   // mtree->Branch("packed_vx",&packed_vx);
   // mtree->GetBranch("packed_vx")->SetTitle("x of the vertex");
   // mtree->Branch("packed_vy",&packed_vy);
   // mtree->GetBranch("packed_vy")->SetTitle("y of the vertex");
   // mtree->Branch("packed_vz",&packed_vz);
   // mtree->GetBranch("packed_vz")->SetTitle("z of the vertex");
   // mtree->Branch("packed_lostInnerHits",&packed_lostInnerHits);
   // mtree->GetBranch("packed_lostInnerHits")->SetTitle("Inner hit information");
   // mtree->Branch("packed_PuppiWeight",&packed_PuppiWeight);
   // mtree->GetBranch("packed_PuppiWeight")->SetTitle("Puppi Weight");
   // mtree->Branch("packed_PuppiWeightNoLep",&packed_PuppiWeightNoLep);
   // mtree->GetBranch("packed_PuppiWeightNoLep")->SetTitle("Puppi MET");
   // mtree->Branch("packed_hcalFraction",&packed_hcalFraction);
   // mtree->GetBranch("packed_hcalFraction")->SetTitle("Energy Measured from Hadronic Calorimeter");
   // mtree->Branch("packed_pdgId",&packed_pdgId);
   // mtree->GetBranch("packed_pdgId")->SetTitle("PDG ID of particle-- 11,13,22 - ele/mu/gamma, 211-charged hadrons, 130-neutral hadrons, 1&2-hadronic and em particles in HF");
}


L1TriggerAnalyzer::~L1TriggerAnalyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
    mfile->cd();
    mtree->Write();
    mfile->Close();
    delete rand;
}


//
// member functions
//

// ------------ method called for each event  ------------
void
L1TriggerAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   
   Handle<vector<l1extra::L1JetParticle> > jets;
   iEvent.getByToken(centralJetToken_,jets);

   Handle<BXVector<l1t::Jet> > hwJets;
   iEvent.getByToken(caloStage2DigisToken_,hwJets);
   Handle<double> rho;
   iEvent.getByToken(rhoToken_,rho);

   //std::cout << (*rho) << std::endl;
   //std::cout << (*hwJets).size() << std::endl;
   // Handle<vector<l1extra::L1JetParticle> > fwdjets;
   // iEvent.getByToken(forwardJetToken_,fwdjets);
   // Handle<vector<l1extra::L1JetParticle> > isotaus;
   // iEvent.getByToken(isoTauToken_,isotaus);
   // Handle<vector<l1extra::L1JetParticle> > taus;
   // iEvent.getByToken(tauToken_,taus);

   jet_pt.clear();
   jet_ptSub.clear();
   jet_eta.clear();
   jet_phi.clear();
   // fwdjet_pt.clear();
   // isotau_pt.clear();
   // tau_pt.clear();
   ht=0;
   htSub=0;
   PV_npvs=0;
   PV_npvs_smr1=0;
   PV_npvs_smr3=0;
   PV_npvsGood=0;
   PV_npvsGood_smr1=0;
   PV_npvsGood_smr3=0;
      
   // for (const l1extra::L1JetParticle &jet : *jets){
   //     jet_pt.push_back(jet.pt());
   //     jet_eta.push_back(jet.eta());
   //     jet_phi.push_back(jet.phi());
   //     ht += jet.pt();
   // }
   for (const l1t::Jet &jet : *hwJets){
       jet_pt.push_back(jet.hwPt()*0.5); // jetLSB = 0.5 GeV 
       jet_ptSub.push_back(max(0.,jet.hwPt()*0.5 - (*rho)*M_PI*0.4*0.4));
       jet_eta.push_back(jet.hwEta() * 2*M_PI/144); // 0-144
       jet_phi.push_back(jet.hwPhi() * 2*M_PI/144);
       ht += jet_pt.back();
       htSub += jet_ptSub.back();
   }

   // for (const l1extra::L1JetParticle &jet : *fwdjets){
   //     fwdjet_pt.push_back(jet.pt());
   // } 
   // for (const l1extra::L1JetParticle &tau : *taus){
   //     tau_pt.push_back(tau.pt());
   // } 
   // for (const l1extra::L1JetParticle &tau : *isotaus){
   //     isotau_pt.push_back(tau.pt());
   // } 
   // get vertex info
   
   Handle<reco::VertexCollection> vertices;
   iEvent.getByToken(vtxToken_, vertices);
   if (vertices->empty()) return; // skip the event if no PV found
    
   Handle<reco::BeamSpot> beamSpotHandle;
   iEvent.getByToken(beamToken_, beamSpotHandle);
   reco::BeamSpot vertexBeamSpot= *beamSpotHandle;
   
   for (const reco::Vertex &vtx : *vertices){
       PV_npvs++;
       if (!vtx.isFake() && vtx.isValid() && vtx.ndof()>4 && fabs(vtx.z()-vertexBeamSpot.z0())<24. && vtx.position().Rho() < 2.)
           PV_npvsGood++;
   } 

   PV_npvs_smr1 = rand->Gaus(PV_npvs,1);
   PV_npvs_smr3 = rand->Gaus(PV_npvs,3);
   PV_npvsGood_smr1 = rand->Gaus(PV_npvsGood,1);
   PV_npvsGood_smr3 = rand->Gaus(PV_npvsGood,3);

   // event info
   if(isData){
       fEvent = iEvent.id().event();
       fLumiBlock = iEvent.luminosityBlock();
       fRun = iEvent.id().run();
       fBx = iEvent.bunchCrossing();
       fOrbit = iEvent.orbitNumber();
   }
   //  std::cout << iEvent.id().event() << std::endl;
   
   mtree->Fill();
   return;      
          
 
}


// ------------ method called once each job just before starting event loop  ------------
void
L1TriggerAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
L1TriggerAnalyzer::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
L1TriggerAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

}

//define this as a plug-in
DEFINE_FWK_MODULE(L1TriggerAnalyzer);
