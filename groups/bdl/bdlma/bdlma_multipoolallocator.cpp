// bdlma_multipoolallocator.cpp                                       -*-C++-*-
#include <bdlma_multipoolallocator.h>

#include <bsls_ident.h>
BSLS_IDENT_RCSID(bdlma_multipoolallocator_cpp,"$Id$ $CSID$")

#include <bdlma_bufferedsequentialallocator.h>  // for testing only

#include <bsls_performancehint.h>

namespace BloombergLP {
namespace bdlma {

                     // ------------------------
                     // class MultipoolAllocator
                     // ------------------------

// CREATORS
MultipoolAllocator::~MultipoolAllocator()
{
}

// MANIPULATORS
void MultipoolAllocator::reserveCapacity(size_type size, size_type numObjects)
{
    if (BSLS_PERFORMANCEHINT_PREDICT_UNLIKELY(0 == size)) {
        BSLS_PERFORMANCEHINT_UNLIKELY_HINT;
        return;                                                       // RETURN
    }

    d_multipool.reserveCapacity(size, numObjects);
}

}  // close package namespace
}  // close enterprise namespace

// ----------------------------------------------------------------------------
// Copyright 2012 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------
