#' @export
CBpriceCouponWrapper<-function(couponRate, S_0, sigma, intRate0, creditSpread, rateCompounding, couponFreq,
                                       dividendProtectionRate, rngDividendSchedule, conversionRatio, noConversionPeriod,
                                       americanConversionType, maturity, faceValue, redemtionPremium, barrierStartTime, barrier, barrierStrike,
                                       putStartTime, putStrike, callStartTime, callStrike, nbStepsPerYear)
{
  return(1-CBprice(S_0, sigma, intRate0, creditSpread, rateCompounding, couponRate, couponFreq,
          dividendProtectionRate, rngDividendSchedule, conversionRatio, noConversionPeriod,
          americanConversionType, maturity, faceValue, redemtionPremium, barrierStartTime, barrier, barrierStrike,
          putStartTime, putStrike, callStartTime, callStrike, nbStepsPerYear));
}
#' @export
CBpriceDividendWrapper<-function(rngDividendSchedule, S_0, sigma, intRate0, creditSpread, rateCompounding, couponRate, couponFreq,
                                 dividendProtectionRate, conversionRatio, noConversionPeriod, americanConversionType, 
                                 maturity, faceValue, redemtionPremium, barrierStartTime, barrier, barrierStrike,
                                 putStartTime, putStrike, callStartTime, callStrike, nbStepsPerYear)
{
  return(CBprice(S_0, sigma, intRate0, creditSpread, rateCompounding, couponRate, couponFreq,
                 dividendProtectionRate, rngDividendSchedule, conversionRatio, noConversionPeriod,
                 americanConversionType, maturity, faceValue, redemtionPremium, barrierStartTime, barrier, barrierStrike,
                 putStartTime, putStrike, callStartTime, callStrike, nbStepsPerYear));
}