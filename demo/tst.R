library(microbenchmark)
div_sched<-matrix(data=c(seq(0.73, 4.73, 1), rep(0.035, 5)), ncol=2)
microbenchmark(CBpriceR(20, 0.25, 0.01, 0.03, 1, 0.02, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 50));

convBondFindCouponR(20, 0.20, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 150);

CBpriceCouponWrapper(0.02, 20, 0.25, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 50);
system.time(op_coupon<-uniroot(f=CBpriceCouponWrapper, interval=c(0,0.5), 
                               20, 0.25, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 150, tol=1e-8))
system.time(convBondFindCouponR(20, 0.20, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 150))
microbenchmark(uniroot(f=CBpriceCouponWrapper, interval=c(0,0.5), 
                       20, 0.20, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 50, tol=1e-8),
               convBondFindCouponR(20, 0.20, 0.01, 0.03, 1, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 50))
# expr      min       lq  median       uq
# 11.13801 11.46668 11.5484 11.89313
# max neval
# 56.34459   100