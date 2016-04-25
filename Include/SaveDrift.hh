#ifndef G_SAVE_DRIFT
#define G_SAVE_DRIFT

#include <string>
#include <TFile.h>
#include <TTree.h>

namespace Garfield {

class SaveDrift {

 public:
  // Constructor
  SaveDrift();
  // Destructor
  ~SaveDrift();

  void Clear();
  void FillEvent();

  // Functions to be used by transport classes.
  void NewElectronDriftLine(const unsigned int np, int& id, const double x0, const double y0, const double z0, const double t0);
  void NewPhotonTrack(const double x0, const double y0, const double z0, const double t0, const double x1, const double y1, const double z1, const double t1);

  void SetDriftLinePoint(const unsigned int iL, const unsigned int iP, const double x, const double y, const double z, const double t);

  void EnableDebugging() { m_debug = true; }
  void DisableDebugging() { m_debug = false; }

  friend class ViewFEMesh;

 private:
  std::string m_className;

  // Options
  bool m_debug;

  TFile* outputFile;
  TTree* outputTree;

  Int_t e_driftLine_id;

  vector< vector<Double_t> > x_e;
  vector< vector<Double_t> > y_e;
  vector< vector<Double_t> > z_e;
  vector< vector<Double_t> > x_p;
  vector< vector<Double_t> > y_p;
  vector< vector<Double_t> > z_p;
};
}
#endif
