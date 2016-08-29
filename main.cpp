#include <iostream>
#include <iomanip>
#include "arr.hpp"

int main(int argc, char **argv){
  std::string operation;
  for(int i=0;i<argc;i++)
    operation+=argv[i]+std::string(" ");

  if(argc!=2 && argc!=4){
    std::cerr<<"Syntax: "<<argv[0]<<" <File Geodatabase> [Raster] <Output Name>"<<std::endl;
    return -1;
  }

  std::string basename = argv[1];

  MasterTable mt(basename+"a00000001.gdbtable");

  if(argc==2){
    std::cout<<"Rasters found: \n";
    for(unsigned int r=0;r<mt.rasters.size();r++)
      std::cout<<std::setw(2)<<r<<" "<<mt.rasters[r].first<<" ("<<std::hex<<std::setw(3)<<mt.rasters[r].second<<std::dec<<")\n";
    if(mt.rasters.size()==0){
      std::cout<<"\tNo rasters found!"<<std::endl;
    }
  } else if(argc==4){
    unsigned int raster_num = std::stoi(argv[2]);
    if(mt.rasters.size()==0){
      std::cerr<<"No rasters found!"<<std::endl;
      return -1;
    }
    if(raster_num>=mt.rasters.size()){ //Note: Don't need <0 check because raster_num is unsigned
      std::cerr<<"Invalid raster number! Must be 0-"<<(mt.rasters.size()-1)<<"."<<std::endl;
      return -1;
    }

    ExportRasterToGeoTIFF(operation, basename, mt.rasters.at(raster_num).second, std::string(argv[3]));
  }

  return 0;
}