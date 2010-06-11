/** \file
 * Determine the required SCS subtraction length
 *
 * Accepts a filename on the command line, or
 * simply '-' to read from standard input.
 *
 * http://www.nigels.com/research/
 *
 * \author  Nigel Stewart (nigels@nigels.com)
 * \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
 *
 * \todo    Core dumps on Linux - fix?
 */

#include <csg/model.h>
#include <csg/element.h>
#include <csg/normalise.h>

#include <csg/bbox.h>

#include <csg/scs.h>
#include <csg/scsseq.h>
#include <csg/options.h>
#include <csg/info.h>

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

int main(int argc,char *argv[])
{
    if (argc!=2)
    {
        cout << endl;
        cout << "SCS Sequence Length" << endl;
        cout << "Nigel Stewart (nigels@nigels.com)" << endl;
        cout << "RMIT Department of Mechanical and Manufacturing Engineering" << endl;
        cout << "18th August 2001" << endl;
        cout << endl;
        cout << "Usage: scsseq [filename]" << endl;
        cout << endl;
        cout << "\t filename is input file, or '-'" << endl;
        cout << endl;

        return EXIT_FAILURE;
    }

    CsgModel model;

    string filename(argv[1]);

    if (filename=="-")
    {
        if (!model.read(cin))
            return EXIT_FAILURE;
    }
    else
    {
        ifstream is(argv[1]);
        if (!model.read(is))
            return EXIT_FAILURE;
    }

    //
    //
    //

    CsgSumOfProducts sum = normalise(model.tree(0));
    sum.optimise();

    for (uint32 i=0; i<sum.size(); i++)
        if (sum[i].size()>1)
        {
            boundingBoxAdjency(sum[i].graph(),sum[i]);
//          boundingBoxAdjencyFast(sum[i].graph(),sum[i]);

            CsgOptions options;
            options.sampleDepthComplexity = false;
            options.overlapGraph = true;

            CsgInfo    info;

#if 0
            cout << gscsSequence(sum[i],options,info).size() << endl;
#else

            // Determine number of subtracted objects in CSG product

            int n=0;
            for (uint32 j=0; j<sum[i].size(); j++)
                if (!sum[i].positive(j))
                    n++;

            // Print out Adleman subtraction sequence

            CsgSubtractionSequence seq1 = gscsSequenceAdleman(n);
            cout << "Adleman:  (" << seq1.size() << ") ";
            cout << ": " << seqenceString(seq1) << endl;

            // Print out Galbiati subtraction sequence

            CsgSubtractionSequence seq2 = gscsSequenceGalbiati(n);
            cout << "Galbiati: (" << seq2.size() << ") ";
            cout << ": " << seqenceString(seq2) << endl;
#endif
        }

    return EXIT_SUCCESS;
}
