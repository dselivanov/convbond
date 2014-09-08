#include "convbond.h"
// convert NumericMatrix to vector<vector<>>
void NumericMatrix_to_vector2d(NumericMatrix Rmatrix, std::vector< std::vector< double > > &vec2d)
{
  vec2d.resize(Rmatrix.nrow());
	for (int i = 0; i < Rmatrix.nrow(); i++)
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
//' Convertible bond pricing
//'
//' Returns price of convertible bond
//' @param S_0 underlying initial price
//' @param sigma annualised implied volatility of the underlying
//' @param riskFreeInterestRate risk free rate
//' @param creditSpread spread to risk free rate
//' @param rateCompounding basis for rates. annual=1, semi-annual=2, etc. For the continious basis use rateCompounding=0
//' @param couponRate coupon on bond
//' @param couponFreq numer of coupons per year. Usually twice a year.
//' @param dividendProtectionRate divident protection threshold. In the model we use dividend protection via adjustment to conversion rate (Dividend protection is almost always provided by an adjustment to the conversion price or conversion ratio).
//' @param RDividendSchedule dividend schedule 2-column matrix. 1-column - time to dividend, 2-column - dividend rate. See demos.
//' @param conversionRatio number of shares per one convertible bond
//' @param noConversionPeriod restriction for conversion in years.
//' @param americanConversionType type of the conversion option. In almost all cases it is american. So we can convert any time. Set =0 if conversion possible only at maturity.
//' @param maturity maturity of the convertible
//' @param faceValue nominal amount of convertible bond
//' @param redemptionPremium premium at conversion. For example if issuer can pay premium 10% of the faceValue at maturity to the holder (at redemtion). If so set parameter =0.1. In almost all cases there is no redemption premium.
//' 
//' @return price of the convertible
// [[Rcpp::export]]
double cbprice(double S_0,
	double sigma, 
	double riskFreeInterestRate,
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
	double redemptionPremium,
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
	return CBprice_cpp(S_0, sigma, riskFreeInterestRate, creditSpread, rateCompounding, couponRate, couponFreq,
					dividendProtectionRate, rngDividendSchedule,conversionRatio,
					noConversionPeriod, americanConversionType, maturity, faceValue,
					redemptionPremium, softCallStartTime, softCall, softCallStrike,
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
	double redemptionPremium,
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
								redemptionPremium, softCallStartTime, softCall, softCallStrike,
								putStartTime, putStrike, callStartTime, callStrike,nbStepsPerYear));
					
}
