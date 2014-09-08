\name{cbprice}
\alias{cbprice}
\title{Convertible bond pricing}
\usage{
  cbprice(S_0, sigma, riskFreeInterestRate, creditSpread,
    rateCompounding, couponRate, couponFreq,
    dividendProtectionRate, RDividendSchedule,
    conversionRatio, noConversionPeriod,
    americanConversionType, maturity, faceValue,
    redemptionPremium, softCallStartTime, softCall,
    softCallStrike, putStartTime, putStrike, callStartTime,
    callStrike, nbStepsPerYear)
}
\arguments{
  \item{S_0}{underlying initial price}

  \item{sigma}{annualised implied volatility of the
  underlying}

  \item{riskFreeInterestRate}{risk free rate}

  \item{creditSpread}{spread to risk free rate}

  \item{rateCompounding}{basis for rates. annual=1,
  semi-annual=2, etc. For the continious basis use
  rateCompounding=0}

  \item{couponRate}{coupon on bond}

  \item{couponFreq}{numer of coupons per year. Usually
  twice a year.}

  \item{dividendProtectionRate}{divident protection
  threshold. In the model we use dividend protection via
  adjustment to conversion rate (Dividend protection is
  almost always provided by an adjustment to the conversion
  price or conversion ratio).}

  \item{RDividendSchedule}{dividend schedule 2-column
  matrix. 1-column - time to dividend, 2-column - dividend
  rate. See demos.}

  \item{conversionRatio}{number of shares per one
  convertible bond}

  \item{noConversionPeriod}{restriction for conversion in
  years.}

  \item{americanConversionType}{type of the conversion
  option. In almost all cases it is american. So we can
  convert any time. Set =0 if conversion possible only at
  maturity.}

  \item{maturity}{maturity of the convertible}

  \item{faceValue}{nominal amount of convertible bond}

  \item{redemptionPremium}{premium at conversion. For
  example if issuer can pay premium 10% of the faceValue at
  maturity to the holder (at redemtion). If so set
  parameter =0.1. In almost all cases there is no
  redemption premium.}
}
\value{
  price of the convertible
}
\description{
  Returns price of convertible bond
}

