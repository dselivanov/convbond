#include "convbond.h"
// convert NumericMatrix to vector<vector<>>
void NumericMatrix_to_vector2d(NumericMatrix Rmatrix, std::vector< std::vector< double > > &vec2d)
{
  vec2d.resize(Rmatrix.nrow());
	for (int i = 0; i < Rmatrix.nnrow(); i++)
	{
		vec2d[i].resize(Rmatrix.ncol());
	}
	for (int i=0;i < Rmatrix.nrow(); i++)
	{
		for (int j=0;j < Rmatrix.ncol(); j++)
		{
			vec2d[i][j] = Rmatrix(i, j);
		}
	}
}
// [[Rcpp::export]]
double CBpriceR(double S_0,
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
	double softCallStartTime,
	double softCall,
	double softCallStrike,
	double putStartTime,
	double putStrike,
	double callStartTime,
	double callStrike,
	double nbStepsPerYear)
{
	std::vector< std::vector< double > > rngDividendSchedule;
	NumericMatrix_to_vector2d(RDividendSchedule, rngDividendSchedule);
	return CBprice(S_0, sigma, intRate0, creditSpread, rateCompounding, couponRate, couponFreq,
					dividendProtectionRate, rngDividendSchedule,conversionRatio,
					noConversionPeriod, americanConversionType, maturity, faceValue,
					redemtionPremium, softCallStartTime, softCall, softCallStrike,
					putStartTime, putStrike, callStartTime, callStrike,nbStepsPerYear);
	
}

// [[Rcpp::export]]
double convBondFindCouponR(
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
	double redemtionPremium,
	double softCallStartTime,
	double softCall,
	double softCallStrike,
	double putStartTime,
	double putStrike,
	double callStartTime,
	double callStrike,
	double nbStepsPerYear)
{
	std::vector< std::vector< double > > rngDividendSchedule;
	NumericMatrix_to_vector2d(RDividendSchedule, rngDividendSchedule);
	return(convBondFindCoupon(S_0, sigma, intRate0, creditSpread, rateCompounding, couponFreq,
								dividendProtectionRate, rngDividendSchedule,conversionRatio,
								noConversionPeriod, americanConversionType, maturity, faceValue,
								redemtionPremium, softCallStartTime, softCall, softCallStrike,
								putStartTime, putStrike, callStartTime, callStrike,nbStepsPerYear));
					
}