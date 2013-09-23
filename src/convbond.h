#include "convbondR.h"
#include <stdio.h>
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
	double redemptionPremium;
	double softCallStartTime;
	double softCall;
	double softCallStrike;
	double putStartTime;
	double putStrike;
	double callStartTime;
	double callStrike;
	double nbStepsPerYear;
} convBondParam;

//int *createIndex(int);
double prod(double*, int);
double prod_with_cond(double*, int, double);
double zeroin(double, double, double (*f)(double, convBondParam*),double, convBondParam*);

double CBprice_cpp(double S_0,
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
	double redemptionPremium,
	double softCallStartTime,
	double softCall,
	double softCallStrike,
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
	double redemptionPremium,
	double softCallStartTime,
	double softCall,
	double softCallStrike,
	double putStartTime,
	double putStrike,
	double callStartTime,
	double callStrike,
	double nbStepsPerYear);
  
double CBpriceWrapper_StructInput(double, convBondParam*);
 
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
	double redemptionPremium,
	double softCallStartTime,
	double softCall,
	double softCallStrike,
	double putStartTime,
	double putStrike,
	double callStartTime,
	double callStrike,
	double nbStepsPerYear);

int checkMemotyLeaks();
double CBprice_wrapper_coupon(double, convBondParam *);