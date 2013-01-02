
C++ NORAD SGP4/SDP4 Implementation
Developed by Michael F. Henry

Copyright © 2003-2011 Michael F. Henry. All rights reserved.
Permission to use for non-commercial purposes only.
All other uses contact author at mfh@zeptomoby.com

The files in this directory implement a simple demonstration program for 
the OrbitTools assemblies. The project generates a single executable, 
orbitToolsDemo.exe, which calculates ECI position and velocity information
for satellites whose orbital elements were originally published in the 1980
NORAD document "Space Track Report No. 3". Also demonstrated is how to use
the libraries to calculate the look angle from a location on earth to a
satellite in orbit.

The project files were compiled using Microsoft Visual Studio 2010.

The correct program output appears below.

Michael F. Henry
December, 2009
(Updated September 2011)

===============================================================================

SGP4 Test
1 88888U          80275.98708465  .00073094  13844-3  66816-4 0     8
2 88888  72.8435 115.9689 0086731  52.6988 110.5714 16.05824518   105

  TSINCE            X                Y                Z

       0.00     2328.97070437   -5995.22083333    1719.97065611
     360.00     2456.10787343   -6071.93868176    1222.89554078
     720.00     2567.56296224   -6112.50380175     713.96182588
    1080.00     2663.09017513   -6115.48274470     196.39907463
    1440.00     2742.55440194   -6079.66984186    -326.39149750

                    XDOT             YDOT             ZDOT

                   2.91207225      -0.98341531      -7.09081697
                   2.67938906      -0.44828838      -7.22879265
                   2.44024485       0.09811117      -7.31995951
                   2.19612076       0.65241695      -7.36282421
                   1.94849696       1.21107421      -7.35619305

SDP4 Test
1 11801U          80230.29629788  .01431103  00000-0  14311-1       8
2 11801  46.7916 230.4354 7318036  47.4722  10.4117  2.28537848     6

  TSINCE            X                Y                Z

       0.00     7473.37213351     428.95462549    5828.74786677
     360.00    -3305.22417985   32410.86360001  -24697.17732308
     720.00    14271.28695394   24110.46300337   -4725.76750899
    1080.00    -9990.05752318   22717.36123643  -23616.89356981
    1440.00     9787.87233694   33753.34427732  -15030.80628319

                    XDOT             YDOT             ZDOT

                   5.10715289       6.44468289      -0.18613182
                  -1.30113547      -1.15131513      -0.28333528
                  -0.32050442       2.67984097      -2.08405301
                  -1.01667268      -2.29026701       0.72892308
                  -1.09425038       0.92358954      -1.52230979

Example output:
AZ: 100.192  EL: 12.852