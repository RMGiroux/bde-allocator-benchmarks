// bdldfp_decimal.t.cpp                                               -*-C++-*-
#include <bdldfp_decimal.h>

#include <bslma_testallocator.h>
#include <bslma_defaultallocatorguard.h>

#include <bsl_iostream.h>
#include <bsl_sstream.h>
#include <bsl_cstdlib.h>
#include <bsl_climits.h> // CHAR_BIT
#include <bsl_limits.h>

#include <typeinfo>

using namespace BloombergLP;
using bsl::cout;
using bsl::cerr;
using bsl::flush;
using bsl::endl;
using bsl::atoi;

//=============================================================================
//                                 TEST PLAN
//-----------------------------------------------------------------------------
//                                  Overview
//                                  --------
// The component under test provides a set of value semantic classes which
// represent a floating point numbers in the decimal base, where each class has
// a different precision.
//-----------------------------------------------------------------------------
// CREATORS
//: o 'Decimal_Type32()'
//: o 'Decimal_Type32(DecimalImplUtil::ValueType32)'
//: o 'Decimal_Type32(Decimal64)'
//: o 'Decimal_Type32(float)'
//: o 'Decimal_Type32(double)'
//: o 'Decimal_Type32(long double)'
//: o 'Decimal_Type32(int)'
//: o 'Decimal_Type32(unsigned int)'
//: o 'Decimal_Type32(long int)'
//: o 'Decimal_Type32(unsigned long int)'
//: o 'Decimal_Type32(long long)'
//: o 'Decimal_Type32(unsigned long long)'
//: o 'Decimal_Type64()'
//: o 'Decimal_Type64(DecimalImplUtil::ValueType64)'
//: o 'Decimal_Type64(Decimal32)'
//: o 'Decimal_Type64(Decimal128)'
//: o 'Decimal_Type64(float)'
//: o 'Decimal_Type64(double)'
//: o 'Decimal_Type64(long double)'
//: o 'Decimal_Type64(int)'
//: o 'Decimal_Type64(unsigned int)'
//: o 'Decimal_Type64(long)'
//: o 'Decimal_Type64(unsigned long)'
//: o 'Decimal_Type64(long long)'
//: o 'Decimal_Type64(unsigned long long)'
//: o 'Decimal_Type128()'
//: o 'Decimal_Type128(DecimalImplUtil::ValueType128)'
//: o 'Decimal_Type128(Decimal32)'
//: o 'Decimal_Type128(Decimal64)'
//: o 'Decimal_Type128(float)'
//: o 'Decimal_Type128(double)'
//: o 'Decimal_Type128(long double)'
//: o 'Decimal_Type128(int)'
//: o 'Decimal_Type128(unsigned int)'
//: o 'Decimal_Type128(long)'
//: o 'Decimal_Type128(unsigned long)'
//: o 'Decimal_Type128(long long)'
//: o 'Decimal_Type128(unsigned long long)'
//
// MANIPULATORS
//: o 'operator='
//: o 'operator++'
//: o 'operator--'
//: o 'operator+='
//: o 'operator-='
//: o 'operator*='
//: o 'operator/='
//: o 'data'
//
// ACCESSORS
//: o 'data'
//: o 'value'
//
// FREE OPERATORS
//: o 'operator+' -- Unary
//: o 'operator++'
//: o 'operator--'
//: o 'operator+'
//: o 'operator-'
//: o 'operator*'
//: o 'operator/'
//: o 'operator=='
//: o 'operator!='
//: o 'operator<'
//: o 'operator>'
//: o 'operator<='
//: o 'operator>='
//: o 'operator>> (bsl::basic_istream<CHARTYPE, TRAITS>& stream...'
//: o 'operator>> (bsl::basic_ostream<CHARTYPE, TRAITS>& stream...'
//
//-----------------------------------------------------------------------------
// [ 1] Implementation Assumptions
// [ 2] Decimal32 Type
// [ 3] Decimal64 Type
// [ 4] Decimal128 Type
// [ 5] USAGE EXAMPLES
// ----------------------------------------------------------------------------


//=============================================================================
//                      STANDARD BDE ASSERT TEST MACRO
//-----------------------------------------------------------------------------
static int testStatus = 0;

static void aSsErT(int c, const char *s, int i)
{
    if (c) {
        cout << "Error " << __FILE__ << "(" << i << "): " << s
             << "    (failed)" << endl;
        if (0 <= testStatus && testStatus <= 100) ++testStatus;
    }
}

#define ASSERT(X) { aSsErT(!(X), #X, __LINE__); }

//=============================================================================
//                  STANDARD BDE LOOP-ASSERT TEST MACROS
//-----------------------------------------------------------------------------
#define LOOP_ASSERT(I,X) { \
   if (!(X)) { cout << #I << ": " << I << "\n"; aSsErT(1, #X, __LINE__); }}

#define LOOP2_ASSERT(I,J,X) { \
   if (!(X)) { cout << #I << ": " << I << "\t" << #J << ": " \
              << J << "\n"; aSsErT(1, #X, __LINE__); } }

#define LOOP3_ASSERT(I,J,K,X) { \
   if (!(X)) { cout << #I << ": " << I << "\t" << #J << ": " << J << "\t" \
              << #K << ": " << K << "\n"; aSsErT(1, #X, __LINE__); } }

#define LOOP4_ASSERT(I,J,K,L,X) { \
   if (!(X)) { cout << #I << ": " << I << "\t" << #J << ": " << J << "\t" << \
       #K << ": " << K << "\t" << #L << ": " << L << "\n"; \
       aSsErT(1, #X, __LINE__); } }

#define LOOP5_ASSERT(I,J,K,L,M,X) { \
   if (!(X)) { cout << #I << ": " << I << "\t" << #J << ": " << J << "\t" << \
       #K << ": " << K << "\t" << #L << ": " << L << "\t" << \
       #M << ": " << M << "\n"; \
       aSsErT(1, #X, __LINE__); } }

#define LOOP6_ASSERT(I,J,K,L,M,N,X) { \
   if (!(X)) { cout << #I << ": " << I << "\t" << #J << ": " << J << "\t" << \
       #K << ": " << K << "\t" << #L << ": " << L << "\t" << \
       #M << ": " << M << "\t" << #N << ": " << N << "\n"; \
       aSsErT(1, #X, __LINE__); } }

//=============================================================================
//                  SEMI-STANDARD TEST OUTPUT MACROS
//-----------------------------------------------------------------------------
#define P(X) cout << #X " = " << (X) << endl; // Print identifier and value.
#define Q(X) cout << "<| " #X " |>" << endl;  // Quote identifier literally.
#define P_(X) cout << #X " = " << (X) << ", "<< flush; // P(X) without '\n'
#define L_ __LINE__                           // current Line number
#define T_ cout << "\t" << flush;             // Print tab w/o newline

//=============================================================================
//                  GLOBAL TYPEDEFS/CONSTANTS FOR TESTING
//-----------------------------------------------------------------------------

namespace BDEC = BloombergLP::bdldfp;

//=============================================================================
//                               USAGE EXAMPLE
//-----------------------------------------------------------------------------

namespace UsageExample {
  // TBD
}  // close namespace UsageExample

//=============================================================================
//              GLOBAL HELPER FUNCTIONS AND CLASSES FOR TESTING
//-----------------------------------------------------------------------------

                 // stringstream helpers - not thread safe!

void getStringFromStream(bsl::ostringstream &o, bsl::string  *out)
{
    bslma::TestAllocator osa("osstream");
    bslma::DefaultAllocatorGuard g(&osa);
    *out = o.str();
}

void getStringFromStream(bsl::wostringstream &o, bsl::wstring *out)
{
    bslma::TestAllocator osa("osstream");
    bslma::DefaultAllocatorGuard g(&osa);
    *out = o.str();
}

 // String compare for decimal floating point numbers needs 'e'/'E' conversion

bsl::string& decLower(bsl::string& s)
{
    for (size_t i = 0; i < s.length(); ++i) if ('E' == s[i]) s[i] = 'e';
    return s;
}

bsl::wstring& decLower(bsl::wstring& s)
{
    for (size_t i = 0; i < s.length(); ++i) if (L'E' == s[i]) s[i] = L'e';
    return s;
}

//-----------------------------------------------------------------------------


template <class Expect, class Received>
void checkType(const Received&)
{
    ASSERT(typeid(Expect) == typeid(Received));
}

                          // Stream buffer helpers

template <int Size>
struct BufferBuf : bsl::streambuf {
    BufferBuf() { reset(); }
    const char *str() { *this->pptr() =0; return this->pbase(); }
    void reset() { this->setp(this->d_buf, this->d_buf + Size); }
    char d_buf[Size + 1];
};

struct PtrInputBuf : bsl::streambuf {
    PtrInputBuf(const char *s) {
        char *x = const_cast<char *>(s);
        this->setg(x, x, x + strlen(x));
    }
};

struct NulBuf : bsl::streambuf {
    char d_dummy[64];
    virtual int overflow(int c) {
        setp( d_dummy, d_dummy + sizeof(d_dummy));
        return traits_type::not_eof(c);
    }
};

//=============================================================================
//                              MAIN PROGRAM
//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    int               test = argc > 1 ? atoi(argv[1]) : 0;
    int           verbose1 = argc > 2;
    int           verbose2 = argc > 3;
    int           verbose3 = argc > 4;
    int allocatorVerbosity = argc > 5;  // always the last

    bslma::TestAllocator defaultAllocator("default", allocatorVerbosity);
    bslma::Default::setDefaultAllocator(&defaultAllocator);

    bslma::TestAllocator globalAllocator("global", allocatorVerbosity);
    bslma::Default::setGlobalAllocator(&globalAllocator);

    cout << "TEST " << __FILE__ << " CASE " << test << endl;;

    bslma::TestAllocator  ta(allocatorVerbosity);
    bslma::TestAllocator *pa = &ta;

    cout.precision(35);

    switch (test) { case 0:

    case 5: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLES
        //   Extracted from component header file.
        //
        // Concerns:
        //: 1 The usage example provided in the component header file compiles,
        //:   links, and runs as shown.
        //
        // Plan:
        //: 1 Incorporate usage example from header into test driver, remove
        //:   leading comment characters, and replace 'assert' with 'ASSERT'.
        //:   (C-1)
        //
        // Testing:
        //   USAGE EXAMPLES
        // --------------------------------------------------------------------

        if (verbose1) bsl::cout << "\nTesting Usage Examples"
                                << "\n======================" << bsl::endl;

        if (verbose2) bsl::cout << "\nPortable initialization of non-integer, "
                                   "constant values" << bsl::endl;
        {
            // If your compiler does not support the C Decimal TR, it does not
            // support decimal floating point literals, only binary
            // floating point literals. The problem with binary floating point
            // literals is the same as with binary floating point numbers in
            // general: they cannot represent the decimal numbers we care
            // about.  To solve this problem there are 3 macros provided by
            // this component that can be used to initialize decimal floating
            // point types with non-integer values, precisely.  These macros
            // will evaluate to real, C language literals where those are
            // supported and to a runtime-parsed solution otherwise.  The
            // following code demonstrates the use of these macros as well as
            // mixed-type arithmetics and comparisons:
            //..
            bdldfp::Decimal32  d32( BDLDFP_DECIMAL_DF(0.1));
            bdldfp::Decimal64  d64( BDLDFP_DECIMAL_DD(0.2));
            bdldfp::Decimal128 d128(BDLDFP_DECIMAL_DL(0.3));

            ASSERT(d32 + d64 == d128);
            ASSERT(bdldfp::Decimal64(d32)  * 10 == bdldfp::Decimal64(1));
            ASSERT(d64  * 10 == bdldfp::Decimal64(2));
            ASSERT(d128 * 10 == bdldfp::Decimal128(3));
        }

        if (verbose2) bsl::cout << "\nPrecise calculations with decimal values"
                                << bsl::endl;
        {
            //..
            // Suppose we need to add two (decimal) numbers and then tell if
            // the result is a particular decimal number or not.  That can get
            // difficult with binary floating-point, but easy with decimal:
            //..
            if (std::numeric_limits<double>::radix == 2) {
               ASSERT(.1 + .2 != .3);
            }
            ASSERT(BDLDFP_DECIMAL_DD(0.1) +  BDLDFP_DECIMAL_DD(0.2) ==
                   BDLDFP_DECIMAL_DD(0.3));
            //..
        }
    } break;

    case 4: {
        // --------------------------------------------------------------------
        // TESTING 'Decimal128'
        //   Ensure that 'Decimal128' functions correctly
        //
        // Concerns:
        //: 1 'Decimal128' operations are properly forwarded to implementation
        //: 2 All possible operand combinations work correctly.
        //
        // Plan:
        //: 1 Expected value testing will be used.
        //:
        //: 2 All forms of LHS and RHS combinations for all free operators will
        //:   be tested.
        //:
        //: 3 Every member operator will be tested
        //
        // Testing:
        //   'class Decimal128'
        // --------------------------------------------------------------------

        if (verbose1) bsl::cout << "\nTesting class Decimal128"
                                << "\n========================" << bsl::endl;

        if (verbose2) bsl::cout << "Constructors" << bsl::endl;

        if (verbose3) bsl::cout << "Copy/convert" << bsl::endl;
        {
            const BDEC::Decimal32  c32  = BDEC::Decimal32(32);
            const BDEC::Decimal64  c64  = BDEC::Decimal64(64);
            const BDEC::Decimal128 c128 = BDEC::Decimal128(128);

            ASSERT(BDLDFP_DECIMAL_DL( 32.0) == BDEC::Decimal128(c32));
            ASSERT(BDLDFP_DECIMAL_DL( 64.0) == BDEC::Decimal128(c64));
            ASSERT(BDLDFP_DECIMAL_DL(128.0) == BDEC::Decimal128(c128));
        }

        if (verbose3) bsl::cout << "Integral" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DL(  0.0) == BDEC::Decimal128());  // default
        ASSERT(BDLDFP_DECIMAL_DL(-42.0) == BDEC::Decimal128(-42)); // int
        ASSERT(BDLDFP_DECIMAL_DL( 42.0) == BDEC::Decimal128(42u)); // unsigned
        ASSERT(BDLDFP_DECIMAL_DL(-42.0) == BDEC::Decimal128(-42l)); // long
        ASSERT(BDLDFP_DECIMAL_DL( 42.0) == BDEC::Decimal128(42ul)); // ulong
        ASSERT(BDLDFP_DECIMAL_DL(-42.0) == BDEC::Decimal128(-42ll)); //longlong
        ASSERT(BDLDFP_DECIMAL_DL( 42.0) == BDEC::Decimal128(42ull)); // ulongl

        if (verbose3) bsl::cout << "Binary FP" << bsl::endl;

        // Note that to test binary-float taking constructors I use numbers
        // that can be represented exactly in both binary and decimal FP.

        ASSERT(BDLDFP_DECIMAL_DL(4.25) == BDEC::Decimal128(4.25f)); // float
        ASSERT(BDLDFP_DECIMAL_DL(4.25) == BDEC::Decimal128(4.25)); // double

        if (verbose3) bsl::cout << "Decimal FP" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DL(-42.0) == BDLDFP_DECIMAL_DF(-42.0));
                                                                  // Decimal32
        ASSERT(BDLDFP_DECIMAL_DL(42.0) == BDLDFP_DECIMAL_DF(42.0));
        ASSERT(BDLDFP_DECIMAL_DL(4.2) == BDLDFP_DECIMAL_DF(4.2));
        ASSERT(BDLDFP_DECIMAL_DL(4.2e9) == BDLDFP_DECIMAL_DF(4.2e9));

        ASSERT(BDLDFP_DECIMAL_DL(-42.0) == BDLDFP_DECIMAL_DD(-42.0));// Dec64
        ASSERT(BDLDFP_DECIMAL_DL(42.0) == BDLDFP_DECIMAL_DD(42.0));
        ASSERT(BDLDFP_DECIMAL_DL(4.2) == BDLDFP_DECIMAL_DD(4.2));
        ASSERT(BDLDFP_DECIMAL_DL(4.2e9) == BDLDFP_DECIMAL_DD(4.2e9));

        if (verbose2) bsl::cout << "Propriatery accessors" << bsl::endl;
        {
            BDEC::Decimal128 d128(42);
            ASSERT((void*)d128.data() == (void*)&d128);

            const BDEC::Decimal128 cd128(42);
            ASSERT((const void*)d128.data() == (const void*)&d128);

            ASSERT(BDEC::Decimal128(cd128.value()) == BDEC::Decimal128(42));
        }

        if (verbose2) bsl::cout << "Operator==" << bsl::endl;

        ASSERT(! (BDLDFP_DECIMAL_DL(4.0) == BDLDFP_DECIMAL_DL(5.0)));
        ASSERT(BDLDFP_DECIMAL_DL(-9.345e27) == BDLDFP_DECIMAL_DL(-9.345e27));

        ASSERT(! (BDLDFP_DECIMAL_DL(4.0) == BDLDFP_DECIMAL_DD(5.0)));
        ASSERT(BDLDFP_DECIMAL_DL(-9.345e27) == BDLDFP_DECIMAL_DD(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DD(4.0) == BDLDFP_DECIMAL_DL(5.0)));
        ASSERT(BDLDFP_DECIMAL_DD(-9.345e27) == BDLDFP_DECIMAL_DL(-9.345e27));

        ASSERT(! (BDLDFP_DECIMAL_DL(4.0) == BDLDFP_DECIMAL_DF(5.0)));
        ASSERT(BDLDFP_DECIMAL_DL(-9.345e27) == BDLDFP_DECIMAL_DF(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DF(4.0) == BDLDFP_DECIMAL_DL(5.0)));
        ASSERT(BDLDFP_DECIMAL_DF(-9.345e27) == BDLDFP_DECIMAL_DL(-9.345e27));

        if (verbose2) bsl::cout << "Operator!=" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DL(4.0) != BDLDFP_DECIMAL_DL(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DL(-9.345e27) !=
                  BDLDFP_DECIMAL_DL(-9.345e27)));

        ASSERT(! (BDLDFP_DECIMAL_DL(4.0) == BDLDFP_DECIMAL_DD(5.0)));
        ASSERT(BDLDFP_DECIMAL_DL(-9.345e27) == BDLDFP_DECIMAL_DD(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DD(4.0) == BDLDFP_DECIMAL_DL(5.0)));
        ASSERT(BDLDFP_DECIMAL_DD(-9.345e27) == BDLDFP_DECIMAL_DL(-9.345e27));

        ASSERT(! (BDLDFP_DECIMAL_DL(4.0) == BDLDFP_DECIMAL_DF(5.0)));
        ASSERT(BDLDFP_DECIMAL_DL(-9.345e27) == BDLDFP_DECIMAL_DF(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DF(4.0) == BDLDFP_DECIMAL_DL(5.0)));
        ASSERT(BDLDFP_DECIMAL_DF(-9.345e27) == BDLDFP_DECIMAL_DL(-9.345e27));

        if (verbose2) bsl::cout << "Operator<" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DL(4.0) < BDLDFP_DECIMAL_DL(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DL(-9.345e27) <
                  BDLDFP_DECIMAL_DL(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DL(5.0) < BDLDFP_DECIMAL_DL(4.0)));

        ASSERT(BDLDFP_DECIMAL_DL(4.0) < BDLDFP_DECIMAL_DD(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DL(-9.345e27) <
                  BDLDFP_DECIMAL_DD(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DL(5.0) < BDLDFP_DECIMAL_DD(4.0)));
        ASSERT(BDLDFP_DECIMAL_DD(4.0) < BDLDFP_DECIMAL_DL(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DD(-9.345e27) <
                  BDLDFP_DECIMAL_DL(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DD(5.0) < BDLDFP_DECIMAL_DL(4.0)));

        ASSERT(BDLDFP_DECIMAL_DL(4.0) < BDLDFP_DECIMAL_DF(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DL(-9.345e27) <
                  BDLDFP_DECIMAL_DF(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DL(5.0) < BDLDFP_DECIMAL_DF(4.0)));
        ASSERT(BDLDFP_DECIMAL_DF(4.0) < BDLDFP_DECIMAL_DL(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DF(-9.345e27) <
                  BDLDFP_DECIMAL_DL(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DF(5.0) < BDLDFP_DECIMAL_DL(4.0)));

        if (verbose2) bsl::cout << "Operator>" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DL(5.0) > BDLDFP_DECIMAL_DL(4.0));
        ASSERT(! (BDLDFP_DECIMAL_DL(-9.345e27) >
                  BDLDFP_DECIMAL_DL(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DL(4.0) > BDLDFP_DECIMAL_DL(5.0)));

        ASSERT(BDLDFP_DECIMAL_DL(5.0) > BDLDFP_DECIMAL_DD(4.0));
        ASSERT(! (BDLDFP_DECIMAL_DL(-9.345e27) >
                  BDLDFP_DECIMAL_DD(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DL(4.0) > BDLDFP_DECIMAL_DD(5.0)));
        ASSERT(BDLDFP_DECIMAL_DD(5.0) > BDLDFP_DECIMAL_DL(4.0));
        ASSERT(! (BDLDFP_DECIMAL_DD(-9.345e27) >
                  BDLDFP_DECIMAL_DL(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DD(4.0) > BDLDFP_DECIMAL_DL(5.0)));

        ASSERT(BDLDFP_DECIMAL_DL(5.0) > BDLDFP_DECIMAL_DF(4.0));
        ASSERT(! (BDLDFP_DECIMAL_DL(-9.345e27) >
                  BDLDFP_DECIMAL_DF(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DL(4.0) > BDLDFP_DECIMAL_DF(5.0)));
        ASSERT(BDLDFP_DECIMAL_DF(5.0) > BDLDFP_DECIMAL_DL(4.0));
        ASSERT(! (BDLDFP_DECIMAL_DF(-9.345e27) >
                  BDLDFP_DECIMAL_DL(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DF(4.0) > BDLDFP_DECIMAL_DL(5.0)));

        if (verbose2) bsl::cout << "Operator<=" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DL(4.0) <= BDLDFP_DECIMAL_DL(5.0));
        ASSERT(BDLDFP_DECIMAL_DL(-9.345e27) <= BDLDFP_DECIMAL_DL(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DL(5.0) <= BDLDFP_DECIMAL_DL(4.0)));

        ASSERT(BDLDFP_DECIMAL_DL(4.0) <= BDLDFP_DECIMAL_DD(5.0));
        ASSERT(BDLDFP_DECIMAL_DL(-9.345e27) <= BDLDFP_DECIMAL_DD(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DL(5.0) <= BDLDFP_DECIMAL_DD(4.0)));
        ASSERT(BDLDFP_DECIMAL_DD(4.0) <= BDLDFP_DECIMAL_DL(5.0));
        ASSERT(BDLDFP_DECIMAL_DD(-9.345e27) <= BDLDFP_DECIMAL_DL(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DD(5.0) <= BDLDFP_DECIMAL_DL(4.0)));

        ASSERT(BDLDFP_DECIMAL_DL(4.0) <= BDLDFP_DECIMAL_DF(5.0));
        ASSERT(BDLDFP_DECIMAL_DL(-9.345e27) <= BDLDFP_DECIMAL_DF(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DL(5.0) <= BDLDFP_DECIMAL_DF(4.0)));
        ASSERT(BDLDFP_DECIMAL_DF(4.0) <= BDLDFP_DECIMAL_DL(5.0));
        ASSERT(BDLDFP_DECIMAL_DF(-9.345e27) <= BDLDFP_DECIMAL_DL(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DF(5.0) <= BDLDFP_DECIMAL_DL(4.0)));

        if (verbose2) bsl::cout << "Operator>=" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DL(5.0) >= BDLDFP_DECIMAL_DL(4.0));
        ASSERT(BDLDFP_DECIMAL_DL(-9.345e27) >= BDLDFP_DECIMAL_DL(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DL(4.0) >= BDLDFP_DECIMAL_DL(5.0)));

        ASSERT(BDLDFP_DECIMAL_DL(5.0) >= BDLDFP_DECIMAL_DD(4.0));
        ASSERT(BDLDFP_DECIMAL_DL(-9.345e27) >= BDLDFP_DECIMAL_DD(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DL(4.0) >= BDLDFP_DECIMAL_DD(5.0)));
        ASSERT(BDLDFP_DECIMAL_DD(5.0) >= BDLDFP_DECIMAL_DL(4.0));
        ASSERT(BDLDFP_DECIMAL_DD(-9.345e27) >= BDLDFP_DECIMAL_DL(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DD(4.0) >= BDLDFP_DECIMAL_DL(5.0)));

        ASSERT(BDLDFP_DECIMAL_DL(5.0) >= BDLDFP_DECIMAL_DF(4.0));
        ASSERT(BDLDFP_DECIMAL_DL(-9.345e27) >= BDLDFP_DECIMAL_DF(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DL(4.0) >= BDLDFP_DECIMAL_DF(5.0)));
        ASSERT(BDLDFP_DECIMAL_DF(5.0) >= BDLDFP_DECIMAL_DL(4.0));
        ASSERT(BDLDFP_DECIMAL_DF(-9.345e27) >= BDLDFP_DECIMAL_DL(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DF(4.0) >= BDLDFP_DECIMAL_DL(5.0)));

        // TODO TBD: Note that I am testing with the maximum number of
        // significant digits and I actually expect stream output to do no
        // rounding.  That is wrong (see later why), but necessary to
        // remote-test the 'format' function and make sure it does not lose
        // digits or does some unwanted rounding.  When 'format' will be in the
        // lower utility, it will be tested directly.
        // Expecting to see all digits is wrong because that is not how the
        // stream output should behave: it should print with the default
        // precision as it would for binary floating point *or* with the
        // implied precision of the cohort if that is larger.  AFAIU

        if (verbose2) bsl::cout << "Test stream out" << bsl::endl;
        {
            bsl::ostringstream  out(pa);

            BDEC::Decimal128 d1(BDLDFP_DECIMAL_DL(
                                    -1.234567890123456789012345678901234e-24));
            out << d1;
            bsl::string s(pa);
            getStringFromStream(out, &s);
            ASSERT(decLower(s) == "-1.234567890123456789012345678901234e-24");
        }

        if (verbose2) bsl::cout << "Test stream in" << bsl::endl;
        {
            bsl::istringstream  in(pa);
            bsl::string ins("-1.234567890123456789012345678901234e-24", pa);
            in.str(ins);

            BDEC::Decimal128 d1;
            in >> d1;
            ASSERT(d1 ==
                  BDLDFP_DECIMAL_DL(-1.234567890123456789012345678901234e-24));
        }

        if (verbose2) bsl::cout << "Test wide stream out" << bsl::endl;
        {
            bsl::wostringstream  out(pa);
            BDEC::Decimal128 d1(BDLDFP_DECIMAL_DL(
                                    -1.234567890123456789012345678901234e-24));
            out << d1;
            bsl::wstring s(pa);
            getStringFromStream(out, &s);
            ASSERT(decLower(s) == L"-1.234567890123456789012345678901234e-24");
        }

        if (verbose2) bsl::cout << "Test wide stream in" << bsl::endl;
        {
            bsl::wistringstream  in(pa);
            bsl::wstring ins(L"-1.234567890123456789012345678901234e-24", pa);
            in.str(ins);

            BDEC::Decimal128 d1;
            in >> d1;
            ASSERT(d1 ==
                  BDLDFP_DECIMAL_DL(-1.234567890123456789012345678901234e-24));
        }

        if (verbose2) bsl::cout << "Operator++" << bsl::endl;
        {
            BDEC::Decimal128 d1(BDLDFP_DECIMAL_DL(-5.0));
            BDEC::Decimal128 d2 = d1++;
            ASSERT(BDLDFP_DECIMAL_DL(-5.0) == d2);
            LOOP_ASSERT(d1, BDLDFP_DECIMAL_DL(-4.0) == d1);
            BDEC::Decimal128 d3 = ++d2;
            LOOP_ASSERT(d2, BDLDFP_DECIMAL_DL(-4.0) == d2);
            LOOP_ASSERT(d3, BDLDFP_DECIMAL_DL(-4.0) == d3);
        }

        if (verbose2) bsl::cout << "Operator--" << bsl::endl;
        {
            BDEC::Decimal128 d1(BDLDFP_DECIMAL_DL(-5.0));
            BDEC::Decimal128 d2 = d1--;
            ASSERT(BDLDFP_DECIMAL_DL(-5.0) == d2);
            LOOP_ASSERT(d1, BDLDFP_DECIMAL_DL(-6.0) == d1);
            BDEC::Decimal128 d3 = --d2;
            LOOP_ASSERT(d2, BDLDFP_DECIMAL_DL(-6.0) == d2);
            LOOP_ASSERT(d3, BDLDFP_DECIMAL_DL(-6.0) == d3);
        }

        if (verbose2) bsl::cout << "Unary-" << bsl::endl;
        {
            BDEC::Decimal128 d1(BDLDFP_DECIMAL_DL(-5.0));
            BDEC::Decimal128 d2(BDLDFP_DECIMAL_DL( 5.0));
            ASSERT(BDLDFP_DECIMAL_DL( 5.0) == -d1);
            ASSERT(BDLDFP_DECIMAL_DL(-5.0) == -d2);

            // Unary - must make +0 into -0

            bsl::ostringstream out(pa);
            out << -BDLDFP_DECIMAL_DL(0.0);
            bsl::string s(pa);
            getStringFromStream(out, &s);
            LOOP_ASSERT(s, s[0] == '-'); // it is negative
            ASSERT(-BDLDFP_DECIMAL_DL(0.0) == BDEC::Decimal128(0)); // and 0
        }

        if (verbose2) bsl::cout << "Unary+" << bsl::endl;
        {
            BDEC::Decimal128 d1(BDLDFP_DECIMAL_DL(-5.0));
            BDEC::Decimal128 d2(BDLDFP_DECIMAL_DL( 5.0));
            ASSERT(BDLDFP_DECIMAL_DL(-5.0) == +d1);
            ASSERT(BDLDFP_DECIMAL_DL( 5.0) == +d2);

            // Unary + must make -0 into +0

            BDEC::Decimal128 negzero(-BDLDFP_DECIMAL_DL(0.0));
            bsl::ostringstream out(pa);
            out << +negzero;
            bsl::string s(pa);
            getStringFromStream(out, &s);
            LOOP_ASSERT(s, s[0] != '+'); // it is positive
            ASSERT(-BDLDFP_DECIMAL_DL(0.0) == BDEC::Decimal128(0)); // and 0
        }

        if (verbose2) bsl::cout << "+=" << bsl::endl;
        {
            BDEC::Decimal128 d(BDLDFP_DECIMAL_DL(-5.0));

            if (verbose3) bsl::cout << "+=(int)" << bsl::endl;
            d += 1;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-4.0) == d);

            if (verbose3) bsl::cout << "+=(unsigned int)" << bsl::endl;
            d += 2u;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-2.0) == d);

            if (verbose3) bsl::cout << "+=(long int)" << bsl::endl;
            d += -1l;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-3.0) == d);

            if (verbose3) bsl::cout << "+=(unsigned long int)" << bsl::endl;
            d += 5ul;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(2.0) == d);

            if (verbose3) bsl::cout << "+=(long long int)" << bsl::endl;
            d += -2ll;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(0.0) == d);

            if (verbose3) bsl::cout << "+=(unsigned long long int)"
                                    << bsl::endl;
            d += 42ull;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(42.0) == d);

            if (verbose3) bsl::cout << "+=(Decimal32)" << bsl::endl;
            d += BDLDFP_DECIMAL_DF(-22.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(20.0) == d);

            if (verbose3) bsl::cout << "+=(Decimal64)" << bsl::endl;
            d += BDLDFP_DECIMAL_DD(3.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(23.0) == d);

            if (verbose3) bsl::cout << "+=(Decimal128)" << bsl::endl;
            d += BDLDFP_DECIMAL_DL(9.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(32.0) == d);
        }

        if (verbose2) bsl::cout << "-=" << bsl::endl;
        {
            BDEC::Decimal128 d(BDLDFP_DECIMAL_DL(-5.0));

            if (verbose3) bsl::cout << "-=(int)" << bsl::endl;
            d -= 1;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-6.0) == d);

            if (verbose3) bsl::cout << "-=(unsigned int)" << bsl::endl;
            d -= 2u;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-8.0) == d);

            if (verbose3) bsl::cout << "-=(long int)" << bsl::endl;
            d -= -10l;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(2.0) == d);

            if (verbose3) bsl::cout << "-=(unsigned long int)" << bsl::endl;
            d -= 10ul;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-8.0) == d);

            if (verbose3) bsl::cout << "-=(long long int)" << bsl::endl;
            d -= -8ll;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(0.0) == d);

            if (verbose3) bsl::cout << "-=(unsigned long long int)"
                                    << bsl::endl;
            d -= 42ull;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-42.0) == d);

            if (verbose3) bsl::cout << "-=(Decimal32)" << bsl::endl;
            d -= BDLDFP_DECIMAL_DF(-22.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-20.0) == d);

            if (verbose3) bsl::cout << "-=(Decimal64)" << bsl::endl;
            d -= BDLDFP_DECIMAL_DD(3.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-23.0) == d);

            if (verbose3) bsl::cout << "-=(Decimal128)" << bsl::endl;
            d -= BDLDFP_DECIMAL_DL(9.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-32.0) == d);
        }

        if (verbose2) bsl::cout << "*=" << bsl::endl;
        {
            BDEC::Decimal128 d(BDLDFP_DECIMAL_DL(-5.0));

            if (verbose3) bsl::cout << "*=(int)" << bsl::endl;
            d *= -2;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(10.0) == d);

            if (verbose3) bsl::cout << "*=(unsigned int)" << bsl::endl;
            d *= 2000u;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(20000.0) == d);

            if (verbose3) bsl::cout << "*=(long int)" << bsl::endl;
            d *= -10l;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-200000.0) == d);

            if (verbose3) bsl::cout << "*=(unsigned long int)" << bsl::endl;
            d *= 3ul;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-600000.0) == d);

            if (verbose3) bsl::cout << "*=(long long int)" << bsl::endl;
            d *= -1ll;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(600000.0) == d);

            if (verbose3) bsl::cout << "*=(unsigned long long int)"
                                    << bsl::endl;
            d *= 5ull;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(3000000.0) == d);

            if (verbose3) bsl::cout << "*=(Decimal32)" << bsl::endl;
            d *= BDLDFP_DECIMAL_DF(1e-5);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(30.0) == d);

            if (verbose3) bsl::cout << "*=(Decimal64)" << bsl::endl;
            d *= BDLDFP_DECIMAL_DD(-3.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-90.0) == d);

            if (verbose3) bsl::cout << "*=(Decimal128)" << bsl::endl;
            d *= BDLDFP_DECIMAL_DL(2.4e-134);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-2.16e-132) == d);
        }

        if (verbose2) bsl::cout << "/=" << bsl::endl;
        {
            BDEC::Decimal128 d(BDLDFP_DECIMAL_DL(-5.0));

            if (verbose3) bsl::cout << "/=(int)" << bsl::endl;
            d /= -2;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(2.5) == d);

            if (verbose3) bsl::cout << "/=(unsigned int)" << bsl::endl;
            d /= 2000u;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(0.00125) == d);

            if (verbose3) bsl::cout << "/=(long int)" << bsl::endl;
            d /= -10l;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-0.000125) == d);

            if (verbose3) bsl::cout << "/=(unsigned long int)" << bsl::endl;
            d /= 5ul;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-0.000025) == d);

            if (verbose3) bsl::cout << "/=(long long int)" << bsl::endl;
            d /= -5ll;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(0.000005) == d);

            if (verbose3) bsl::cout << "/=(unsigned long long int)"
                                    << bsl::endl;
            d /= 5ull;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(0.000001) == d);

            if (verbose3) bsl::cout << "/=(Decimal32)" << bsl::endl;
            d /= BDLDFP_DECIMAL_DF(1e-5);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(0.1) == d);

            if (verbose3) bsl::cout << "/=(Decimal64)" << bsl::endl;
            d /= BDLDFP_DECIMAL_DD(-5.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(-0.02) == d);

            if (verbose3) bsl::cout << "/=(Decimal128)" << bsl::endl;
            d /= BDLDFP_DECIMAL_DL(-2.5e-134);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DL(8.e131) == d);
        }

        if (verbose2) bsl::cout << "operator+" << bsl::endl;
        {
            BDEC::Decimal128 d(BDLDFP_DECIMAL_DL(-5.0));

            if (verbose3) bsl::cout << "dec + int" << bsl::endl;
            LOOP_ASSERT(d + 1, d + 1 == BDLDFP_DECIMAL_DL(-4.0));
            LOOP_ASSERT(1 + d, 1 + d == BDLDFP_DECIMAL_DL(-4.0));

            if (verbose3) bsl::cout << "dec + unsigned int" << bsl::endl;
            LOOP_ASSERT(d + 10u, d + 10u == BDLDFP_DECIMAL_DL(5.0));
            LOOP_ASSERT(10u + d, 10u + d == BDLDFP_DECIMAL_DL(5.0));

            if (verbose3) bsl::cout << "dec + long int" << bsl::endl;
            LOOP_ASSERT(d + 1l, d + 1l == BDLDFP_DECIMAL_DL(-4.0));
            LOOP_ASSERT(1l + d, 1l + d == BDLDFP_DECIMAL_DL(-4.0));

            if (verbose3) bsl::cout << "dec + unsigned long int" << bsl::endl;
            LOOP_ASSERT(d + 10ul, d + 10ul == BDLDFP_DECIMAL_DL(5.0));
            LOOP_ASSERT(10ul + d, 10ul + d == BDLDFP_DECIMAL_DL(5.0));

            if (verbose3) bsl::cout << "dec + long long int" << bsl::endl;
            LOOP_ASSERT(d + 1ll, d + 1ll == BDLDFP_DECIMAL_DL(-4.0));
            LOOP_ASSERT(1ll + d, 1ll + d == BDLDFP_DECIMAL_DL(-4.0));

            if (verbose3) bsl::cout << "dec + unsigned long long int"
                                    << bsl::endl;
            LOOP_ASSERT(d + 10ull, d + 10ull == BDLDFP_DECIMAL_DL(5.0));
            LOOP_ASSERT(10ull + d, 10ull + d == BDLDFP_DECIMAL_DL(5.0));

            if (verbose3) bsl::cout << "dec + dec128" << bsl::endl;
            LOOP_ASSERT(d + BDLDFP_DECIMAL_DL(-3.0),
                        d + BDLDFP_DECIMAL_DL(-3.0) ==
                        BDLDFP_DECIMAL_DL(-8.0));

            if (verbose3) bsl::cout << "dec + dec32" << bsl::endl;
            LOOP_ASSERT(d + BDLDFP_DECIMAL_DF(-3.0),
                        d + BDLDFP_DECIMAL_DF(-3.0) ==
                        BDLDFP_DECIMAL_DL(-8.0));
            LOOP_ASSERT(BDLDFP_DECIMAL_DF(-3.0) + d,
                        BDLDFP_DECIMAL_DF(-3.0) + d ==
                        BDLDFP_DECIMAL_DL(-8.0));

            if (verbose3) bsl::cout << "dec + dec64" << bsl::endl;
            LOOP_ASSERT(d + BDLDFP_DECIMAL_DD(-3.0),
                        d + BDLDFP_DECIMAL_DD(-3.0) ==
                        BDLDFP_DECIMAL_DL(-8.0));
            LOOP_ASSERT(BDLDFP_DECIMAL_DD(-3.0) + d,
                        BDLDFP_DECIMAL_DD(-3.0) + d ==
                        BDLDFP_DECIMAL_DL(-8.0));
        }

        if (verbose2) bsl::cout << "operator-" << bsl::endl;
        {
            BDEC::Decimal128 d(BDLDFP_DECIMAL_DL(-5.0));

            if (verbose3) bsl::cout << "dec - int" << bsl::endl;
            LOOP_ASSERT(d - 1, d - 1 == BDLDFP_DECIMAL_DL(-6.0));
            LOOP_ASSERT(1 - d, 1 - d == BDLDFP_DECIMAL_DL( 6.0));

            if (verbose3) bsl::cout << "dec - unsigned int" << bsl::endl;
            LOOP_ASSERT(d - 10u, d - 10u == BDLDFP_DECIMAL_DL(-15.0));
            LOOP_ASSERT(10u - d, 10u - d == BDLDFP_DECIMAL_DL( 15.0));

            if (verbose3) bsl::cout << "dec - long int" << bsl::endl;
            LOOP_ASSERT(d - 1l, d - 1l == BDLDFP_DECIMAL_DL(-6.0));
            LOOP_ASSERT(1l - d, 1l - d == BDLDFP_DECIMAL_DL( 6.0));

            if (verbose3) bsl::cout << "dec - unsigned long int" << bsl::endl;
            LOOP_ASSERT(d - 10ul, d - 10ul == BDLDFP_DECIMAL_DL(-15.0));
            LOOP_ASSERT(10ul - d, 10ul - d == BDLDFP_DECIMAL_DL( 15.0));

            if (verbose3) bsl::cout << "dec - long long int" << bsl::endl;
            LOOP_ASSERT(d - 1ll, d - 1ll == BDLDFP_DECIMAL_DL(-6.0));
            LOOP_ASSERT(1ll - d, 1ll - d == BDLDFP_DECIMAL_DL( 6.0));

            if (verbose3) bsl::cout << "dec - unsigned long long int"
                                    << bsl::endl;
            LOOP_ASSERT(d - 10ull, d - 10ull == BDLDFP_DECIMAL_DL(-15.0));
            LOOP_ASSERT(10ull - d, 10ull - d == BDLDFP_DECIMAL_DL( 15.0));

            if (verbose3) bsl::cout << "dec - dec128" << bsl::endl;
            LOOP_ASSERT(d - BDLDFP_DECIMAL_DL(-3.0),
                        d - BDLDFP_DECIMAL_DL(-3.0) ==
                        BDLDFP_DECIMAL_DL(-2.0));

            if (verbose3) bsl::cout << "dec - dec32" << bsl::endl;
            LOOP_ASSERT(d - BDLDFP_DECIMAL_DF(-3.0),
                        d - BDLDFP_DECIMAL_DF(-3.0) ==
                        BDLDFP_DECIMAL_DL(-2.0));
            LOOP_ASSERT(BDLDFP_DECIMAL_DF(-3.0) - d,
                        BDLDFP_DECIMAL_DF(-3.0) - d ==
                        BDLDFP_DECIMAL_DL( 2.0));

            if (verbose3) bsl::cout << "dec - dec64" << bsl::endl;
            LOOP_ASSERT(d - BDLDFP_DECIMAL_DD(-3.0),
                        d - BDLDFP_DECIMAL_DD(-3.0) ==
                        BDLDFP_DECIMAL_DL(-2.0));
            LOOP_ASSERT(BDLDFP_DECIMAL_DD(-3.0) - d,
                        BDLDFP_DECIMAL_DD(-3.0) - d ==
                        BDLDFP_DECIMAL_DL( 2.0));
        }

        if (verbose2) bsl::cout << "operator*" << bsl::endl;
        {
            BDEC::Decimal64 d(BDLDFP_DECIMAL_DD(-5.0));

            if (verbose3) bsl::cout << "dec * int" << bsl::endl;
            LOOP_ASSERT(d * -2, d * -2 == BDLDFP_DECIMAL_DD(10.0));
            LOOP_ASSERT(-2 * d, -2 * d == BDLDFP_DECIMAL_DD(10.0));

            if (verbose3) bsl::cout << "dec * unsigned int" << bsl::endl;
            LOOP_ASSERT(d * 10u, d * 10u == BDLDFP_DECIMAL_DD(-50.0));
            LOOP_ASSERT(10u * d, 10u * d == BDLDFP_DECIMAL_DD(-50.0));

            if (verbose3) bsl::cout << "dec * long int" << bsl::endl;
            LOOP_ASSERT(d * -2l, d * -2l == BDLDFP_DECIMAL_DD(10.0));
            LOOP_ASSERT(-2l * d, -2l * d == BDLDFP_DECIMAL_DD(10.0));

            if (verbose3) bsl::cout << "dec * unsigned long int" << bsl::endl;
            LOOP_ASSERT(d * 10ul, d * 10ul == BDLDFP_DECIMAL_DD(-50.0));
            LOOP_ASSERT(10ul * d, 10ul * d == BDLDFP_DECIMAL_DD(-50.0));

            if (verbose3) bsl::cout << "dec * long long int" << bsl::endl;
            LOOP_ASSERT(d * -2ll, d * -2ll == BDLDFP_DECIMAL_DD(10.0));
            LOOP_ASSERT(-2ll * d, -2ll * d == BDLDFP_DECIMAL_DD(10.0));

            if (verbose3) bsl::cout << "dec * unsigned long long int"
                                    << bsl::endl;
            LOOP_ASSERT(d * 10ull, d * 10ull == BDLDFP_DECIMAL_DD(-50.0));
            LOOP_ASSERT(10ull * d, 10ull * d == BDLDFP_DECIMAL_DD(-50.0));

            if (verbose3) bsl::cout << "dec * dec64" << bsl::endl;
            LOOP_ASSERT(d * BDLDFP_DECIMAL_DD(-3.0),
                        d * BDLDFP_DECIMAL_DD(-3.0) ==
                        BDLDFP_DECIMAL_DD(15.0));

            if (verbose3) bsl::cout << "dec * dec32" << bsl::endl;
            LOOP_ASSERT(d * BDLDFP_DECIMAL_DF(-3.0),
                        d * BDLDFP_DECIMAL_DF(-3.0) ==
                        BDLDFP_DECIMAL_DD(15.0));
            LOOP_ASSERT(BDLDFP_DECIMAL_DF(-3.0) * d,
                        BDLDFP_DECIMAL_DF(-3.0) * d ==
                        BDLDFP_DECIMAL_DD(15.0));
        }

        if (verbose2) bsl::cout << "operator/" << bsl::endl;
        {
            BDEC::Decimal128 d(BDLDFP_DECIMAL_DL(-5.0));

            if (verbose3) bsl::cout << "dec / int" << bsl::endl;
            LOOP_ASSERT(d / -2, d / -2 == BDLDFP_DECIMAL_DL(2.5));
            LOOP_ASSERT(-2 / d, -2 / d == BDLDFP_DECIMAL_DL(0.4));

            if (verbose3) bsl::cout << "dec / unsigned int" << bsl::endl;
            LOOP_ASSERT(d / 100u, d / 100u == BDLDFP_DECIMAL_DL( -0.05));
            LOOP_ASSERT(100u / d, 100u / d == BDLDFP_DECIMAL_DL(-20.0));

            if (verbose3) bsl::cout << "dec / long int" << bsl::endl;
            LOOP_ASSERT(d / -2l, d / -2l == BDLDFP_DECIMAL_DL(2.5));
            LOOP_ASSERT(-2l / d, -2l / d == BDLDFP_DECIMAL_DL(0.4));

            if (verbose3) bsl::cout << "dec / unsigned long int" << bsl::endl;
            LOOP_ASSERT(d / 100ul, d / 100ul == BDLDFP_DECIMAL_DL( -0.05));
            LOOP_ASSERT(100ul / d, 100ul / d == BDLDFP_DECIMAL_DL(-20.0));

            if (verbose3) bsl::cout << "dec / long long int" << bsl::endl;
            LOOP_ASSERT(d / -2ll, d / -2ll == BDLDFP_DECIMAL_DL(2.5));
            LOOP_ASSERT(-2ll / d, -2ll / d == BDLDFP_DECIMAL_DL(0.4));

            if (verbose3) bsl::cout << "dec / unsigned long long int"
                                    << bsl::endl;
            LOOP_ASSERT(d / 100ull, d / 100ull == BDLDFP_DECIMAL_DL( -0.05));
            LOOP_ASSERT(100ull / d, 100ull / d == BDLDFP_DECIMAL_DL(-20.0));

            if (verbose3) bsl::cout << "dec / dec128" << bsl::endl;
            LOOP_ASSERT(d / BDLDFP_DECIMAL_DL(-50.0),
                        d / BDLDFP_DECIMAL_DL(-50.0) ==
                        BDLDFP_DECIMAL_DL(0.1));

            if (verbose3) bsl::cout << "dec / dec32" << bsl::endl;
            LOOP_ASSERT(d / BDLDFP_DECIMAL_DF(-50.0),
                        d / BDLDFP_DECIMAL_DF(-50.0) ==
                        BDLDFP_DECIMAL_DL(0.1));
            LOOP_ASSERT(BDLDFP_DECIMAL_DF(-50.0) / d,
                        BDLDFP_DECIMAL_DF(-50.0) / d ==
                        BDLDFP_DECIMAL_DL(10.0));

            if (verbose3) bsl::cout << "dec / dec64" << bsl::endl;
            LOOP_ASSERT(d / BDLDFP_DECIMAL_DD(-50.0),
                        d / BDLDFP_DECIMAL_DD(-50.0) ==
                        BDLDFP_DECIMAL_DL(0.1));
            LOOP_ASSERT(BDLDFP_DECIMAL_DD(-50.0) / d,
                        BDLDFP_DECIMAL_DD(-50.0) / d ==
                        BDLDFP_DECIMAL_DL(10.0));
        }

        if (verbose2) bsl::cout << "Create test objects" << bsl::endl;

        BDEC::Decimal32        d32  = BDEC::Decimal32();
        const BDEC::Decimal32  c32  = BDEC::Decimal32();
        BDEC::Decimal64        d64  = BDEC::Decimal64();
        const BDEC::Decimal64  c64  = BDEC::Decimal64();
        BDEC::Decimal128       d128 = BDEC::Decimal128();
        const BDEC::Decimal128 c128 = BDEC::Decimal128();

        if (verbose2) bsl::cout << "Check return types" << bsl::endl;

        checkType<BDEC::Decimal128&>(++d128);
        checkType<BDEC::Decimal128>(d128++);
        checkType<BDEC::Decimal128&>(--d128);
        checkType<BDEC::Decimal128>(d128--);
        checkType<BDEC::Decimal128&>(d128 += static_cast<char>(1));
        checkType<BDEC::Decimal128&>(d128 += static_cast<unsigned char>(1));
        checkType<BDEC::Decimal128&>(d128 += static_cast<signed char>(1));
        checkType<BDEC::Decimal128&>(d128 += static_cast<short>(1));
        checkType<BDEC::Decimal128&>(d128 += static_cast<unsigned short>(1));
        checkType<BDEC::Decimal128&>(d128 += static_cast<int>(1));
        checkType<BDEC::Decimal128&>(d128 += static_cast<unsigned int>(1));
        checkType<BDEC::Decimal128&>(d128 += static_cast<long>(1));
        checkType<BDEC::Decimal128&>(d128 += static_cast<unsigned long>(1));
        checkType<BDEC::Decimal128&>(d128 += static_cast<long long>(1));
        checkType<BDEC::Decimal128&>(d128 +=
                                     static_cast<unsigned long long>(1));
        checkType<BDEC::Decimal128&>(d128 += static_cast<BDEC::Decimal32>(1));
        checkType<BDEC::Decimal128&>(d128 += static_cast<BDEC::Decimal64>(1));
        checkType<BDEC::Decimal128&>(d128 += static_cast<BDEC::Decimal128>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<char>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<unsigned char>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<signed char>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<short>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<unsigned short>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<int>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<unsigned int>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<long>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<unsigned long>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<long long>(1));
        checkType<BDEC::Decimal128&>(d128 -=
                                     static_cast<unsigned long long>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<BDEC::Decimal32>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<BDEC::Decimal64>(1));
        checkType<BDEC::Decimal128&>(d128 -= static_cast<BDEC::Decimal128>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<char>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<unsigned char>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<signed char>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<short>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<unsigned short>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<int>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<unsigned int>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<long>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<unsigned long>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<long long>(1));
        checkType<BDEC::Decimal128&>(d128 *=
                                     static_cast<unsigned long long>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<BDEC::Decimal32>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<BDEC::Decimal64>(1));
        checkType<BDEC::Decimal128&>(d128 *= static_cast<BDEC::Decimal128>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<char>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<unsigned char>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<signed char>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<short>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<unsigned short>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<int>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<unsigned int>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<long>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<unsigned long>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<long long>(1));
        checkType<BDEC::Decimal128&>(d128 /=
                                     static_cast<unsigned long long>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<BDEC::Decimal32>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<BDEC::Decimal64>(1));
        checkType<BDEC::Decimal128&>(d128 /= static_cast<BDEC::Decimal128>(1));

        checkType<BDEC::Decimal128>(+d128);
        checkType<BDEC::Decimal128>(-d128);

        checkType<BDEC::Decimal128>(d128 + d128);
        checkType<BDEC::Decimal128>(d128 - d128);
        checkType<BDEC::Decimal128>(d128 * d128);
        checkType<BDEC::Decimal128>(d128 / d128);
        checkType<bool>(d128 == d128);
        checkType<bool>(d32 == d128);
        checkType<bool>(d128 == d32);
        checkType<bool>(d128 != d128);
        checkType<bool>(d32 != d128);
        checkType<bool>(d128 != d32);
        checkType<bool>(d128 < d128);
        checkType<bool>(d32 < d128);
        checkType<bool>(d128 < d32);
        checkType<bool>(d128 <= d128);
        checkType<bool>(d32 <= d128);
        checkType<bool>(d128 <= d32);
        checkType<bool>(d128 > d128);
        checkType<bool>(d32 > d128);
        checkType<bool>(d128 > d32);
        checkType<bool>(d128 >= d128);
        checkType<bool>(d32 >= d128);
        checkType<bool>(d128 >= d32);

        {
            bsl::istringstream  in(pa);
            bsl::wistringstream win(pa);
            bsl::ostringstream  out(pa);
            bsl::wostringstream wout(pa);

            checkType<bsl::istream&>(in >> d128);
            checkType<bsl::wistream&>(win >> d128);
            checkType<bsl::ostream&>(out << c128);
            checkType<bsl::wostream&>(wout << c128);
        }


        typedef bsl::numeric_limits<BDEC::Decimal128> d128_limits;
        checkType<bool>(d128_limits::is_specialized);
        checkType<BDEC::Decimal128>(d128_limits::min());
        checkType<BDEC::Decimal128>(d128_limits::max());
        checkType<int>(d128_limits::digits);
        checkType<int>(d128_limits::digits10);
        checkType<int>(d128_limits::max_digits10);
        checkType<bool>(d128_limits::is_signed);
        checkType<bool>(d128_limits::is_integer);
        checkType<bool>(d128_limits::is_exact);
        checkType<int>(d128_limits::radix);
        checkType<BDEC::Decimal128>(d128_limits::epsilon());
        checkType<BDEC::Decimal128>(d128_limits::round_error());
        checkType<int>(d128_limits::min_exponent);
        checkType<int>(d128_limits::min_exponent10);
        checkType<int>(d128_limits::max_exponent);
        checkType<int>(d128_limits::max_exponent10);
        checkType<bool>(d128_limits::has_infinity);
        checkType<bool>(d128_limits::has_quiet_NaN);
        checkType<bool>(d128_limits::has_signaling_NaN);
        checkType<bsl::float_denorm_style>(d128_limits::has_denorm);
        checkType<bool>(d128_limits::has_denorm_loss);
        checkType<BDEC::Decimal128>(d128_limits::infinity());
        checkType<BDEC::Decimal128>(d128_limits::quiet_NaN());
        checkType<BDEC::Decimal128>(d128_limits::signaling_NaN());
        checkType<BDEC::Decimal128>(d128_limits::denorm_min());
        checkType<bool>(d128_limits::is_iec559);
        checkType<bool>(d128_limits::is_bounded);
        checkType<bool>(d128_limits::is_modulo);
        checkType<bool>(d128_limits::traps);
        checkType<bool>(d128_limits::tinyness_before);
        checkType<bsl::float_round_style>(d128_limits::round_style);
    } break;

    case 3: {
        // --------------------------------------------------------------------
        // TESTING 'Decimal64'
        //   Ensure that 'Decimal64' functions correctly
        //
        // Concerns:
        //: 1 'Decimal64' operations are properly forwarded to implementation
        //: 2 All possible operand combinations work correctly.
        //
        // Plan:
        //: 1 Expected value testing will be used.
        //:
        //: 2 All forms of LHS and RHS combinations for all free operators will
        //:   be tested.
        //:
        //: 3 Every member operator will be tested
        //
        // Testing:
        //   'class Decimal64'
        // --------------------------------------------------------------------

        if (verbose1) bsl::cout << "\nTesting class Decimal64"
                                << "\n=======================" << bsl::endl;

        if (verbose2) bsl::cout << "Constructors" << bsl::endl;

        if (verbose3) bsl::cout << "Copy/convert" << bsl::endl;
        {
            const BDEC::Decimal32  c32  = BDEC::Decimal32(32);
            const BDEC::Decimal64  c64  = BDEC::Decimal64(64);
            const BDEC::Decimal128 c128 = BDEC::Decimal128(128);

            ASSERT(BDLDFP_DECIMAL_DD( 32.0) == BDEC::Decimal64(c32));
            ASSERT(BDLDFP_DECIMAL_DD( 64.0) == BDEC::Decimal64(c64));
            ASSERT(BDLDFP_DECIMAL_DD(128.0) == BDEC::Decimal64(c128));
        }

        if (verbose3) bsl::cout << "Integral" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DD(  0.0) == BDEC::Decimal64());  // default
        ASSERT(BDLDFP_DECIMAL_DD(-42.0) == BDEC::Decimal64(-42)); // int
        ASSERT(BDLDFP_DECIMAL_DD( 42.0) == BDEC::Decimal64(42u)); // unsigned
        ASSERT(BDLDFP_DECIMAL_DD(-42.0) == BDEC::Decimal64(-42l)); // long
        ASSERT(BDLDFP_DECIMAL_DD( 42.0) == BDEC::Decimal64(42ul)); // ulong
        ASSERT(BDLDFP_DECIMAL_DD(-42.0) == BDEC::Decimal64(-42ll)); // longlong
        ASSERT(BDLDFP_DECIMAL_DD( 42.0) == BDEC::Decimal64(42ull)); // ulongl

        if (verbose3) bsl::cout << "Binary FP" << bsl::endl;

        // Note that to test binary-float taking constructors I use numbers
        // that can be represented exactly in both binary and decimal FP.

        ASSERT(BDLDFP_DECIMAL_DD(4.25) == BDEC::Decimal64(4.25f)); // float
        ASSERT(BDLDFP_DECIMAL_DD(4.25) == BDEC::Decimal64(4.25)); // double

        if (verbose3) bsl::cout << "Decimal FP" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DD(-42.0) ==
               BDLDFP_DECIMAL_DF(-42.0));// Decimal342
        ASSERT(BDLDFP_DECIMAL_DD(42.0) == BDLDFP_DECIMAL_DF(42.0));
        ASSERT(BDLDFP_DECIMAL_DD(4.2) == BDLDFP_DECIMAL_DF(4.2));
        ASSERT(BDLDFP_DECIMAL_DD(4.2e9) == BDLDFP_DECIMAL_DF(4.2e9));

        ASSERT(BDLDFP_DECIMAL_DD(-42.0) == BDLDFP_DECIMAL_DL(-42.0));// Dec128
        ASSERT(BDLDFP_DECIMAL_DD(42.0) == BDLDFP_DECIMAL_DL(42.0));
        ASSERT(BDLDFP_DECIMAL_DD(4.2) == BDLDFP_DECIMAL_DL(4.2));
        ASSERT(BDLDFP_DECIMAL_DD(4.2e9) == BDLDFP_DECIMAL_DL(4.2e9));

        if (verbose2) bsl::cout << "Propriatery accessors" << bsl::endl;
        {
            BDEC::Decimal64 d64(42);
            ASSERT((void*)d64.data() == (void*)&d64);

            const BDEC::Decimal64 cd64(42);
            ASSERT((const void*)d64.data() == (const void*)&d64);

            ASSERT(BDEC::Decimal64(cd64.value()) == BDEC::Decimal64(42));
        }

        if (verbose2) bsl::cout << "Operator==" << bsl::endl;

        ASSERT(! (BDLDFP_DECIMAL_DD(4.0) == BDLDFP_DECIMAL_DD(5.0)));
        ASSERT(BDLDFP_DECIMAL_DD(-9.345e27) == BDLDFP_DECIMAL_DD(-9.345e27));

        ASSERT(! (BDLDFP_DECIMAL_DD(4.0) == BDLDFP_DECIMAL_DF(5.0)));
        ASSERT(BDLDFP_DECIMAL_DD(-9.345e27) == BDLDFP_DECIMAL_DF(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DF(4.0) == BDLDFP_DECIMAL_DD(5.0)));
        ASSERT(BDLDFP_DECIMAL_DF(-9.345e27) == BDLDFP_DECIMAL_DD(-9.345e27));

        if (verbose2) bsl::cout << "Operator!=" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DD(4.0) != BDLDFP_DECIMAL_DD(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DD(-9.345e27) !=
                  BDLDFP_DECIMAL_DD(-9.345e27)));

        ASSERT(BDLDFP_DECIMAL_DD(4.0) != BDLDFP_DECIMAL_DF(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DD(-9.345e27) !=
                  BDLDFP_DECIMAL_DF(-9.345e27)));
        ASSERT(BDLDFP_DECIMAL_DF(4.0) != BDLDFP_DECIMAL_DD(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DF(-9.345e27) !=
                  BDLDFP_DECIMAL_DD(-9.345e27)));

        if (verbose2) bsl::cout << "Operator<" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DD(4.0) < BDLDFP_DECIMAL_DD(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DD(-9.345e27) <
                  BDLDFP_DECIMAL_DD(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DD(5.0) < BDLDFP_DECIMAL_DD(4.0)));

        ASSERT(BDLDFP_DECIMAL_DD(4.0) < BDLDFP_DECIMAL_DF(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DD(-9.345e27) <
                  BDLDFP_DECIMAL_DF(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DD(5.0) < BDLDFP_DECIMAL_DF(4.0)));
        ASSERT(BDLDFP_DECIMAL_DF(4.0) < BDLDFP_DECIMAL_DD(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DF(-9.345e27) <
                  BDLDFP_DECIMAL_DD(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DF(5.0) < BDLDFP_DECIMAL_DD(4.0)));

        if (verbose2) bsl::cout << "Operator>" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DD(5.0) > BDLDFP_DECIMAL_DD(4.0));
        ASSERT(! (BDLDFP_DECIMAL_DD(-9.345e27) >
                  BDLDFP_DECIMAL_DD(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DD(4.0) > BDLDFP_DECIMAL_DD(5.0)));

        ASSERT(BDLDFP_DECIMAL_DD(5.0) > BDLDFP_DECIMAL_DF(4.0));
        ASSERT(! (BDLDFP_DECIMAL_DD(-9.345e27) >
                  BDLDFP_DECIMAL_DF(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DD(4.0) > BDLDFP_DECIMAL_DF(5.0)));
        ASSERT(BDLDFP_DECIMAL_DF(5.0) > BDLDFP_DECIMAL_DD(4.0));
        ASSERT(! (BDLDFP_DECIMAL_DF(-9.345e27) >
                  BDLDFP_DECIMAL_DD(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DF(4.0) > BDLDFP_DECIMAL_DD(5.0)));

        if (verbose2) bsl::cout << "Operator<=" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DD(4.0) <= BDLDFP_DECIMAL_DD(5.0));
        ASSERT(BDLDFP_DECIMAL_DD(-9.345e27) <= BDLDFP_DECIMAL_DD(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DD(5.0) <= BDLDFP_DECIMAL_DD(4.0)));

        ASSERT(BDLDFP_DECIMAL_DD(4.0) <= BDLDFP_DECIMAL_DF(5.0));
        ASSERT(BDLDFP_DECIMAL_DD(-9.345e27) <= BDLDFP_DECIMAL_DF(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DD(5.0) <= BDLDFP_DECIMAL_DF(4.0)));
        ASSERT(BDLDFP_DECIMAL_DF(4.0) <= BDLDFP_DECIMAL_DD(5.0));
        ASSERT(BDLDFP_DECIMAL_DF(-9.345e27) <= BDLDFP_DECIMAL_DD(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DF(5.0) <= BDLDFP_DECIMAL_DD(4.0)));

        if (verbose2) bsl::cout << "Operator>=" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DD(5.0) >= BDLDFP_DECIMAL_DD(4.0));
        ASSERT(BDLDFP_DECIMAL_DD(-9.345e27) >= BDLDFP_DECIMAL_DD(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DD(4.0) >= BDLDFP_DECIMAL_DD(5.0)));

        ASSERT(BDLDFP_DECIMAL_DD(5.0) >= BDLDFP_DECIMAL_DF(4.0));
        ASSERT(BDLDFP_DECIMAL_DD(-9.345e27) >= BDLDFP_DECIMAL_DF(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DD(4.0) >= BDLDFP_DECIMAL_DF(5.0)));
        ASSERT(BDLDFP_DECIMAL_DF(5.0) >= BDLDFP_DECIMAL_DD(4.0));
        ASSERT(BDLDFP_DECIMAL_DF(-9.345e27) >= BDLDFP_DECIMAL_DD(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DF(4.0) >= BDLDFP_DECIMAL_DD(5.0)));

        // TODO TBD: Note that I am testing with the maximum number of
        // significant digits and I actually expect stream output to do no
        // rounding.  That is wrong (see later why), but necessary to
        // remote-test the 'format' function and make sure it does not lose
        // digits or does some unwanted rounding.  When 'format' will be in the
        // lower utility, it will be tested directly.
        // Expecting to see all digits is wrong because that is not how the
        // stream output should behave: it should print with the default
        // precision as it would for binary floating point *or* with the
        // implied precision of the cohort if that is larger.  AFAIU

        if (verbose2) bsl::cout << "Test stream out" << bsl::endl;
        {
            bsl::ostringstream  out(pa);

            BDEC::Decimal64 d1(BDLDFP_DECIMAL_DD(-1.234567890123456e-24));
            out << d1;
            bsl::string s(pa);
            getStringFromStream(out, &s);
            LOOP_ASSERT(s, decLower(s) == "-1.234567890123456e-24");
        }

        if (verbose2) bsl::cout << "Test stream in" << bsl::endl;
        {
            bsl::istringstream  in(pa);
            bsl::string ins("-1.234567890123456e-24", pa);
            in.str(ins);

            BDEC::Decimal64 d1;
            in >> d1;
            ASSERT(d1 == BDLDFP_DECIMAL_DD(-1.234567890123456e-24));
        }

        if (verbose2) bsl::cout << "Test wide stream out" << bsl::endl;
        {
            bsl::wostringstream  out(pa);
            BDEC::Decimal64 d1(BDLDFP_DECIMAL_DD(-1.234567890123456e-24));
            out << d1;
            bsl::wstring s(pa);
            getStringFromStream(out, &s);
            ASSERT(decLower(s) == L"-1.234567890123456e-24");
        }

        if (verbose2) bsl::cout << "Test wide stream in" << bsl::endl;
        {
            bsl::wistringstream  in(pa);
            bsl::wstring ins(L"-1.234567890123456e-24", pa);
            in.str(ins);

            BDEC::Decimal64 d1;
            in >> d1;
            ASSERT(d1 == BDLDFP_DECIMAL_DD(-1.234567890123456e-24));
        }

        if (verbose2) bsl::cout << "Operator++" << bsl::endl;
        {
            BDEC::Decimal64 d1(BDLDFP_DECIMAL_DD(-5.0));
            BDEC::Decimal64 d2 = d1++;
            ASSERT(BDLDFP_DECIMAL_DD(-5.0) == d2);
            LOOP_ASSERT(d1, BDLDFP_DECIMAL_DD(-4.0) == d1);
            BDEC::Decimal64 d3 = ++d2;
            LOOP_ASSERT(d2, BDLDFP_DECIMAL_DD(-4.0) == d2);
            LOOP_ASSERT(d3, BDLDFP_DECIMAL_DD(-4.0) == d3);
        }

        if (verbose2) bsl::cout << "Operator--" << bsl::endl;
        {
            BDEC::Decimal64 d1(BDLDFP_DECIMAL_DD(-5.0));
            BDEC::Decimal64 d2 = d1--;
            ASSERT(BDLDFP_DECIMAL_DD(-5.0) == d2);
            LOOP_ASSERT(d1, BDLDFP_DECIMAL_DD(-6.0) == d1);
            BDEC::Decimal64 d3 = --d2;
            LOOP_ASSERT(d2, BDLDFP_DECIMAL_DD(-6.0) == d2);
            LOOP_ASSERT(d3, BDLDFP_DECIMAL_DD(-6.0) == d3);
        }

        if (verbose2) bsl::cout << "Unary-" << bsl::endl;
        {
            BDEC::Decimal64 d1(BDLDFP_DECIMAL_DD(-5.0));
            BDEC::Decimal64 d2(BDLDFP_DECIMAL_DD( 5.0));
            ASSERT(BDLDFP_DECIMAL_DD( 5.0) == -d1);
            ASSERT(BDLDFP_DECIMAL_DD(-5.0) == -d2);

            // Unary - must make +0 into -0

            bsl::ostringstream out(pa);
            out << -BDLDFP_DECIMAL_DD(0.0);
            bsl::string s(pa);
            getStringFromStream(out, &s);
            LOOP_ASSERT(s, s[0] == '-'); // it is negative
            ASSERT(-BDLDFP_DECIMAL_DD(0.0) == BDEC::Decimal64(0)) // and 0
        }

        if (verbose2) bsl::cout << "Unary+" << bsl::endl;
        {
            BDEC::Decimal64 d1(BDLDFP_DECIMAL_DD(-5.0));
            BDEC::Decimal64 d2(BDLDFP_DECIMAL_DD( 5.0));
            ASSERT(BDLDFP_DECIMAL_DD(-5.0) == +d1);
            ASSERT(BDLDFP_DECIMAL_DD( 5.0) == +d2);

            // Unary + must make -0 into +0

            BDEC::Decimal128 negzero(-BDLDFP_DECIMAL_DD(0.0));
            bsl::ostringstream out(pa);
            out << +negzero;
            bsl::string s(pa);
            getStringFromStream(out, &s);
            LOOP_ASSERT(s, s[0] != '+'); // it is positive
            ASSERT(-BDLDFP_DECIMAL_DD(0.0) == BDEC::Decimal64(0)) // and 0
        }

        if (verbose2) bsl::cout << "+=" << bsl::endl;
        {
            BDEC::Decimal64 d(BDLDFP_DECIMAL_DD(-5.0));

            if (verbose3) bsl::cout << "+=(int)" << bsl::endl;
            d += 1;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-4.0) == d);

            if (verbose3) bsl::cout << "+=(unsigned int)" << bsl::endl;
            d += 2u;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-2.0) == d);

            if (verbose3) bsl::cout << "+=(long int)" << bsl::endl;
            d += -1l;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-3.0) == d);

            if (verbose3) bsl::cout << "+=(unsigned long int)" << bsl::endl;
            d += 5ul;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(2.0) == d);

            if (verbose3) bsl::cout << "+=(long long int)" << bsl::endl;
            d += -2ll;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(0.0) == d);

            if (verbose3) bsl::cout << "+=(unsigned long long int)"
                                    << bsl::endl;
            d += 42ull;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(42.0) == d);

            if (verbose3) bsl::cout << "+=(Decimal32)" << bsl::endl;
            d += BDLDFP_DECIMAL_DF(-22.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(20.0) == d);

            if (verbose3) bsl::cout << "+=(Decimal64)" << bsl::endl;
            d += BDLDFP_DECIMAL_DD(3.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(23.0) == d);

            if (verbose3) bsl::cout << "+=(Decimal128)" << bsl::endl;
            d += BDLDFP_DECIMAL_DL(9.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(32.0) == d);
        }

        if (verbose2) bsl::cout << "-=" << bsl::endl;
        {
            BDEC::Decimal64 d(BDLDFP_DECIMAL_DD(-5.0));

            if (verbose3) bsl::cout << "-=(int)" << bsl::endl;
            d -= 1;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-6.0) == d);

            if (verbose3) bsl::cout << "-=(unsigned int)" << bsl::endl;
            d -= 2u;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-8.0) == d);

            if (verbose3) bsl::cout << "-=(long int)" << bsl::endl;
            d -= -10l;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(2.0) == d);

            if (verbose3) bsl::cout << "-=(unsigned long int)" << bsl::endl;
            d -= 10ul;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-8.0) == d);

            if (verbose3) bsl::cout << "-=(long long int)" << bsl::endl;
            d -= -8ll;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(0.0) == d);

            if (verbose3) bsl::cout << "-=(unsigned long long int)"
                                    << bsl::endl;
            d -= 42ull;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-42.0) == d);

            if (verbose3) bsl::cout << "-=(Decimal32)" << bsl::endl;
            d -= BDLDFP_DECIMAL_DF(-22.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-20.0) == d);

            if (verbose3) bsl::cout << "-=(Decimal64)" << bsl::endl;
            d -= BDLDFP_DECIMAL_DD(3.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-23.0) == d);

            if (verbose3) bsl::cout << "-=(Decimal128)" << bsl::endl;
            d -= BDLDFP_DECIMAL_DL(9.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-32.0) == d);
        }

        if (verbose2) bsl::cout << "*=" << bsl::endl;
        {
            BDEC::Decimal64 d(BDLDFP_DECIMAL_DD(-5.0));

            if (verbose3) bsl::cout << "*=(int)" << bsl::endl;
            d *= -2;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(10.0) == d);

            if (verbose3) bsl::cout << "*=(unsigned int)" << bsl::endl;
            d *= 2000u;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(20000.0) == d);

            if (verbose3) bsl::cout << "*=(long int)" << bsl::endl;
            d *= -10l;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-200000.0) == d);

            if (verbose3) bsl::cout << "*=(unsigned long int)" << bsl::endl;
            d *= 3ul;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-600000.0) == d);

            if (verbose3) bsl::cout << "*=(long long int)" << bsl::endl;
            d *= -1ll;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(600000.0) == d);

            if (verbose3) bsl::cout << "*=(unsigned long long int)"
                                    << bsl::endl;
            d *= 5ull;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(3000000.0) == d);

            if (verbose3) bsl::cout << "*=(Decimal32)" << bsl::endl;
            d *= BDLDFP_DECIMAL_DF(1e-5);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(30.0) == d);

            if (verbose3) bsl::cout << "*=(Decimal64)" << bsl::endl;
            d *= BDLDFP_DECIMAL_DD(-3.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-90.0) == d);

            if (verbose3) bsl::cout << "*=(Decimal128)" << bsl::endl;
            d *= BDLDFP_DECIMAL_DL(2.4e-134);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-2.16e-132) == d);
        }

        if (verbose2) bsl::cout << "/=" << bsl::endl;
        {
            BDEC::Decimal64 d(BDLDFP_DECIMAL_DD(-5.0));

            if (verbose3) bsl::cout << "/=(int)" << bsl::endl;
            d /= -2;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(2.5) == d);

            if (verbose3) bsl::cout << "/=(unsigned int)" << bsl::endl;
            d /= 2000u;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(0.00125) == d);

            if (verbose3) bsl::cout << "/=(long int)" << bsl::endl;
            d /= -10l;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-0.000125) == d);

            if (verbose3) bsl::cout << "/=(unsigned long int)" << bsl::endl;
            d /= 5ul;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-0.000025) == d);

            if (verbose3) bsl::cout << "/=(long long int)" << bsl::endl;
            d /= -5ll;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(0.000005) == d);

            if (verbose3) bsl::cout << "/=(unsigned long long int)"
                                    << bsl::endl;
            d /= 5ull;
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(0.000001) == d);

            if (verbose3) bsl::cout << "/=(Decimal32)" << bsl::endl;
            d /= BDLDFP_DECIMAL_DF(1e-5);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(0.1) == d);

            if (verbose3) bsl::cout << "/=(Decimal64)" << bsl::endl;
            d /= BDLDFP_DECIMAL_DD(-5.0);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(-0.02) == d);

            if (verbose3) bsl::cout << "/=(Decimal128)" << bsl::endl;
            d /= BDLDFP_DECIMAL_DL(-2.5e-134);
            LOOP_ASSERT(d, BDLDFP_DECIMAL_DD(8.e131) == d);
        }

        if (verbose2) bsl::cout << "operator+" << bsl::endl;
        {
            BDEC::Decimal64 d(BDLDFP_DECIMAL_DD(-5.0));

            if (verbose3) bsl::cout << "dec + int" << bsl::endl;
            LOOP_ASSERT(d + 1, d + 1 == BDLDFP_DECIMAL_DD(-4.0));
            LOOP_ASSERT(1 + d, 1 + d == BDLDFP_DECIMAL_DD(-4.0));

            if (verbose3) bsl::cout << "dec + unsigned int" << bsl::endl;
            LOOP_ASSERT(d + 10u, d + 10u == BDLDFP_DECIMAL_DD(5.0));
            LOOP_ASSERT(10u + d, 10u + d == BDLDFP_DECIMAL_DD(5.0));

            if (verbose3) bsl::cout << "dec + long int" << bsl::endl;
            LOOP_ASSERT(d + 1l, d + 1l == BDLDFP_DECIMAL_DD(-4.0));
            LOOP_ASSERT(1l + d, 1l + d == BDLDFP_DECIMAL_DD(-4.0));

            if (verbose3) bsl::cout << "dec + unsigned long int" << bsl::endl;
            LOOP_ASSERT(d + 10ul, d + 10ul == BDLDFP_DECIMAL_DD(5.0));
            LOOP_ASSERT(10ul + d, 10ul + d == BDLDFP_DECIMAL_DD(5.0));

            if (verbose3) bsl::cout << "dec + long long int" << bsl::endl;
            LOOP_ASSERT(d + 1ll, d + 1ll == BDLDFP_DECIMAL_DD(-4.0));
            LOOP_ASSERT(1ll + d, 1ll + d == BDLDFP_DECIMAL_DD(-4.0));

            if (verbose3) bsl::cout << "dec + unsigned long long int"
                                    << bsl::endl;
            LOOP_ASSERT(d + 10ull, d + 10ull == BDLDFP_DECIMAL_DD(5.0));
            LOOP_ASSERT(10ull + d, 10ull + d == BDLDFP_DECIMAL_DD(5.0));

            if (verbose3) bsl::cout << "dec + dec64" << bsl::endl;
            LOOP_ASSERT(d + BDLDFP_DECIMAL_DD(-3.0),
                        d + BDLDFP_DECIMAL_DD(-3.0) ==
                        BDLDFP_DECIMAL_DD(-8.0));

            if (verbose3) bsl::cout << "dec + dec32" << bsl::endl;
            LOOP_ASSERT(d + BDLDFP_DECIMAL_DF(-3.0),
                        d + BDLDFP_DECIMAL_DF(-3.0) ==
                        BDLDFP_DECIMAL_DD(-8.0));
            LOOP_ASSERT(BDLDFP_DECIMAL_DF(-3.0) + d,
                        BDLDFP_DECIMAL_DF(-3.0) + d ==
                        BDLDFP_DECIMAL_DD(-8.0));
        }

        if (verbose2) bsl::cout << "operator-" << bsl::endl;
        {
            BDEC::Decimal64 d(BDLDFP_DECIMAL_DD(-5.0));

            if (verbose3) bsl::cout << "dec - int" << bsl::endl;
            LOOP_ASSERT(d - 1, d - 1 == BDLDFP_DECIMAL_DD(-6.0));
            LOOP_ASSERT(1 - d, 1 - d == BDLDFP_DECIMAL_DD( 6.0));

            if (verbose3) bsl::cout << "dec - unsigned int" << bsl::endl;
            LOOP_ASSERT(d - 10u, d - 10u == BDLDFP_DECIMAL_DD(-15.0));
            LOOP_ASSERT(10u - d, 10u - d == BDLDFP_DECIMAL_DD( 15.0));

            if (verbose3) bsl::cout << "dec - long int" << bsl::endl;
            LOOP_ASSERT(d - 1l, d - 1l == BDLDFP_DECIMAL_DD(-6.0));
            LOOP_ASSERT(1l - d, 1l - d == BDLDFP_DECIMAL_DD( 6.0));

            if (verbose3) bsl::cout << "dec - unsigned long int" << bsl::endl;
            LOOP_ASSERT(d - 10ul, d - 10ul == BDLDFP_DECIMAL_DD(-15.0));
            LOOP_ASSERT(10ul - d, 10ul - d == BDLDFP_DECIMAL_DD( 15.0));

            if (verbose3) bsl::cout << "dec - long long int" << bsl::endl;
            LOOP_ASSERT(d - 1ll, d - 1ll == BDLDFP_DECIMAL_DD(-6.0));
            LOOP_ASSERT(1ll - d, 1ll - d == BDLDFP_DECIMAL_DD( 6.0));

            if (verbose3) bsl::cout << "dec - unsigned long long int"
                                    << bsl::endl;
            LOOP_ASSERT(d - 10ull, d - 10ull == BDLDFP_DECIMAL_DD(-15.0));
            LOOP_ASSERT(10ull - d, 10ull - d == BDLDFP_DECIMAL_DD( 15.0));

            if (verbose3) bsl::cout << "dec - dec64" << bsl::endl;
            LOOP_ASSERT(d - BDLDFP_DECIMAL_DD(-3.0),
                        d - BDLDFP_DECIMAL_DD(-3.0) ==
                        BDLDFP_DECIMAL_DD(-2.0));

            if (verbose3) bsl::cout << "dec - dec32" << bsl::endl;
            LOOP_ASSERT(d - BDLDFP_DECIMAL_DF(-3.0),
                        d - BDLDFP_DECIMAL_DF(-3.0) ==
                        BDLDFP_DECIMAL_DD(-2.0));
            LOOP_ASSERT(BDLDFP_DECIMAL_DF(-3.0) - d,
                        BDLDFP_DECIMAL_DF(-3.0) - d ==
                        BDLDFP_DECIMAL_DD( 2.0));
        }

        if (verbose2) bsl::cout << "operator*" << bsl::endl;
        {
            BDEC::Decimal64 d(BDLDFP_DECIMAL_DD(-5.0));

            if (verbose3) bsl::cout << "dec * int" << bsl::endl;
            LOOP_ASSERT(d * -2, d * -2 == BDLDFP_DECIMAL_DD(10.0));
            LOOP_ASSERT(-2 * d, -2 * d == BDLDFP_DECIMAL_DD(10.0));

            if (verbose3) bsl::cout << "dec * unsigned int" << bsl::endl;
            LOOP_ASSERT(d * 10u, d * 10u == BDLDFP_DECIMAL_DD(-50.0));
            LOOP_ASSERT(10u * d, 10u * d == BDLDFP_DECIMAL_DD(-50.0));

            if (verbose3) bsl::cout << "dec * long int" << bsl::endl;
            LOOP_ASSERT(d * -2l, d * -2l == BDLDFP_DECIMAL_DD(10.0));
            LOOP_ASSERT(-2l * d, -2l * d == BDLDFP_DECIMAL_DD(10.0));

            if (verbose3) bsl::cout << "dec * unsigned long int" << bsl::endl;
            LOOP_ASSERT(d * 10ul, d * 10ul == BDLDFP_DECIMAL_DD(-50.0));
            LOOP_ASSERT(10ul * d, 10ul * d == BDLDFP_DECIMAL_DD(-50.0));

            if (verbose3) bsl::cout << "dec * long long int" << bsl::endl;
            LOOP_ASSERT(d * -2ll, d * -2ll == BDLDFP_DECIMAL_DD(10.0));
            LOOP_ASSERT(-2ll * d, -2ll * d == BDLDFP_DECIMAL_DD(10.0));

            if (verbose3) bsl::cout << "dec * unsigned long long int"
                                    << bsl::endl;
            LOOP_ASSERT(d * 10ull, d * 10ull == BDLDFP_DECIMAL_DD(-50.0));
            LOOP_ASSERT(10ull * d, 10ull * d == BDLDFP_DECIMAL_DD(-50.0));

            if (verbose3) bsl::cout << "dec * dec64" << bsl::endl;
            LOOP_ASSERT(d * BDLDFP_DECIMAL_DD(-3.0),
                        d * BDLDFP_DECIMAL_DD(-3.0) ==
                        BDLDFP_DECIMAL_DD(15.0));

            if (verbose3) bsl::cout << "dec * dec32" << bsl::endl;
            LOOP_ASSERT(d * BDLDFP_DECIMAL_DF(-3.0),
                        d * BDLDFP_DECIMAL_DF(-3.0) ==
                        BDLDFP_DECIMAL_DD(15.0));
            LOOP_ASSERT(BDLDFP_DECIMAL_DF(-3.0) * d,
                        BDLDFP_DECIMAL_DF(-3.0) * d ==
                        BDLDFP_DECIMAL_DD(15.0));
        }

        if (verbose2) bsl::cout << "operator/" << bsl::endl;
        {
            BDEC::Decimal64 d(BDLDFP_DECIMAL_DD(-5.0));

            if (verbose3) bsl::cout << "dec / int" << bsl::endl;
            LOOP_ASSERT(d / -2, d / -2 == BDLDFP_DECIMAL_DD(2.5));
            LOOP_ASSERT(-2 / d, -2 / d == BDLDFP_DECIMAL_DD(0.4));

            if (verbose3) bsl::cout << "dec / unsigned int" << bsl::endl;
            LOOP_ASSERT(d / 100u, d / 100u == BDLDFP_DECIMAL_DD( -0.05));
            LOOP_ASSERT(100u / d, 100u / d == BDLDFP_DECIMAL_DD(-20.0));

            if (verbose3) bsl::cout << "dec / long int" << bsl::endl;
            LOOP_ASSERT(d / -2l, d / -2l == BDLDFP_DECIMAL_DD(2.5));
            LOOP_ASSERT(-2l / d, -2l / d == BDLDFP_DECIMAL_DD(0.4));

            if (verbose3) bsl::cout << "dec / unsigned long int" << bsl::endl;
            LOOP_ASSERT(d / 100ul, d / 100ul == BDLDFP_DECIMAL_DD( -0.05));
            LOOP_ASSERT(100ul / d, 100ul / d == BDLDFP_DECIMAL_DD(-20.0));

            if (verbose3) bsl::cout << "dec / long long int" << bsl::endl;
            LOOP_ASSERT(d / -2ll, d / -2ll == BDLDFP_DECIMAL_DD(2.5));
            LOOP_ASSERT(-2ll / d, -2ll / d == BDLDFP_DECIMAL_DD(0.4));

            if (verbose3) bsl::cout << "dec / unsigned long long int"
                                    << bsl::endl;
            LOOP_ASSERT(d / 100ull, d / 100ull == BDLDFP_DECIMAL_DD( -0.05));
            LOOP_ASSERT(100ull / d, 100ull / d == BDLDFP_DECIMAL_DD(-20.0));

            if (verbose3) bsl::cout << "dec / dec64" << bsl::endl;
            LOOP_ASSERT(d / BDLDFP_DECIMAL_DD(-50.0),
                        d / BDLDFP_DECIMAL_DD(-50.0) ==
                        BDLDFP_DECIMAL_DD(0.1));

            if (verbose3) bsl::cout << "dec / dec32" << bsl::endl;
            LOOP_ASSERT(d / BDLDFP_DECIMAL_DF(-50.0),
                        d / BDLDFP_DECIMAL_DF(-50.0) ==
                        BDLDFP_DECIMAL_DD(0.1));
            LOOP_ASSERT(BDLDFP_DECIMAL_DF(-50.0) / d,
                        BDLDFP_DECIMAL_DF(-50.0) / d ==
                        BDLDFP_DECIMAL_DD(10.0));
        }

        if (verbose2) bsl::cout << "Create test objects" << bsl::endl;

        BDEC::Decimal32        d32  = BDEC::Decimal32();
        const BDEC::Decimal32  c32  = BDEC::Decimal32();
        BDEC::Decimal64        d64  = BDEC::Decimal64();
        const BDEC::Decimal64  c64  = BDEC::Decimal64();
        BDEC::Decimal128       d128 = BDEC::Decimal128();
        const BDEC::Decimal128 c128 = BDEC::Decimal128();

        if (verbose2) bsl::cout << "Check return types" << bsl::endl;

        checkType<BDEC::Decimal64&>(++d64);
        checkType<BDEC::Decimal64>(d64++);
        checkType<BDEC::Decimal64&>(--d64);
        checkType<BDEC::Decimal64>(d64--);
        checkType<BDEC::Decimal64&>(d64 += static_cast<char>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<unsigned char>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<signed char>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<short>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<unsigned short>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<int>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<unsigned int>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<long>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<unsigned long>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<long long>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<unsigned long long>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<BDEC::Decimal32>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<BDEC::Decimal64>(1));
        checkType<BDEC::Decimal64&>(d64 += static_cast<BDEC::Decimal128>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<char>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<unsigned char>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<signed char>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<short>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<unsigned short>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<int>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<unsigned int>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<long>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<unsigned long>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<long long>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<unsigned long long>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<BDEC::Decimal32>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<BDEC::Decimal64>(1));
        checkType<BDEC::Decimal64&>(d64 -= static_cast<BDEC::Decimal128>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<char>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<unsigned char>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<signed char>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<short>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<unsigned short>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<int>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<unsigned int>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<long>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<unsigned long>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<long long>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<unsigned long long>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<BDEC::Decimal32>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<BDEC::Decimal64>(1));
        checkType<BDEC::Decimal64&>(d64 *= static_cast<BDEC::Decimal128>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<char>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<unsigned char>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<signed char>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<short>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<unsigned short>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<int>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<unsigned int>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<long>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<unsigned long>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<long long>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<unsigned long long>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<BDEC::Decimal32>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<BDEC::Decimal64>(1));
        checkType<BDEC::Decimal64&>(d64 /= static_cast<BDEC::Decimal128>(1));

        checkType<BDEC::Decimal64>(+d64);
        checkType<BDEC::Decimal64>(-d64);

        checkType<BDEC::Decimal64>(d64 + d64);
        checkType<BDEC::Decimal64>(d64 - d64);
        checkType<BDEC::Decimal64>(d64 * d64);
        checkType<BDEC::Decimal64>(d64 / d64);
        checkType<bool>(d64 == d64);
        checkType<bool>(d32 == d64);
        checkType<bool>(d64 == d32);
        checkType<bool>(d64 != d64);
        checkType<bool>(d32 != d64);
        checkType<bool>(d64 != d32);
        checkType<bool>(d64 < d64);
        checkType<bool>(d32 < d64);
        checkType<bool>(d64 < d32);
        checkType<bool>(d64 <= d64);
        checkType<bool>(d32 <= d64);
        checkType<bool>(d64 <= d32);
        checkType<bool>(d64 > d64);
        checkType<bool>(d32 > d64);
        checkType<bool>(d64 > d32);
        checkType<bool>(d64 >= d64);
        checkType<bool>(d32 >= d64);
        checkType<bool>(d64 >= d32);

        {
            bsl::istringstream  in(pa);
            bsl::wistringstream win(pa);
            bsl::ostringstream  out(pa);
            bsl::wostringstream wout(pa);

            checkType<bsl::istream&>(in >> d64);
            checkType<bsl::wistream&>(win >> d64);
            checkType<bsl::ostream&>(out << c64);
            checkType<bsl::wostream&>(wout << c64);
        }

        typedef bsl::numeric_limits<BDEC::Decimal64> d64_limits;
        checkType<bool>(d64_limits::is_specialized);
        checkType<BDEC::Decimal64>(d64_limits::min());
        checkType<BDEC::Decimal64>(d64_limits::max());
        checkType<int>(d64_limits::digits);
        checkType<int>(d64_limits::digits10);
        checkType<int>(d64_limits::max_digits10);
        checkType<bool>(d64_limits::is_signed);
        checkType<bool>(d64_limits::is_integer);
        checkType<bool>(d64_limits::is_exact);
        checkType<int>(d64_limits::radix);
        checkType<BDEC::Decimal64>(d64_limits::epsilon());
        checkType<BDEC::Decimal64>(d64_limits::round_error());
        checkType<int>(d64_limits::min_exponent);
        checkType<int>(d64_limits::min_exponent10);
        checkType<int>(d64_limits::max_exponent);
        checkType<int>(d64_limits::max_exponent10);
        checkType<bool>(d64_limits::has_infinity);
        checkType<bool>(d64_limits::has_quiet_NaN);
        checkType<bool>(d64_limits::has_signaling_NaN);
        checkType<bsl::float_denorm_style>(d64_limits::has_denorm);
        checkType<bool>(d64_limits::has_denorm_loss);
        checkType<BDEC::Decimal64>(d64_limits::infinity());
        checkType<BDEC::Decimal64>(d64_limits::quiet_NaN());
        checkType<BDEC::Decimal64>(d64_limits::signaling_NaN());
        checkType<BDEC::Decimal64>(d64_limits::denorm_min());
        checkType<bool>(d64_limits::is_iec559);
        checkType<bool>(d64_limits::is_bounded);
        checkType<bool>(d64_limits::is_modulo);
        checkType<bool>(d64_limits::traps);
        checkType<bool>(d64_limits::tinyness_before);
        checkType<bsl::float_round_style>(d64_limits::round_style);
      } break;

    case 2: {
        // --------------------------------------------------------------------
        // TESTING 'Decimal32'
        //   Ensure that 'Decimal32' functions correctly
        //
        // Concerns:
        //: 1 'Decimal32' operations are properly forwarded to implementation
        //: 2 All possible operand combinations work correctly.
        //
        // Plan:
        //: 1 Expected value testing will be used.
        //:
        //: 2 All forms of LHS and RHS combinations for all free operators will
        //:   be tested.
        //:
        //: 3 Every member operator will be tested
        //
        // Testing:
        //   'class Decimal32'
        // --------------------------------------------------------------------
        if (verbose1) bsl::cout << "\nTesting class Decimal32"
                                << "\n=======================" << bsl::endl;

        if (verbose2) bsl::cout << "Constructors" << bsl::endl;

        if (verbose3) bsl::cout << "Copy/convert" << bsl::endl;
        {
            const BDEC::Decimal32  c32  = BDEC::Decimal32(32);
            const BDEC::Decimal64  c64  = BDEC::Decimal64(64);
            const BDEC::Decimal128 c128 = BDEC::Decimal128(128);

            ASSERT(BDLDFP_DECIMAL_DF( 32.0) == BDEC::Decimal32(c32));
            ASSERT(BDLDFP_DECIMAL_DF( 64.0) == BDEC::Decimal32(c64));
            // TODO: Conversions from Decimal128 to Decimal32.
            // ASSERT(BDLDFP_DECIMAL_DF(128.0) == BDEC::Decimal32(c128));
        }

        if (verbose3) bsl::cout << "Integral" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DF(  0.0) == BDEC::Decimal32());  // default
        ASSERT(BDLDFP_DECIMAL_DF(-42.0) == BDEC::Decimal32(-42)); // int
        ASSERT(BDLDFP_DECIMAL_DF( 42.0) == BDEC::Decimal32(42u)); // unsigned
        ASSERT(BDLDFP_DECIMAL_DF(-42.0) == BDEC::Decimal32(-42l)); // long
        ASSERT(BDLDFP_DECIMAL_DF( 42.0) == BDEC::Decimal32(42ul)); // ulong
        ASSERT(BDLDFP_DECIMAL_DF(-42.0) == BDEC::Decimal32(-42ll)); // longlong
        ASSERT(BDLDFP_DECIMAL_DF( 42.0) == BDEC::Decimal32(42ull)); // ulongl

        if (verbose3) bsl::cout << "Binary FP" << bsl::endl;

        // Note that to test binary-float taking constructors I use numbers
        // that can be represented exactly in both binary and decimal FP.

        ASSERT(BDLDFP_DECIMAL_DF(4.25) == BDEC::Decimal32(4.25f)); // float
        ASSERT(BDLDFP_DECIMAL_DF(4.25) == BDEC::Decimal32(4.25)); // double

        if (verbose3) bsl::cout << "Decimal FP" << bsl::endl;

        // Decimal64
        ASSERT(BDLDFP_DECIMAL_DF(-42.0) == BDLDFP_DECIMAL_DD(-42.0));
        ASSERT(BDLDFP_DECIMAL_DF(42.0) == BDLDFP_DECIMAL_DD(42.0));
        ASSERT(BDLDFP_DECIMAL_DF(4.2) == BDLDFP_DECIMAL_DD(4.2));
        ASSERT(BDLDFP_DECIMAL_DF(4.2e9) == BDLDFP_DECIMAL_DD(4.2e9));

        // Dec128
        ASSERT(BDLDFP_DECIMAL_DF(-42.0) == BDLDFP_DECIMAL_DL(-42.0));
        ASSERT(BDLDFP_DECIMAL_DF(42.0) == BDLDFP_DECIMAL_DL(42.0));
        ASSERT(BDLDFP_DECIMAL_DF(4.2) == BDLDFP_DECIMAL_DL(4.2));
        ASSERT(BDLDFP_DECIMAL_DF(4.2e9) == BDLDFP_DECIMAL_DL(4.2e9));

        if (verbose2) bsl::cout << "Propriatery accessors" << bsl::endl;
        {
            BDEC::Decimal32 d32(42);
            ASSERT((void*)d32.data() == (void*)&d32);

            const BDEC::Decimal32 cd32(42);
            ASSERT((const void*)d32.data() == (const void*)&d32);

            ASSERT(BDEC::Decimal32(cd32.value()) == BDEC::Decimal32(42));
        }

        if (verbose2) bsl::cout << "Operator==" << bsl::endl;

        ASSERT(! (BDLDFP_DECIMAL_DF(4.0) == BDLDFP_DECIMAL_DF(5.0)));
        ASSERT(BDLDFP_DECIMAL_DF(-9.345e27) == BDLDFP_DECIMAL_DF(-9.345e27));

        if (verbose2) bsl::cout << "Operator!=" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DF(4.0) != BDLDFP_DECIMAL_DF(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DF(-9.345e27) !=
                  BDLDFP_DECIMAL_DF(-9.345e27)));

        if (verbose2) bsl::cout << "Operator<" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DF(4.0) <
               BDLDFP_DECIMAL_DF(5.0));
        ASSERT(! (BDLDFP_DECIMAL_DF(-9.345e27) <
                  BDLDFP_DECIMAL_DF(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DF(5.0) < BDLDFP_DECIMAL_DF(4.0)));

        if (verbose2) bsl::cout << "Operator>" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DF(5.0) > BDLDFP_DECIMAL_DF(4.0));
        ASSERT(! (BDLDFP_DECIMAL_DF(-9.345e27) >
                  BDLDFP_DECIMAL_DF(-9.345e27)));
        ASSERT(! (BDLDFP_DECIMAL_DF(4.0) > BDLDFP_DECIMAL_DF(5.0)));

        if (verbose2) bsl::cout << "Operator<=" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DF(4.0) <= BDLDFP_DECIMAL_DF(5.0));
        ASSERT(BDLDFP_DECIMAL_DF(-9.345e27) <= BDLDFP_DECIMAL_DF(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DF(5.0) <= BDLDFP_DECIMAL_DF(4.0)));

        if (verbose2) bsl::cout << "Operator>=" << bsl::endl;

        ASSERT(BDLDFP_DECIMAL_DF(5.0) >= BDLDFP_DECIMAL_DF(4.0));
        ASSERT(BDLDFP_DECIMAL_DF(-9.345e27) >= BDLDFP_DECIMAL_DF(-9.345e27));
        ASSERT(! (BDLDFP_DECIMAL_DF(4.0) >= BDLDFP_DECIMAL_DF(5.0)));

        // TODO TBD: Note that I am testing with the maximum number of
        // significant digits and I actually expect stream output to do no
        // rounding.  That is wrong (see later why), but necessary to
        // remote-test the 'format' function and make sure it does not lose
        // digits or does some unwanted rounding.  When 'format' will be in the
        // lower utility, it will be tested directly.
        // Expecting to see all digits is wrong because that is not how the
        // stream output should behave: it should print with the default
        // precision as it would for binary floating point *or* with the
        // implied precision of the cohort if that is larger.  AFAIU

        if (verbose2) bsl::cout << "Test stream out" << bsl::endl;
        {
            bsl::ostringstream out(pa);

            BDEC::Decimal32 d1(BDLDFP_DECIMAL_DF(-8.327457e-24));
            out << d1;
            bsl::string s(pa);
            getStringFromStream(out, &s);
            ASSERT(decLower(s) == "-8.327457e-24");
        }

        if (verbose2) bsl::cout << "Test stream in" << bsl::endl;
        {
            bsl::istringstream in(pa);
            bsl::string ins("-8.327457e-24", pa);
            in.str(ins);

            BDEC::Decimal32 d1;
            in >> d1;
            ASSERT(d1 == BDLDFP_DECIMAL_DF(-8.327457e-24));
        }

        if (verbose2) bsl::cout << "Test wide stream out" << bsl::endl;
        {
            bsl::wostringstream  out(pa);
            BDEC::Decimal32 d1(BDLDFP_DECIMAL_DF(-8.327457e-24));
            out << d1;
            bsl::wstring s(pa);
            getStringFromStream(out, &s);
            ASSERT(decLower(s) == L"-8.327457e-24");
        }

        if (verbose2) bsl::cout << "Test wide stream in" << bsl::endl;
        {
            bsl::wistringstream  in(pa);
            bsl::wstring ins(L"-8.327457e-24", pa);
            in.str(ins);

            BDEC::Decimal32 d1;
            in >> d1;
            ASSERT(d1 == BDLDFP_DECIMAL_DF(-8.327457e-24));
        }

        if (verbose2) bsl::cout << "Unary-" << bsl::endl;
        {
            BDEC::Decimal32 d1(BDLDFP_DECIMAL_DF(-5.0));
            BDEC::Decimal32 d2(BDLDFP_DECIMAL_DF( 5.0));
            ASSERT(BDLDFP_DECIMAL_DF( 5.0) == -d1);
            ASSERT(BDLDFP_DECIMAL_DF(-5.0) == -d2);

            // Unary - must make +0 into -0

            bsl::ostringstream out(pa);
            out << -BDLDFP_DECIMAL_DF(0.0);
            bsl::string s(pa);
            getStringFromStream(out, &s);
            LOOP_ASSERT(s, s[0] == '-'); // it is negative
            ASSERT(-BDLDFP_DECIMAL_DF(0.0) == BDEC::Decimal32(0)) // and 0
        }

        if (verbose2) bsl::cout << "Unary+" << bsl::endl;
        {
            BDEC::Decimal32 d1(BDLDFP_DECIMAL_DF(-5.0));
            BDEC::Decimal32 d2(BDLDFP_DECIMAL_DF( 5.0));
            ASSERT(BDLDFP_DECIMAL_DF(-5.0) == +d1);
            ASSERT(BDLDFP_DECIMAL_DF( 5.0) == +d2);

            // Unary + must make -0 into +0

            BDEC::Decimal128 negzero(-BDLDFP_DECIMAL_DF(0.0));
            bsl::ostringstream out(pa);
            out << +negzero;
            bsl::string s(pa);
            getStringFromStream(out, &s);
            LOOP_ASSERT(s, s[0] != '+'); // it is positive
            ASSERT(-BDLDFP_DECIMAL_DF(0.0) == BDEC::Decimal32(0)) // and 0
        }


        if (verbose2) bsl::cout << "Create test objects" << bsl::endl;

        BDEC::Decimal32        d32  = BDEC::Decimal32();
        const BDEC::Decimal32  c32  = BDEC::Decimal32();
        BDEC::Decimal64        d64  = BDEC::Decimal64();
        const BDEC::Decimal64  c64  = BDEC::Decimal64();
        BDEC::Decimal128       d128 = BDEC::Decimal128();
        const BDEC::Decimal128 c128 = BDEC::Decimal128();

        if (verbose2) bsl::cout << "Check return types" << bsl::endl;

        checkType<bool>(d32 == d32);
        checkType<bool>(d32 != d32);
        checkType<bool>(d32 < d32);
        checkType<bool>(d32 <= d32);
        checkType<bool>(d32 > d32);
        checkType<bool>(d32 >= d32);

        checkType<BDEC::Decimal32>(+d32);
        checkType<BDEC::Decimal32>(-d32);

        {
            bsl::istringstream  in(pa);
            bsl::ostringstream  out(pa);
            bsl::wistringstream win(pa);
            bsl::wostringstream wout(pa);

            checkType<bsl::istream&>(in >> d32);
            checkType<bsl::wistream&>(win >> d32);
            checkType<bsl::ostream&>(out << c32);
            checkType<bsl::wostream&>(wout << c32);
        }

        typedef bsl::numeric_limits<BDEC::Decimal32> d32_limits;
        checkType<bool>(d32_limits::is_specialized);
        checkType<BDEC::Decimal32>(d32_limits::min());
        checkType<BDEC::Decimal32>(d32_limits::max());
        checkType<int>(d32_limits::digits);
        checkType<int>(d32_limits::digits10);
        checkType<int>(d32_limits::max_digits10);
        checkType<bool>(d32_limits::is_signed);
        checkType<bool>(d32_limits::is_integer);
        checkType<bool>(d32_limits::is_exact);
        checkType<int>(d32_limits::radix);
        checkType<BDEC::Decimal32>(d32_limits::epsilon());
        checkType<BDEC::Decimal32>(d32_limits::round_error());
        checkType<int>(d32_limits::min_exponent);
        checkType<int>(d32_limits::min_exponent10);
        checkType<int>(d32_limits::max_exponent);
        checkType<int>(d32_limits::max_exponent10);
        checkType<bool>(d32_limits::has_infinity);
        checkType<bool>(d32_limits::has_quiet_NaN);
        checkType<bool>(d32_limits::has_signaling_NaN);
        checkType<bsl::float_denorm_style>(d32_limits::has_denorm);
        checkType<bool>(d32_limits::has_denorm_loss);
        checkType<BDEC::Decimal32>(d32_limits::infinity());
        checkType<BDEC::Decimal32>(d32_limits::quiet_NaN());
        checkType<BDEC::Decimal32>(d32_limits::signaling_NaN());
        checkType<BDEC::Decimal32>(d32_limits::denorm_min());
        checkType<bool>(d32_limits::is_iec559);
        checkType<bool>(d32_limits::is_bounded);
        checkType<bool>(d32_limits::is_modulo);
        checkType<bool>(d32_limits::traps);
        checkType<bool>(d32_limits::tinyness_before);
        checkType<bsl::float_round_style>(d32_limits::round_style);
      } break;

    case 1: {
        // --------------------------------------------------------------------
        // TESTING Implementation configuration
        //   Ensure that the implementation is configured properly
        //
        // Concerns:
        //: 1 The implementation is setup properly.
        //: 2 The endianness of the implementation is correct.
        //: 3 The number of bits in a char must be 8.
        //
        // Plan:
        //: 1 Individual assertions for each compile-time configuration choice.
        // --------------------------------------------------------------------
        if (verbose1) bsl::cout << "\nTesting Implementation Configuration"
                                << "\n===================================="
                                << bsl::endl;
        #if BDLDFP_DECIMALPLATFORM_DECNUMBER
            LOOP_ASSERT(decContextTestEndian(1), 0 == decContextTestEndian(1));
        #endif

        ASSERT(8 == CHAR_BIT);

        ASSERT(sizeof(BDEC::Decimal32) == (32 / CHAR_BIT));
        ASSERT(sizeof(BDEC::Decimal64) == (64 / CHAR_BIT));
        ASSERT(sizeof(BDEC::Decimal128) == (128 / CHAR_BIT));

        // Making sure our buffers are large enough for snprintf
        {

            // Let's make sure we have the right values.  We have to use
            // numeric_limits, because IBM does not provide the standard C
            // xxx_MIN/xxx_MAX macros for long long types.

            ASSERT(bsl::numeric_limits<long long>::is_specialized);
            ASSERT(bsl::numeric_limits<unsigned long long>::is_specialized);

            NulBuf nb; // Use this to make sure we can print
            bsl::ostream nul(&nb);

            // Make sure that printing in itself works.

            nul << bsl::numeric_limits<long long>::min();
            ASSERT(nul);
            nul << bsl::numeric_limits<long long>::max();
            ASSERT(nul);
            nul << bsl::numeric_limits<unsigned long long>::max();
            ASSERT(nul);

            // And here comes the real testing

            BufferBuf<24> bb;
            bsl::ostream out(&bb);

            out << bsl::numeric_limits<long long>::min();
            ASSERT(out && strlen(bb.str()) < (24 - 1));
            out.clear(); bb.reset();

            out << bsl::numeric_limits<long long>::max();
            ASSERT(out && strlen(bb.str()) < (24 - 1));
            out.clear(); bb.reset();

            out << bsl::numeric_limits<unsigned long long>::max();
            ASSERT(out && strlen(bb.str()) < (24 - 1));
            out.clear(); bb.reset();
        }

    } break;

    default: {
        cerr << "WARNING: CASE `" << test << "' NOT FOUND." << endl;
        testStatus = -1;
      }
    }

    // CONCERN: No memory came from the global or default allocator.

    LOOP2_ASSERT(test, globalAllocator.numBlocksTotal(),
                 0 == globalAllocator.numBlocksTotal());
    LOOP2_ASSERT(test, defaultAllocator.numBlocksTotal(),
                 0 == defaultAllocator.numBlocksTotal());

    if (testStatus > 0) {
        cerr << "Error, non-zero test status = " << testStatus << "." << endl;
    }

    return testStatus;
}

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Bloomberg L.P.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------- END-OF-FILE ----------------------------------