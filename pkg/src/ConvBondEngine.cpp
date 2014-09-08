#include "convbond.h"
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
	double nbStepsPerYear)
{	
	int nbOfDividends = 0;
	if (!rngDividendSchedule.empty())
	{
		nbOfDividends = rngDividendSchedule.size();
	}
	int nbTreeLevels = int(nbStepsPerYear) * int(maturity);
	double intRate, intRateRisky, conversionValue = 0.0, dividendAdj, conversionAdj, discFactorRiskyUp, discFactorRiskyDown, ConvBondPrice;
	 // converting input rates to Continuous basis
	if(rateCompounding > 0)
	{
		intRate = rateCompounding * log(1 + intRate0 / rateCompounding);
		intRateRisky = rateCompounding * log(1 + (intRate0 + creditSpread) / rateCompounding);
	} else
	{
		intRate = intRate0;
		intRateRisky = intRate0 + creditSpread;
	}
	 // ##############################################	
	double dt = maturity / nbTreeLevels;
	 // calculating up and down steps
	double u = exp(sigma * sqrt( dt ));
	double d = 1 / u;
	 // calculating risk - neutral probabilities
	double p = (exp( ( intRate ) * dt) - d) / (u - d);
	int i, j, k;
	double * * treeS = new double * [nbTreeLevels];
	double * * treeConversionValue = new double * [nbTreeLevels];
	double * * treeConversionProb = new double * [nbTreeLevels];
	double * * treeDiscRate = new double * [nbTreeLevels];
	for (i = 0;i<nbTreeLevels;i++ )
	{
		treeS[i] = new double[nbTreeLevels];
		treeConversionValue[i] = new double[nbTreeLevels];
		treeConversionProb[i] = new double[nbTreeLevels];
		treeDiscRate[i] = new double[nbTreeLevels];
	}
	double * couponSchedule = new double[nbTreeLevels];
	double * dividendSchedule = new double[nbTreeLevels];
	 // setting up coupon schedule
	couponSchedule[nbTreeLevels - 1] = couponRate / couponFreq; // last coupon
	double couponTime_tmp = maturity - 1 / couponFreq;
	for (k = nbTreeLevels - 2; k >= 0; k-- )
	{
		couponSchedule[k] = 0;
		while (couponTime_tmp > k * dt)
		{
			couponSchedule[k] = couponSchedule[k] + exp( - intRateRisky * (couponTime_tmp - (k + 1) * dt)) * couponRate / couponFreq;
			couponTime_tmp = couponTime_tmp - 1 / couponFreq;
		} 
	}
	for(j = 0; j < nbTreeLevels; j++ )
	{
		dividendSchedule[j] = 1;
	}
	for(j = 0; j < nbOfDividends; j++ )
	{
		i = 0;
		while ((dt * (i + 1) < rngDividendSchedule[j][DIVIDEND_DATE_DIMENSION]) && (i < (nbTreeLevels - 1)))
		{
			i++ ;
		} 
		dividendSchedule[i] = dividendSchedule[i] - rngDividendSchedule[j][DIVIDEND_AMOUNT_DIMENSION];
	}
	dividendAdj = prod(dividendSchedule, nbTreeLevels);
	conversionAdj = 1 / prod_with_cond(dividendSchedule, nbTreeLevels, dividendProtectionRate);
	for( i = 0; i < nbTreeLevels; i++ )
	{
		treeS[i][nbTreeLevels - 1] = dividendAdj * S_0 * pow(u, i) * pow(d, (nbTreeLevels - i));
		conversionValue = conversionAdj * conversionRatio * treeS[i][nbTreeLevels - 1] / (faceValue);
		if(conversionValue > (1 + redemptionPremium) + couponSchedule[nbTreeLevels - 1]){
			treeConversionValue[i][nbTreeLevels - 1] = conversionValue;
			treeConversionProb[i][nbTreeLevels - 1] = 1;
			treeDiscRate[i][nbTreeLevels - 1] = intRate * treeConversionProb[i][nbTreeLevels - 1] + 
														intRateRisky * (1 - treeConversionProb[i][nbTreeLevels - 1]);
		} else {
			treeConversionValue[i][nbTreeLevels - 1] = (1 + redemptionPremium) + couponSchedule[nbTreeLevels - 1];
			treeConversionProb[i][nbTreeLevels - 1] = 0;
			treeDiscRate[i][nbTreeLevels - 1] = intRate * treeConversionProb[i][nbTreeLevels - 1] + 
														intRateRisky * (1 - treeConversionProb[i][nbTreeLevels - 1]);
		}
	}
	for(k = nbTreeLevels - 2; k >= 0; k-- )
	{
		dividendAdj = prod(dividendSchedule, k);
		conversionAdj = 1 / prod_with_cond(dividendSchedule, k, dividendProtectionRate);
		i = 0;
		for(i = 0; i <= k; i++ )
		{
			treeS[i][k] = dividendAdj * S_0 * pow(u, i) * pow(d, (k - i));
			conversionValue = conversionAdj * conversionRatio * treeS[i][k] / faceValue;
			treeConversionProb[i][k] = p * treeConversionProb[i + 1][k + 1] + 
														(1 - p) * treeConversionProb[i][k + 1];
			treeDiscRate[i][k] = intRate * treeConversionProb[i][k] + 
														intRateRisky * (1 - treeConversionProb[i][k]);
			discFactorRiskyUp = exp( - treeDiscRate[i + 1][k + 1] * dt);
			discFactorRiskyDown = exp( - treeDiscRate[i][k + 1] * dt);
			treeConversionValue[i][k] = couponSchedule[k] + 
														(p * discFactorRiskyUp * treeConversionValue[i + 1][k + 1] + 
														(1 - p) * discFactorRiskyDown * treeConversionValue[i][k + 1]);
			// forcing conversion : softaCall
			if ((softCall > 0) && (treeS[i][k] >= softCall) && (softCallStartTime <= k * dt)) 
			{
				treeConversionProb[i][k] = 1;
				conversionValue = conversionAdj * conversionRatio * softCall / faceValue;
				treeDiscRate[i][k] = intRate * treeConversionProb[i][k] + intRateRisky * (1 - treeConversionProb[i][k]);
				discFactorRiskyUp = exp( - treeDiscRate[i + 1][k + 1] * dt);
				discFactorRiskyDown = exp( - treeDiscRate[i][k + 1] * dt);
				treeConversionValue[i][k] = couponSchedule[k] + p * discFactorRiskyUp * treeConversionValue[i + 1][k + 1]
															 + (1 - p) * discFactorRiskyDown * treeConversionValue[i][k + 1];
				treeConversionValue[i][k] = max(min(treeConversionValue[i][k], softCallStrike), conversionValue);
			}
			if (americanConversionType && noConversionPeriod <= k * dt) 
			{
				if (conversionValue > treeConversionValue[i][k]) 
				{
					treeConversionValue[i][k] = conversionValue;
				}
			}
			if((callStrike > 0) 
				&& (conversionValue > callStrike) 
				&& (treeConversionValue[i][k] > conversionValue)
				&& (noConversionPeriod <= dt * k)
				&& (callStartTime <= dt * k ))
			{
				treeConversionValue[i][k] = conversionValue;
			} else 
			{
				if((callStrike > 0)
					&& (treeConversionValue[i][k] > callStrike)
					&& (callStrike > conversionValue)
					&& (callStartTime <= dt * k))
				{
					treeConversionValue[i][k] = callStrike;
				}
				if ((putStrike > 0) 
					&& (treeConversionValue[i][k] < putStrike)
					&& (putStartTime <= dt * k)
					&& (putStrike > conversionValue))
				{
					treeConversionValue[i][k] = putStrike;
				}
			}
		}
	}
	ConvBondPrice = treeConversionValue[0][0];
	 // clening the memory
	for (i = 0; i<nbTreeLevels; i++ )
	{
		delete[] treeS[i];
		delete[] treeConversionValue[i];
		delete[] treeConversionProb[i];
		delete[] treeDiscRate[i];
	}
	delete[] treeS;
	delete[] treeConversionValue;
	delete[] treeConversionProb;
	delete[] treeDiscRate;
	delete[] couponSchedule;
	delete[] dividendSchedule;
	return ConvBondPrice;
}

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
	double nbStepsPerYear)
{
	convBondParam * ptr_convBondParamStr;
	ptr_convBondParamStr = new convBondParam;
	ptr_convBondParamStr -> S_0 = S_0;
	ptr_convBondParamStr -> sigma = sigma; 
	ptr_convBondParamStr -> intRate0 = intRate0;
	ptr_convBondParamStr -> creditSpread = creditSpread;
	ptr_convBondParamStr -> rateCompounding = rateCompounding;
	ptr_convBondParamStr -> couponRate = couponRate;
	ptr_convBondParamStr -> couponFreq = couponFreq;
	ptr_convBondParamStr -> dividendProtectionRate = dividendProtectionRate;
	ptr_convBondParamStr -> rngDividendSchedule = rngDividendSchedule;
	ptr_convBondParamStr -> conversionRatio = conversionRatio;
	ptr_convBondParamStr -> noConversionPeriod = noConversionPeriod;
	ptr_convBondParamStr -> americanConversionType = americanConversionType;
	ptr_convBondParamStr -> maturity = maturity;
	ptr_convBondParamStr -> faceValue = faceValue;
	ptr_convBondParamStr -> redemptionPremium = redemptionPremium;
	ptr_convBondParamStr -> softCallStartTime = softCallStartTime;
	ptr_convBondParamStr -> softCall = softCall;
	ptr_convBondParamStr -> softCallStrike = softCallStrike;
	ptr_convBondParamStr -> putStartTime = putStartTime;
	ptr_convBondParamStr -> putStrike = putStrike;
	ptr_convBondParamStr -> callStartTime = callStartTime;
	ptr_convBondParamStr -> callStrike = callStrike;
	ptr_convBondParamStr -> nbStepsPerYear = nbStepsPerYear;
	return ptr_convBondParamStr;
}

double CBprice_wrapper_coupon(double couponRate, convBondParam * ptr_convBondParamStr)
{
 double price = CBprice_cpp(
	ptr_convBondParamStr -> S_0,
	ptr_convBondParamStr -> sigma, 
	ptr_convBondParamStr -> intRate0,
	ptr_convBondParamStr -> creditSpread,
	ptr_convBondParamStr -> rateCompounding,
	couponRate,
	ptr_convBondParamStr -> couponFreq,
	ptr_convBondParamStr -> dividendProtectionRate,
	ptr_convBondParamStr -> rngDividendSchedule,
	ptr_convBondParamStr -> conversionRatio,
	ptr_convBondParamStr -> noConversionPeriod,
	ptr_convBondParamStr -> americanConversionType,
	ptr_convBondParamStr -> maturity,
	ptr_convBondParamStr -> faceValue,
	ptr_convBondParamStr -> redemptionPremium,
	ptr_convBondParamStr -> softCallStartTime,
	ptr_convBondParamStr -> softCall,
	ptr_convBondParamStr -> softCallStrike,
	ptr_convBondParamStr -> putStartTime,
	ptr_convBondParamStr -> putStrike,
	ptr_convBondParamStr -> callStartTime,
	ptr_convBondParamStr -> callStrike,
	ptr_convBondParamStr -> nbStepsPerYear);
	return (price - CB_PRICE_TARGET_COUPON_CALCULATION);
}

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
	double nbStepsPerYear)
{
	double COUPON_RATE = 0;
	convBondParam * ptr_cbparam1;
	ptr_cbparam1 = init_convBondParam(S_0, sigma, intRate0, creditSpread, rateCompounding, 
					COUPON_RATE,
					couponFreq, dividendProtectionRate, rngDividendSchedule, 
					conversionRatio, noConversionPeriod, americanConversionType, maturity,
					faceValue, redemptionPremium, softCallStartTime, softCall, softCallStrike, putStartTime, putStrike,
					callStartTime, callStrike, nbStepsPerYear);
	COUPON_RATE = zeroin(TARGET_COUPON_START, TARGET_COUPON_END, CBprice_wrapper_coupon, TOLERANCE, ptr_cbparam1);
	delete ptr_cbparam1;
	return (COUPON_RATE);
}