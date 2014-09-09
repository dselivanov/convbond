#include <Rcpp.h>
using namespace Rcpp;
double CBprice(
	double S_0,
	double sigma, 
	double intRate,
	double creditSpread,
	double rateCompounding,
	double couponRate,
	double couponFreq,
	double dividendProtectionRate,
	NumericMatrix dividendSchedule,
	double conversionRatio,
	double noConversionPeriod,
	double americanConversionType,
	double maturity,
	double faceValue,
	double redemptionPremium,
	double softCallStartTime,
	double softCall,
	double softCallStrike,
	double putStartTime,
	double putStrike,
	double callStartTime,
	double callStrike,
	double nbStepsPerYear);
	

double CBfindCoupon(
	double S_0,
	double sigma, 
	double intRate0,
	double creditSpread,
	double rateCompounding,
	double couponFreq,
	double dividendProtectionRate,
	NumericMatrix RDividendSchedule,
	double conversionRatio,
	double noConversionPeriod,
	double americanConversionType,
	double maturity,
	double faceValue,
	double redemptionPremium,
	double softCallStartTime,
	double softCallBarrier,
	double softCallStrike,
	double putStartTime,
	double putStrike,
	double callStartTime,
	double callStrike,
	double nbStepsPerYear,
  double targetBondPrice);

void NumericMatrixToVector2d(NumericMatrix Rmatrix, std::vector< std::vector< double > > &vec2d);
