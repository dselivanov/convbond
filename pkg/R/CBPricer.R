#' @describeIn CBprice CBpriceCouponWrapper wrapper of CBprice for usage in uniroot function. 
#' This is useful we want to find coupon level for a given convertible bond specs. Particulary useful for issuance of CB.
#' @export
CBpriceCouponWrapper<-function(couponRate, S_0, sigma, intRate0, creditSpread, rateCompounding, couponFreq,
                               dividendProtectionRate, rngDividendSchedule, conversionRatio, noConversionPeriod,
                               americanConversionType, maturity, faceValue, redemtionPremium = 0, softCallStartTime = 0,
                               softCallBarrier = 0, softCallStrike = 0, putStartTime = 0, putStrike = 0, callStartTime = 0,
                               callStrike = 0, nbStepsPerYear = 0)
{
  return(1-CBprice(S_0, sigma, intRate0, creditSpread, rateCompounding, couponRate, couponFreq,
          dividendProtectionRate, rngDividendSchedule, conversionRatio, noConversionPeriod,
          americanConversionType, maturity, faceValue, redemtionPremium, softCallStartTime, softCallBarrier,
          softCallStrike, putStartTime, putStrike, callStartTime, callStrike, nbStepsPerYear));
}

#' @describeIn CBprice CBpriceDividendWrapper wrapper of CBprice for usage in uniroot function. 
#' This is useful we want to find dividend level for a given convertible bond
#' @export
CBpriceDividendWrapper<-function(rngDividendSchedule, S_0, sigma, intRate0, creditSpread, rateCompounding, couponRate, couponFreq,
                                 dividendProtectionRate, conversionRatio, noConversionPeriod, americanConversionType, 
                                 maturity, faceValue, redemtionPremium = 0, softCallStartTime = 0, softCallBarrier = 0,
                                 softCallStrike = 0, putStartTime = 0, putStrike = 0, callStartTime = 0,
                                 callStrike = 0, nbStepsPerYear = 0)
{
  return(CBprice(S_0, sigma, intRate0, creditSpread, rateCompounding, couponRate, couponFreq,
                 dividendProtectionRate, rngDividendSchedule, conversionRatio, noConversionPeriod,
                 americanConversionType, maturity, faceValue, redemtionPremium, softCallStartTime, softCallBarrier, softCallStrike,
                 putStartTime, putStrike, callStartTime, callStrike, nbStepsPerYear));
}