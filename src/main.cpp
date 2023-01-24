#include <fstream>
#include <string.h>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include <omp.h>

#include "dicom_read/DicomReader.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "second_order/secondorder.h"
#include "performance/benchmark.h"
// #include ""

using namespace std;


int main(int argc, char *argv[])
{
    DicomReader dicomObj("images/MasaMicro1.dcm");
    DicomImage DCM_image("images/MasaMicro1.dcm");

    int depth = DCM_image.getDepth();
    int width = dicomObj.getWidth();
    int height = dicomObj.getHeight();
    cout << "Filas: " << height << endl;
    cout << "Columnas: " << width << endl;
    cout << "Profundidad de la imagen: " << depth << endl;
    vector<vector<int>> arr = dicomObj.getIntImageMatrix(depth);


    SecondOrder s;
    systemMetrics systemMetrics("secondorder");
    systemMetrics.resetCounters();

    // double idnP = s.IDN_OPM(arr);
    // cout << "IDN using OPM: " << idnP << endl;
    double idn = s.IDN(arr);
    cout << "IDN: " << idn << endl;

    // double ido_c4P = s.IDOC4_OPM(arr);
    // cout << "IDOC4 using OPM: " << ido_c4P << endl;
    double ido_c4 = s.IDOC4(arr);
    cout << "IDOC4: " << ido_c4 << endl;

    // double inverse_varianceP = s.InverseVariance_OPM(arr);
    // cout << "InverseVariance using OPM: " << inverse_varianceP << endl;
    double inverse_variance = s.InverseVariance(arr);
    cout << "InverseVariance: " << inverse_variance << endl;

    // double local_homogeneityP = s.LocalHomogeneity_OPM(arr);
    // cout << "LocalHomogeneity using OPM: " << local_homogeneityP << endl;
    double local_homogeneity = s.LocalHomogeneity(arr);
    cout << "LocalHomogeneity: " << local_homogeneity << endl;

    // double max_probabilityP = s.MaxProbability_OPM(arr);
    // cout << "MaxProbability using OPM: " << max_probabilityP << endl;
    double max_probability = s.MaxProbability(arr);
    cout << "MaxProbability: " << max_probability << endl;

    // double max_intensityroiP = s.MaxIntensityROI_OPM(arr, 1000, 1000, 2000, 2000);
    // cout << "MaxIntensityROI using OPM: " << max_intensityroiP << endl;
    double max_intensityroi = s.MaxIntensityROI(arr, 1000, 1000, 2000, 2000);
    cout << "MaxIntensityROI: " << max_intensityroi << endl;

    // int mean_intensityroiP = s.MeanIntensityROI_OPM(arr, 1000, 1000, 2000, 2000);
    // cout << "MeanIntensityROI using OPM: " << mean_intensityroiP << endl;
    double mean_intensityroi = s.MeanIntensityROI(arr, 1000, 1000, 2000, 2000);
    cout << "MeanIntensityROI: " << mean_intensityroi << endl;

    // double lreP = s.LRE_ORM(arr);
    // cout << "LRE using OPM: " << lreP << endl;
    double lre = s.LRE(arr);
    cout << "LRE: " << lre << endl;

    // double mean_varianceP = s.MeanVariance_OPM(arr);
    // cout << "MeanVariance using OPM: " << mean_varianceP << endl;
    double mean_variance = s.MeanVariance(arr);
    cout << "MeanVariance: " << mean_variance << endl;

    systemMetrics.calculate();
    systemMetrics.printMetrics();
    // Imprimimos las metricas
    cout << "RAM: " << getRamUsage() << "kb" << endl;
    return 0;
}