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
#include "SecondOrder/secondorder.h"
#include "performance/benchmark.h"
// #include ""

using namespace std;


int main(int argc, char *argv[])
{
    DicomReader dicomObj("images/MasaMicro1.dcm");
    DicomImage DCM_image("images/MasaMicro1.dcm");

    int depth = DCM_image.getDepth();
    vector<vector<int>> image = dicomObj.getIntImageMatrix(depth);


    SecondOrder s;
    systemMetrics systemMetrics("SecondOrder");
    systemMetrics.resetCounters();

    double idn = s.IDN_OPM(image);
    // double idn = s.IDN(image);

    double ido_c4 = s.IDOC4_OPM(image);
    // double ido_c4 = s.IDOC4(image);

    double inverse_variance = s.InverseVariance_OPM(image);
    // double inverse_variance = s.InverseVariance(image);

    double local_homogeneity = s.LocalHomogeneity_OPM(image);
    // double local_homogeneity = s.LocalHomogeneity(image);

    double max_probability = s.MaxProbability_OPM(image);
    // double max_probability = s.MaxProbability(image);

    double max_intensityroi = s.MaxIntensityROI_OPM(image, 1000, 1000, 2000, 2000);
    // double max_intensityroi = s.MaxIntensityROI(image, 1000, 1000, 2000, 2000);

    double mean_intensityroi = s.MeanIntensityROI_OPM(image, 1000, 1000, 2000, 2000);
    // double mean_intensityroi = s.MeanIntensityROI(image, 1000, 1000, 2000, 2000);

    double lre = s.LRE_OPM(image);
    // double lre = s.LRE(image);

    double mean_variance = s.MeanVariance_OPM(image);
    // double mean_variance = s.MeanVariance(image);

    systemMetrics.calculate();
    systemMetrics.printMetrics();
    // Imprimimos las metricas
    cout << "RAM: " << getRamUsage() << "kb" << endl;

    printf("\nIDN: %f " , idn );
    printf("\nIDOC4: %f " , ido_c4 );
    printf("\nInverseVariance: %f " , inverse_variance );
    printf("\nLocalHomogeneity: %f " , local_homogeneity );
    printf("\nMaxProbability: %f " , max_probability );
    printf("\nMaxIntensityROI: %f " , max_intensityroi );
    printf("\nMeanIntensityROI: %f " , mean_intensityroi );
    printf("\nLRE: %f " , lre );
    printf("\nMeanVariance: %f \n" , mean_variance );
    return 0;
}