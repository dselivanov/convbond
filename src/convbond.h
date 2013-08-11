#include <Rcpp.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <vector>
#define DIVIDEND_AMOUNT_DIMENSION 1
#define DIVIDEND_DATE_DIMENSION 0
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#define EPSILON 1e-8
#define MAXITER 1000
#define TOLERANCE 1e-5
#define CB_PRICE_TARGET_COUPON_CALCULATION 1
#define TARGET_COUPON_START 0
#define TARGET_COUPON_END 0.5
using namespace Rcpp;

typedef struct convBondParam {
  double S_0;
  double sigma; 
	double intRate0;
	double creditSpread;
	double rateCompounding;
	double couponRate;
	double couponFreq;
	double dividendProtectionRate;
	std::vector< std::vector< double > > rngDividendSchedule;
	double conversionRatio;
	double noConversionPeriod;
	double americanConversionType;
	double maturity;
	double faceValue;
	double redemtionPremium;
	double barrierStartTime;
	double barrier;
	double barrierStrike;
	double putStartTime;
	double putStrike;
	double callStartTime;
	double callStrike;
	double nbStepsPerYear;
} convBondParam;

int *createIndex(int);
double prod(double*, int*, int);
double prod_with_cond(double*, int*, int, double);
double zeroin(double, double, double (*f)(double, convBondParam*),double, convBondParam*);

double CBprice(double S_0,
  double sigma, 
	double intRate0,
	double creditSpread,
	double rateCompounding,
	double couponRate,
	double couponFreq,
	double dividendProtectionRate,
	std::vector< std::vector< double > > rngDividendSchedule,
	double conversionRatio,
	double noConversionPeriod,
	double americanConversionType,
	double maturity,
	double faceValue,
	double redemtionPremium,
	double barrierStartTime,
	double barrier,
	double barrierStrike,
	double putStartTime,
	double putStrike,
	double callStartTime,
	double callStrike,
	double nbStepsPerYear);

convBondParam * init_convBondParam(
  double S_0,
	double sigma, 
	double intRate0,
	double creditSpread,
	double rateCompounding,
	double couponRate,
	double couponFreq,
	double dividendProtectionRate,
	std::vector< std::vector< double > > rngDividendSchedule,
	double conversionRatio,
	double noConversionPeriod,
	double americanConversionType,
	double maturity,
	double faceValue,
	double redemtionPremium,
	double barrierStartTime,
	double barrier,
	double barrierStrike,
	double putStartTime,
	double putStrike,
	double callStartTime,
	double callStrike,
	double nbStepsPerYear);
  
double tst(NumericMatrix m1);

double CBpriceWrapper_StructInput(double, convBondParam*);

double CBpriceR(
  double S_0,
  double sigma, 
  double intRate0,
  double creditSpread,
	double rateCompounding,
	double couponRate,
	double couponFreq,
	double dividendProtectionRate,
	NumericMatrix RDividendSchedule,
	double conversionRatio,
	double noConversionPeriod,
	double americanConversionType,
	double maturity,
	double faceValue,
	double redemtionPremium,
	double barrierStartTime,
	double barrier,
	double barrierStrike,
	double putStartTime,
	double putStrike,
	double callStartTime,
	double callStrike,
	double nbStepsPerYear);
  
double convBondFindCoupon(
  double S_0,
	double sigma, 
	double intRate0,
	double creditSpread,
	double rateCompounding,
	double couponFreq,
	double dividendProtectionRate,
	std::vector< std::vector< double > > rngDividendSchedule,		
	double conversionRatio,
	double noConversionPeriod,
	double americanConversionType,
	double maturity,
	double faceValue,
	double redemtionPremium,
	double barrierStartTime,
	double barrier,
	double barrierStrike,
	double putStartTime,
	double putStrike,
	double callStartTime,
	double callStrike,
	double nbStepsPerYear);
  
void NumericMatrix_to_vector2d(NumericMatrix Rmatrix, std::vector< std::vector< double > > &vec2d);