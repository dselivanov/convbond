library(ggplot2)
library(scales)
library(microbenchmark)
# generate some data for test
startDiv<-0.008
step<-0.002
N <- 50
# dividend schedule must be in matrix format - each row is a pair 
# (time in years since evaluation moment, dividend level (percent of equiity price at given time))
DivList<-list()
for (i in (1:N))
{
  DivList[[i]] <- matrix(data=c(seq(0.76, 4.76, 1), rep(startDiv + step * i, 5)), ncol = 2)
}
div_sched <- DivList[[1]]
# check format
print(div_sched)
########################################################################################
# Let's calculate price of CB:
CBprice(S_0 = 20, sigma = 0.25, riskFreeInterestRate = 0.01, creditSpread = 0.03, rateCompounding = 1, 
        couponRate = 0.02, couponFreq = 1, dividendProtectionRate = 0.015, dividendSchedule = div_sched, 
        conversionRatio = 4, noConversionPeriod = 0, americanConversionType = 1, maturity = 5, faceValue = 100, 
        redemptionPremium = 0, softCallStartTime = 0, softCallBarrier = 0, softCallStrike = 0, 
        putStartTime = 0, putStrike = 0, callStartTime = 0, callStrike = 0, nbStepsPerYear = 50);
# Try to add softCall after 1 year with strike = nominal faceValue and diffrent barriers:
cbprice <- c()
barrier <- 20 + seq(0, 10, 0.25)
for (i in barrier) {
  cbprice <- append(cbprice, CBprice(S_0 = 20, sigma = 0.15, riskFreeInterestRate = 0.01, creditSpread = 0.03, rateCompounding = 1, 
          couponRate = 0.02, couponFreq = 2, dividendProtectionRate = 0.015, dividendSchedule = div_sched, 
          conversionRatio = 4, noConversionPeriod = 0, americanConversionType = 1, maturity = 5, faceValue = 100, 
          redemptionPremium = 0, softCallStartTime = 1, softCallBarrier = i, softCallStrike = 1,
          putStartTime = 0, putStrike = 0, callStartTime = 0, callStrike = 0, nbStepsPerYear = 50)
  )
}
ggplot(data = data.frame(barrier = barrier, cbprice = cbprice),
  mapping = aes(x = barrier, y = cbprice)) + 
  geom_line(col = 'red') +
  geom_point(col = 'red') +
  scale_x_continuous(labels = dollar) +
  scale_y_continuous(labels = percent)

# And try to calculate coupon:
CBfindCoupon(20, 0.20, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 50);
########################################################################################
# Let's calculate prices for diffrent dividend levels and fixed dividend protection rate.
y <- lapply(DivList, CBpriceDividendWrapper, S_0 = 20, sigma = 0.35, intRate0 = 0.01, creditSpread = 0.03, rateCompounding = 1, 
        couponRate = 0.02, couponFreq = 1, dividendProtectionRate = 0.025, conversionRatio = 4 , noConversionPeriod = 0,
        americanConversionType = 1, maturity = 10, faceValue = 100, redemtionPremium = 0, softCallStartTime=0, 
        softCall = 0, softCallStrike = 0, putStartTime = 0, putStrike = 0, callStartTime = 0, callStrike = 0, nbStepsPerYear = 10)

ggplot(data = data.frame(dividend=seq(startDiv + step, startDiv + step * N, step), cbprice = unlist(y)),
       mapping = aes(x = dividend, y = cbprice)) + 
  geom_line(col = 'red') +
  geom_point(col = 'red') +
  scale_x_continuous(labels = percent) +
  scale_y_continuous(labels = percent)
########################################################################################

# check performance of uniroot + CBpriceCouponWrapper vs CBfindCoupon
microbenchmark(uniroot(f=CBpriceCouponWrapper, interval=c(0,0.5), 20, 0.20, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 50, tol=1e-8),
               CBfindCoupon(20, 0.20, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 50))
