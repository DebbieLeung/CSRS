# CSRS-DLL
## A Library for Coherent Spherical Range-Search on GPUs
#### Lianping Xing, Charlie C.L. Wang and Kin-Chuen Hui

What is CSRS-DLL?
CSRS-DLL is a wrapped dynamic-link library for the research Coherent Spherical Range-Search for dynamic points on GPUs [1], which supports algorithms for exact spherical range-search in arbitrarily dimensions.

Range-search with a radius r for a query q on a set of data points P is an operation to find all the neighbors p the distances from which to q are not larger than r. As the range of search is a d-dimensional sphere, this is called spherical range-search (SRS).

Different from finding k approximate nearest neighbors (ANNs), exact SRS is needed in geometry processing and physical simulation to avoid missing small features. With the help of a balanced AABB-tree, the spatial coherence of query points and the temporal coherence of dynamic points are exploited to achieve very efficient range-search and hierarchical update.

The library also comes with test programs for measuring the quality of performance of CSRS on any particular data sets. Our library provides the implementation of method presented in the following paper.

### [Project page](http://www.mae.cuhk.edu.hk/~cwang/Projects/CSRSProj.htm) | [Youtube 1](https://youtu.be/LTMe5je9beE) 


Reference:
[1] Lianping Xing, Charlie C.L. Wang, and Kin-Chuen Hui, "[Coherent spherical range-search for dynamic points on GPUs](https://www.sciencedirect.com/science/article/pii/S0010448517300106?via%3Dihub)", Computer-Aided Design, 2017.
