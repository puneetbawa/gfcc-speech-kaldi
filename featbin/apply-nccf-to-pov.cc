// featbin/apply-nccf-to-pov.cc

#include "base/kaldi-common.h"
#include "util/common-utils.h"
#include "matrix/kaldi-matrix.h"
#include "feat/pitch-functions.h"
#include "transform/featxtra-functions.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  try {
    using namespace kaldi;

    const char *usage =
        "Transform raw NCCF to accurate Probability of Voicing (POV).\n"
        "Kaldi pitch extractor (compute-kaldi-pitch) outputs (NCCF, pitch).\n"
        "This program transforms (NCCF, pitch) -> (POV, pitch).\n";

    ParseOptions po(usage);

    po.Read(argc, argv);

    if (po.NumArgs() != 2) {
      po.PrintUsage();
      exit(1);
    }

    kaldi::int32 num_done = 0;
    
    std::string feat_rspecifier = po.GetArg(1);
    std::string feat_wspecifier = po.GetArg(2);

    SequentialBaseFloatMatrixReader feat_reader(feat_rspecifier);
    BaseFloatMatrixWriter feat_writer(feat_wspecifier);
    
    for (;!feat_reader.Done(); feat_reader.Next()) {
      std::string utt = feat_reader.Key();
      Matrix<BaseFloat> feat(feat_reader.Value());
      ApplyNccfToPov(&feat);
      feat_writer.Write(utt, feat);
      num_done++;
    }
    return (num_done != 0 ? 0 : 1);
  } catch(const std::exception &e) {
    std::cerr << e.what();
    return -1;
  }
}
