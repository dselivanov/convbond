
# Repository provides materials and code for evaluating convertible bonds.
* R package for evaluating convertible bond prices and other useful characteristics of this derivatives.
* Many useful articles
* Speadsheet calculators - 1) founded in www 2) MS excel wrapper of old version of convbond code (probably there are some bugs in this wrapper)

## ATTENTION!
I worked on this project in summer of 2013. There is autumn of 2014 at the moment and since January of 2014 I'm working in another field - machine learning and big data. So **probably**  

1. this package will not be in active development
1. some useful details about pricing already forgotten  

## MOTIVATION
This package was developed because of lack of this functionality in other packages and even other open source projects. There is excellent (quantlib)[http://quantlib.org/index.shtml] project and related R wrapper - RQuantLib(http://cran.r-project.org/web/packages/RQuantLib/index.html). But it is very big and it is quite hard to understand all its structure and how to use it (at least for me). And the  more important - this library has no functionality for pricing convertible bonds with dividend protection. Now almost all convertibles has dividend protection, soft calls, etc.

## FEATURES
Convbond package allow to evaluate convertibles with  

* dividend protection  
* restrictions on conversion period  
* soft call options with restrictions on exercise period  
* regular call options with restrictions on exercise period  
* regular put options with restrictions on exercise period  
* diffrent types of conversion - american or european  
* redemtion premium  

Dividend forecasts in the pricer have to be determined via dividend matrix - date(as period in years from pricing date to dividend date):amoun(have to be determined as percentage of equiry price).
For coupons we have to determine coupon rate and coupon frequency. It is not very useful when pricing existing convertible, but useful when we try to determine convertible characteristics while placement. But this lack of functionality can be fixed quite easy - see ConvBondEngine.cpp source file. 

### Installing convbond package
First of all you have to install **devtools** package:  
```R
install.packages(devtools)
```
Then you can install convbond package directly from github:
```R
library(devtools)
install_github("dselivanov/convbond/pkg")
library(convbond)
```
