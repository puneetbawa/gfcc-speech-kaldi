// feat/feature-dctf.cc

#include "feat/feature-dctf.h"
#include "feat/feature-window.h"

namespace kaldi {

Dctf::Dctf(const DctfOptions &opts)
    : opts_(opts), feature_window_function_(opts.frame_opts) {
  int32 num_bins = opts.num_bins;
  int32 num_ceps = opts.num_ceps;
  Matrix<BaseFloat> dct_matrix(num_bins, num_bins);
  ComputeDctMatrix(&dct_matrix);
  // Note that we include zeroth dct in either case.  If using the
  // energy we replace this with the energy.  This means a different
  // ordering of features than HTK.
  SubMatrix<BaseFloat> dct_rows(dct_matrix, 0, num_ceps, 0, num_bins);
  dct_matrix_.Resize(num_ceps, num_bins);
  dct_matrix_.CopyFromMat(dct_rows);  // subset of rows.

}

Dctf::~Dctf() {
}

void Dctf::Compute(const VectorBase<BaseFloat> &wave,
                   Matrix<BaseFloat> *output,
                   Vector<BaseFloat> *wave_remainder) {
  assert(output != NULL);
  int32 rows_out = NumFrames(wave.Dim(), opts_.frame_opts);
  int32 cols_out = opts_.num_ceps;
  if (rows_out == 0)
    KALDI_ERR << "Dctf::Compute, no frames fit in file (#samples is " << wave.Dim() << ")";
  output->Resize(rows_out, cols_out);
  if (wave_remainder != NULL)
    ExtractWaveformRemainder(wave, opts_.frame_opts, wave_remainder);
  Vector<BaseFloat> window;  // windowed waveform.
  for (int32 r = 0; r < rows_out; r++) {  // r is frame index..
    ExtractWindow(0, wave, r, opts_.frame_opts, feature_window_function_, &window, NULL);

    SubVector<BaseFloat> this_dctf(output->Row(r));

    // DCTF
    this_dctf.AddMatVec(1.0, dct_matrix_, kNoTrans, window, 0.0);
  }
}
}  // namespace
