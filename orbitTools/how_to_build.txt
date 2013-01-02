# type below command to build libcore.a
cd core
g++ -c cEci.cpp cJulian.cpp cSite.cpp cTLE.cpp cVector.cpp coord.cpp globals.cpp stdafx.cpp
ar crv libcore.a cEci.o cJulian.o cSite.o cTLE.o cVector.o coord.o globals.o stdafx.o
rm *.o
mv libcore.a ../
cd ../

# type below command to build liborbit.a
cd orbit
g++ -c cOrbit.cpp cNoradBase.cpp cNoradSDP4.cpp cNoradSGP4.cpp stdafx.cpp
ar crv liborbit.a cOrbit.o cNoradBase.o cNoradSDP4.o cNoradSGP4.o stdafx.o
rm *.o
mv liborbit.a ../
cd ../
