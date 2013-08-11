library(ggplot2)
library(scales)
library(microbenchmark)
startDiv<-0.01
step<-0.002
N <- 50
DivList<-list()
for (i in (1:N))
{
  DivList[[i]] <- matrix(data=c(seq(0.76, 4.76, 1), rep(startDiv + step * i, 5)), ncol=2)
}
y<-lapply(DivList, CBpriceDividendWrapper, S_0 = 20, sigma = 0.35, intRate0 = 0.01, creditSpread = 0.03, rateCompounding = 1, 
        couponRate = 0.02, couponFreq = 1, dividendProtectionRate = 0.025, conversionRatio = 4 , noConversionPeriod = 0,
        americanConversionType = 1, maturity = 10, faceValue = 100, redemtionPremium = 0, barrierStartTime=0 ,barrier = 0, barrierStrike = 0,
        putStartTime = 0, putStrike = 0, callStartTime = 0, callStrike = 0, nbStepsPerYear = 100)

ggplot(data=data.frame(x=seq(startDiv + step, startDiv + step*N, step), y=unlist(y)), aes(x=x, y=y)) + 
   geom_line(col='red') +
   geom_point(col='red') +
   scale_x_continuous(labels = percent) +
   scale_y_continuous(labels = percent)


div_sched<-DivList[[1]]
CBpriceR(20, 0.25, 0.01, 0.03, 1, 0.02, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 50);
convBondFindCouponR(20, 0.20, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 50);

#CBpriceCouponWrapper(0.02, 20, 0.25, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 50);
#system.time(op_coupon<-uniroot(f=CBpriceCouponWrapper, interval=c(0,0.5), 
#                               20, 0.25, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 150, tol=1e-8))
#system.time(convBondFindCouponR(20, 0.20, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 150))
microbenchmark(uniroot(f=CBpriceCouponWrapper, interval=c(0,0.5), 20, 0.20, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 50, tol=1e-8),
               convBondFindCouponR(20, 0.20, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 50))