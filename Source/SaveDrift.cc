#include <iostream>

#include "SaveDrift.hh"

namespace Garfield {

SaveDrift::SaveDrift(TString outputFilePath) : m_className("SaveDrift"), m_debug(false) {
  outputFile = new TFile(outputFilePath ,"RECREATE");
  outputFile->cd();
  outputTree = new TTree("driftLineTree", "DriftLines");
  outputTree->Branch("x_e", &x_e);
  outputTree->Branch("y_e", &y_e);
  outputTree->Branch("z_e", &z_e);
  outputTree->Branch("t_e", &t_e);
  outputTree->Branch("x_p", &x_p);
  outputTree->Branch("y_p", &y_p);
  outputTree->Branch("z_p", &z_p);
  outputTree->Branch("t_p", &t_p);

  e_driftLine_id = 0;
}

SaveDrift::~SaveDrift() {
  outputFile->cd();
  outputFile->Write();
  outputFile->Close();
  Clear();
}

void SaveDrift::Clear() {
  x_e.clear(); y_e.clear(); z_e.clear(); t_e.clear();
  x_p.clear(); y_p.clear(); z_p.clear(); t_p.clear();
}

void SaveDrift::FillEvent() {
  outputTree->Fill();
}

void SaveDrift::NewElectronDriftLine(const unsigned int np, int& id) {
  std::vector<Double_t> line_x(np);
  std::vector<Double_t> line_y(np);
  std::vector<Double_t> line_z(np);
  std::vector<Double_t> line_t(np);

  x_e.push_back(line_x);
  y_e.push_back(line_y);
  z_e.push_back(line_z);
  t_e.push_back(line_t);

  id = e_driftLine_id;
  e_driftLine_id++;
}

void SaveDrift::NewPhotonTrack(const double x0, const double y0, const double z0, const double t0, const double x1, const double y1, const double z1, const double t1) {
  std::vector<Double_t> track_x(2);
  std::vector<Double_t> track_y(2);
  std::vector<Double_t> track_z(2);
  std::vector<Double_t> track_t(2);

  track_x.at(0) = x0; track_x.at(1) = x1;
  track_y.at(0) = y0; track_y.at(1) = y1;
  track_z.at(0) = z0; track_z.at(1) = z1;
  track_t.at(0) = t0; track_t.at(1) = t1;

  x_p.push_back(track_x);
  y_p.push_back(track_y);
  z_p.push_back(track_z);
  t_p.push_back(track_t);
}

void SaveDrift::SetDriftLinePoint(const unsigned int iL, const unsigned int iP, const double x, const double y, const double z, const double t) {
  if (iL >= x_e.size()) {
    std::cerr << m_className << "::SetDriftLinePoint:\n";
    std::cerr << "    Drift line index " << iL << " is out of range.\n";
    return;
  }
  x_e.at(iL).at(iP) = x;
  y_e.at(iL).at(iP) = y;
  z_e.at(iL).at(iP) = z;
  t_e.at(iL).at(iP) = t;
}
}
