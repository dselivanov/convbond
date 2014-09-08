#include "convbond.h"
//' Convertible bond pricing.
//'
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
//' @return price of convertible
//' @export
// [[Rcpp::export]]
double CBprice(double S_0,
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
	NumericMatrixToVector2d(RDividendSchedule, rngDividendSchedule);
	return CBpriceCpp(S_0, sigma, riskFreeInterestRate, creditSpread, rateCompounding, couponRate, couponFreq,
					dividendProtectionRate, rngDividendSchedule,conversionRatio,
					noConversionPeriod, americanConversionType, maturity, faceValue,
					redemptionPremium, softCallStartTime, softCall, softCallStrike,
					putStartTime, putStrike, callStartTime, callStrike,nbStepsPerYear);
	
}

//' @export
// [[Rcpp::export]]
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
	double softCall,
	double softCallStrike,
	double putStartTime,
	double putStrike,
	double callStartTime,
	double callStrike,
	double nbStepsPerYear,
  double targetBondPrice = 1.0
  )
{
	std::vector< std::vector< double > > rngDividendSchedule;
	NumericMatrixToVector2d(RDividendSchedule, rngDividendSchedule);
	return(
    convBondFindCouponCpp(S_0, sigma, intRate0, creditSpread, rateCompounding, couponFreq,
								dividendProtectionRate, rngDividendSchedule,conversionRatio,
								noConversionPeriod, americanConversionType, maturity, faceValue,
								redemptionPremium, softCallStartTime, softCall, softCallStrike,
								putStartTime, putStrike, callStartTime, callStrike, nbStepsPerYear, targetBondPrice)
  );
					
}
