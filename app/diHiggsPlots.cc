#include <iostream>
#include <fstream>
#include <string>
//ROOT
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include <TROOT.h>
//LOCAL
#include <hh_tree.hh>
#include <CommandLineInput.hh>


#define _info  1
#define _debug 1

int main(int argc, char** argv)
{
  //Get input file from command line
  // if not present program will quit
  std::string input_list = ParseCommandLine( argc, argv, "input_list");
  if( input_list == "" || input_list == "not-found" )
    {
      std::cerr << "[ERROR]: Provide an input list using --input_list=<your_input_list>.\nExiting programs!!" << std::endl;
      return -1;
    }

  //Get output file from command line
  // if not present program will quit
  std::string output_file = ParseCommandLine( argc, argv, "output_file");
  if( output_file == "" || output_file == "not-found" )
    {
      std::cerr << "[ERROR]: Provide an input list using --output_file=<your_output_file>.\nExiting programs!!" << std::endl;
      return -1;
    }

  std::string data_str = ParseCommandLine( argc, argv, "is_data");
  bool _is_data = false;
  if( data_str != "not-found" )
    {
      _is_data = true;
    }
  

  if( _info ) std::cout << "[INFO] input list       -> " << input_list << std::endl;
  if( _info ) std::cout << "[INFO] output file      -> " << output_file << std::endl;
  if( _info )
    {
      if( _is_data ) std::cout << "[INFO] running on data? -> YES" << std::endl;
      else std::cout << "[INFO] running on data? -> NO" << std::endl;
    }

  TFile* fdummy = new TFile("dummy.root", "recreate");
  //----------------------
  //define main TChain
  //----------------------
  TChain* chain = new TChain("hh");

  //-----------------------------------------------
  //Start reading input list and concatenate TChain
  //-----------------------------------------------
  std::ifstream ifs (input_list.c_str(), std::ifstream::in);
  std::string current_file_name;
  while( ifs.good() )
    {
      ifs >> current_file_name;
      if(ifs.eof()) break;//exit if end of file is reached
      
      if( _debug ) std::cout << "[DEBUG]: " << current_file_name << std::endl;
      chain->Add( current_file_name.c_str() );//concatenate all input file into the TChain
    }


  TChain* cut_chain = new TChain();
  //cut_chain = (TChain*)chain->CopyTree("(FatJet_btagDDBvL[0]>0.8 && FatJet_btagDDBvL[1]>0.8 && FatJet_pt[0]>300. && FatJet_pt[1]>300. && FatJet_msoftdrop[1]>100. && FatJet_msoftdrop[1]<160. && FatJet_msoftdrop[0]>100. && FatJet_msoftdrop[0]<160.)");
  cut_chain = (TChain*)chain->CopyTree("(FatJet_btagDDBvL[0]>0.8 && FatJet_btagDDBvL[1]>0.8 && FatJet_pt[0]> 300. && FatJet_pt[1] > 300.)");

  //TChain* chain = new TChain("Events");
  //chain->Add("/eos/uscms/store/group/lpcbacon/pancakes/02/2017/UL/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/pancakes-02_RunIISummer19UL17MiniAOD-106X_v6-v2/200127_173532/0000/nano_mc_2017_387.root");

  //SIGNAL
  // chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_1.root");
  // chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_2.root");
  // chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_3.root");
  // chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_4.root");
  // chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_5.root");
  // chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_6.root");
  // chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_7.root");
  // chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_8.root");
  // chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_9.root");
  // chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_10.root");
  // chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_11.root");


  //chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_.root");
  //chain->Add("/mnt/hadoop/store/group/phys_exotica/privateProduction/NANOAOD/v1/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/v1_RunIIAutumn18MiniAOD-102X_v15-v1/200312_210339/0000/RunIIAutumn18NanoAODv5_BulkGravTohhTohWWhbb_.root");

  //------------------------------------------
  //Define main object from Make Class
  //Require a valid TChain called <chain>
  //------------------------------------------
  hh* evt = new hh( cut_chain );
  evt->fout_name = output_file;
  evt->lumi = 42000.0;
  if (_is_data) evt->process = "data";
  else evt->process = "qcd";
  //-----------------------------------------
  //Running main Loop for HH analysis
  //-----------------------------------------
  if( _debug ) std::cout << "[DEBUG] Beginning Main Loop" << std::endl;
  evt->Loop();
  if( _debug ) std::cout << "[DEBUG] Finished Main Loop" << std::endl;
  
  delete fdummy;
  return 0;
}
