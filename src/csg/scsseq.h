#ifndef CSG_SCSSEQ_H
#define CSG_SCSSEQ_H

/** \file
 *  \brief SCS (Sequenced Convex Subtraction) Sequence Generation
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
 *  \author  RMIT School of Computer Science and Information Technology, Australia
 */

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <vector>
#include <iosfwd>
#include <string>

class CsgSumOfProducts;
class CsgProduct;
class CsgOptions;
class CsgInfo;

typedef std::vector<unsigned int> CsgSubtractionSequence;

//
// Sequence Generation
//

/// Generate subtraction sequence, given n and k
CsgSubtractionSequence gscsSequence(const unsigned int n, const unsigned int k);

/// Generate subtraction sequence, given n
CsgSubtractionSequence gscsSequenceAdleman(const unsigned int n);

/// Generate subtraction sequence, given n
CsgSubtractionSequence gscsSequenceGalbiati(const unsigned int n);

/// Generate subtraction sequence, given n and k
CsgSubtractionSequence gscsSequenceSavage(const unsigned int n, const unsigned int k);

/// Generate subtraction sequence, using adjacency graph
CsgSubtractionSequence gscsSequence
(
    const CsgProduct &prod,
    const CsgOptions &options,
          CsgInfo    &info
);

/// Remap sequence
bool gscsRemapSequence(CsgSubtractionSequence &sequence,const std::vector<unsigned int> &remap);
/// Remap sequence
bool gscsRemapSequence(CsgSubtractionSequence &sequence,const CsgProduct &product);
/// Normalise sequence
bool gscsNormalise(CsgSubtractionSequence &sequence);

/// Optimise sequence
CsgSubtractionSequence gscsSequenceOptimise(const CsgSubtractionSequence &sequence);

/// Write sequence to string
std::string seqenceString(const CsgSubtractionSequence &seq,const CsgProduct &prod);
std::string seqenceString(const CsgSubtractionSequence &seq);

#endif

