#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include "EventLoop/OutputStream.h"
#include <MyA/MyxAODAnalysis.h>

#include <TFile.h>

#include "xAODEventInfo/EventInfo.h"
#include "xAODJet/JetContainer.h"
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODEgamma/Photon.h"
#include <AsgTools/MessageCheck.h>

// this is needed to distribute the algorithm to the workers
ClassImp(MyxAODAnalysis)

#define ARRAY_INIT {}

MyxAODAnalysis :: MyxAODAnalysis () :
    m_tree(new TTree("tree", "output tree")),
    m_eventnumber(-999.0),
    m_eventweight(-999.0),
    m_NTruthPhotons(-1),
    m_NTruthJets(-1),

    m_j0pt{ARRAY_INIT},
    m_j0eta{ARRAY_INIT},
    m_j0phi{ARRAY_INIT},
    m_j0m{ARRAY_INIT},
    m_j0id{ARRAY_INIT},

    m_gammapt{ARRAY_INIT},
    m_gammaeta{ARRAY_INIT},
    m_gammaphi{ARRAY_INIT},
    m_gammam{ARRAY_INIT}
{
}



EL::StatusCode MyxAODAnalysis :: setupJob (EL::Job& job)
{
  job.useXAOD ();
  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)

  xAOD::Init("MyxAODAnalysis").ignore(); // call before opening first file
  /* https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/EventLoop#Creating_output_n_tuples */
  // output file for tree
  EL::OutputStream out ("outputTree");
  job.outputAdd (out);

  ANA_CHECK(xAOD::Init());
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: histInitialize ()
{
  //h_jetncharged = new TH1F("h_jetncharged", "h_jetncharged", 100, 0, 100); // jet pt [GeV]
  //wk()->addOutput (h_jetncharged);

  // get the output file, create a new TTree and connect it to that output
  // define what braches will go in that tree

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: initialize ()
{
  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)

  m_event = wk()->xaodEvent();

  TFile *outputFile = wk()->getOutputFile ("outputTree");
  //tree = new TTree ("tree", "tree");
  m_tree->SetDirectory (outputFile);

  m_tree->Branch("EventNumber", &m_eventnumber);
  m_tree->Branch("EventWeight", &m_eventweight);
  m_tree->Branch("NTruthPhotons", &m_NTruthPhotons);
  m_tree->Branch("NTruthJets", &m_NTruthJets);

  m_tree->Branch("j0pt", &m_j0pt);
  m_tree->Branch("j0eta", &m_j0eta);
  m_tree->Branch("j0phi", &m_j0phi);
  m_tree->Branch("j0m", &m_j0m);
  m_tree->Branch("j0id", &m_j0id);

  m_tree->Branch("gammapt", &m_gammapt);
  m_tree->Branch("gammaeta", &m_gammaeta);
  m_tree->Branch("gammaphi", &m_gammaphi);
  m_tree->Branch("gammam", &m_gammam);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)


  const xAOD::EventInfo* eventInfo = 0;
  ANA_CHECK(m_event->retrieve( eventInfo, "EventInfo") );
  m_eventnumber = eventInfo->eventNumber();
  m_eventweight = eventInfo->mcEventWeight();

  //const xAOD::TruthEventContainer* xTruthEventContainer = NULL;
  //ANA_CHECK( m_event->retrieve( xTruthEventContainer, "TruthEvents"));
  //Info("execute()","******* TruthEvents size %lu", xTruthEventContainer->size());
  //xAOD::TruthEventContainer::const_iterator truth_event = xTruthEventContainer->begin();
  
  float min_photon_pt = 5000;
  // get photons
  const DataVector<xAOD::TruthParticle_v1>* photons (nullptr);
  ANA_CHECK(m_event->retrieve( photons, "Truth3Photons" ));
  //Info("execute()", "  number of photons = %lu", photons->size());
  //m_NTruthPhotons = photons->size();
  m_NTruthPhotons = 2;
  m_gammapt.clear();
  m_gammaeta.clear();
  m_gammaphi.clear();
  m_gammam.clear();
  std::vector<TLorentzVector> gamp4;
  for(const auto photon : *photons){
    if(photon->pt()<min_photon_pt) continue;
    m_gammapt.push_back(photon->pt()/1000.);
    m_gammaeta.push_back(photon->eta());
    m_gammaphi.push_back(photon->phi());
    m_gammam.push_back(photon->m()/1000.);
    gamp4.push_back(photon->p4());
  }

  // get jet container of interest
  // 
  float min_jet_pt = 10000;
  const xAOD::JetContainer* jets (nullptr);
  ANA_CHECK(m_event->retrieve( jets, "AntiKt4TruthJets" ));
  // Info("execute()", "  number of jets = %lu", jets->size());
  m_NTruthJets = jets->size();

  // loop over the jets in the container
  xAOD::JetContainer::const_iterator jet_itr = jets->begin();
  xAOD::JetContainer::const_iterator jet_end = jets->end();
  //for( ; jet_itr != jet_end; ++jet_itr ) {
  m_j0pt.clear();
  m_j0eta.clear();
  m_j0phi.clear();
  m_j0m.clear();
  m_j0id.clear();
  for(const auto jet : *jets){
    if(jet->pt()<min_jet_pt) continue;
    TLorentzVector jetp4 = jet->p4();
    bool isPhoton=false;
    for(int i=0; i<gamp4.size(); i++){
      if(m_gammapt[i]*1000.<min_photon_pt) continue;
      float dR = jetp4.DeltaR(gamp4[i]); 
      if(dR<0.4){
        isPhoton=true;
        break;
      }
    }
    int id;
    jet->getAttribute("PartonTruthLabelID",id);
    //std::cout << isPhoton << ";" << id << std::endl;
    if(isPhoton) m_j0id.push_back(22); //pdgID of photon
    else m_j0id.push_back(id); //could be anything

    m_j0pt.push_back(jet->pt()/1000.);
    m_j0eta.push_back(jet->eta());
    m_j0phi.push_back(jet->phi());
    m_j0m.push_back(jet->m()/1000.);

    // for (size_t ind = 0; ind < (*jet_itr)->numConstituents(); ind++) {
    //   const xAOD::TruthParticle *part = static_cast<const xAOD::TruthParticle*>((*jet_itr)->rawConstituent(ind));
    //   if (!part) continue;
    //   if( ! (part->status() == 1) )                continue; // final state
    //   if( ! (part->isCharged()) )                  continue; // charged
    //   if( ! (part->pt()>50.) )                     continue; //pt>0 MeV
    //   // if( ! (part->p4().DeltaR((*jet_itr)->p4()) < 0.4) ) continue; // inside of jet
    //   ncharged++; //count this particle
    // }
  } // end for loop over jets

  /*for(int iPart=0; iPart<(*truth_event)->nTruthParticles(); ++iPart){
    const xAOD::TruthParticle* pitr = (*truth_event)->truthParticle(iPart);
    if( !pitr) continue;
    if( ! (pitr->status() == 1) )                continue; // final state
    //if( ! (pitr->isCharged()) )                  continue; // charged
    if( ! (pitr->pt()>50.) )                    continue; //pt>0 MeV
    //if( ! (pitr->p4().DeltaR((*jet_itr)->p4()) < 0.4) ) continue; // inside of jet
    if ((pitr->barcode())>2e5) continue;
    std::cout << pitr->pdgId() << std::endl;
    //ncharged++; //count this particle
  }*/

  m_tree->Fill();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.
  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.
  return EL::StatusCode::SUCCESS;
}
