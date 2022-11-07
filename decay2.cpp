// standard library header files
#include <iostream>
#include <math.h>

// ROOT header files: random numbers, plotting, file storage
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"

using namespace std;

class particle {
public:
  particle(); // m and p inizialized to zero
  particle(float m, float p); //m mass in MeV, center of mass frame for p
  ~particle() { };

  float m() {return m_;}
  float p() {return p_;}
  

private:
  float m_;
  float p_;
};

particle::particle () {
  m_=0.0;
  p_=0.0;
}
particle::particle (float x, float y) {
  m_ = x;
  p_ = y;
}

double radius(float m1, float m2, float m3) {
    double pcm = sqrt(
		     m1*m1*m1*m1
		     +m2*m2*m2+m2
		     +m3*m3*m3*m3
		     -2*m1*m1*m2*m2
		     -2*m1*m1*m3*m3
		     -2*m2*m2*m3*m3
		     )/2*m1;
    
  return pcm;
  
  };

// For the time being we will not use command line variables
int main(int argc, char* argv[]) {

  // Open TFile for output
  TString rootfname("./output.root");
  // Overwite output file if it already exists
  TFile rfile(rootfname, "RECREATE");
  // Open the ROOT file and make sure the file was opened successfully.
  // Typical cause for failure are: 1) wrong path, 2) no write privilege
  if( !rfile.IsOpen() ) {
    std::cout << "problems creating root file: exiting... " << std::endl;
    exit(-1);
  }
  std::cout << "storing output in root file " << rootfname << std::endl;

  // Start up a new random generator... (we have a new: we will need a delete!)
  TRandom3* gen = new TRandom3();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(0);

    int nbins = 100;
  const int nevents = 10 ;
  double x1=0.9, x2=1.1;
  double resol = 0.01;
  double xlo = x1*(1-5*resol);
  double xhi = x2*(1+5*resol);
  double binwidth = (xhi-xlo) / nbins;
  std::cout << "# bins: " << nbins << "\t bin width: " << binwidth << std::endl;
  // The two histograms instances (name, title, number of bins, range)
  TH1F hx1("hx1", "distribution of true x", nbins, xlo, xhi);
  // The 'd' is for detector 


  




  

  particle bmeson(5279, 0); //center of mass frame
  particle kaon(500, 0); //p is initialized then modified  
  particle pi(140, 0); //p is initialized then modified


  
  
  // float massa_1 = bmeson.m();

  double raggio;
  raggio = radius(bmeson.m(), kaon.m(), pi.m());
  // raggio = radius(10,1,1);
  cout << "pcm is " << raggio << endl;
  // cout << "massa_1 is " << massa_1 << endl;
 double x,y,z = 0;
 double theta, phi = 0;

for(int i=0; i<nevents; ++i) {
 
  
  gen->Sphere(x,y,z,raggio);
  theta = atan(y/x);
  phi = acos(z/raggio);
  cout << i << " - " << theta  << " - " << phi << endl;
 }
 
  
/*  // Fill in histograms
     hx1.Fill(g);
  }

 // After generating the data, we take care of plotting the results
  // * create canvas
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);
  // * start from TRUE values and customize some histogram properties
  hx1.GetXaxis()->SetTitle("X axis");
  // * plot
  hx1.Draw();
  // * store to file in 2 formats
  canv.SaveAs("./x.pdf");
  canv.SaveAs("./x.jpg");


*/

  return 0;

}
