/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once
#include <cstdint>
#include "fbgemm/Fbgemm.h"
#include "GenerateKernel.h"

namespace fbgemm {

/**
 * @brief Execute Engine for the macro-kernel and output processing.
 * ExecuteKernel is a derived class of CodeGenBase.
 */
template <
    typename packingAMatrix,
    typename packingBMatrix,
    typename cT,
    typename processOutputType>
class ExecuteKernel : public CodeGenBase<
                          typename packingAMatrix::inpType,
                          typename packingBMatrix::inpType,
                          cT,
                          typename packingBMatrix::accType> {
 public:
  ExecuteKernel(
      PackMatrix<
          packingAMatrix,
          typename packingAMatrix::inpType,
          typename packingAMatrix::accType>& packA,
      PackMatrix<
          packingBMatrix,
          typename packingBMatrix::inpType,
          typename packingBMatrix::accType>& packB,
      int32_t kBlock,
      cT* matC,
      typename packingBMatrix::accType* C_buffer,
      int32_t ldc,
      const processOutputType& outputProcess);
  void execute(int kBlock);

 private:
  PackMatrix<
      packingAMatrix,
      typename packingAMatrix::inpType,
      typename packingAMatrix::accType>&
      packedA_; ///< Packed block of matrix A.
  PackMatrix<
      packingBMatrix,
      typename packingBMatrix::inpType,
      typename packingBMatrix::accType>& packedB_; ///< Packed matrix B.
  int32_t kBlock_; ///< Block ID in the k dimension.
  cT* matC_; ///< Output for matrix C.
  typename packingAMatrix::accType*
      C_buffer_; ///< the accumulation buffer for matrix C.
  int32_t ldc_; ///< the leading dimension of matrix C.
  const processOutputType& outputProcess_; ///< output processing function for
                                           ///< the C tile in the macro-kernel.
};

} // namespace fbgemm
