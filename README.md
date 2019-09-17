# CSRS-DLL: A Library for Coherent Spherical Range-Search on GPUs
#### Lianping Xing, Charlie C.L. Wang and Kin-Chuen Hui

What is CSRS-DLL?
CSRS-DLL is a wrapped dynamic-link library for the research Coherent Spherical Range-Search for dynamic points on GPUs [1], which supports algorithms for exact spherical range-search in arbitrarily dimensions.

Range-search with a radius r for a query q on a set of data points P is an operation to find all the neighbors p the distances from which to q are not larger than r. As the range of search is a d-dimensional sphere, this is called spherical range-search (SRS).

Different from finding k approximate nearest neighbors (ANNs), exact SRS is needed in geometry processing and physical simulation to avoid missing small features. With the help of a balanced AABB-tree, the spatial coherence of query points and the temporal coherence of dynamic points are exploited to achieve very efficient range-search and hierarchical update.

The library provides the implementation of method presented in the following paper, where the source code can be found at the page: [Project page](http://www.mae.cuhk.edu.hk/~cwang/Projects/CSRSProj.htm). The purpose of this DLL is to allow developers, who are not familiar with the CUDA development, to benefit from the performance of highly parallel range search. Note that, in order to use CSRS-DLL, you only need to install the most updated driver for NVIDIA graphics card but not the CUDA development enviornment.

### [Youtube](https://youtu.be/LTMe5je9beE) 


## Getting Started
Choose the search method
```
Search_Method method = NEAREST;	 //GENERAL, DATAPNTS, NEAREST
```
Declare the search parameters
```
csrs_attr.data_nb = 100000;   // Data point number
csrs_attr.query_nb = 100000;   // Query point number
csrs_attr.dim = CSRS_PNT_DIM;   // Dimension of points
csrs_attr.bucket_size = 20;
csrs_attr.max_neighbor_num = (method == NEAREST) ? 1 : 350;
```
Initialize the search and query data
```
PrepareRandomData(data_pnts, query_pnts, query_radius, csrs_attr);
```
Perform searching and output the results
```
if (run_search(data_pnts, query_pnts, query_radius, ret_indexes, ret_dists, ret_neigh, method, csrs_attr, iterations)) {
```


## Citation
If you use this code for your research, please cite our [paper](https://www.sciencedirect.com/science/article/pii/S0010448517300106?via%3Dihub):

```
@article{CSRS2017,
  title={Coherent spherical range-search for dynamic points on GPUs},
  author={Xing, Lianping and Wang, Charlie C.L. and Hui, Kin-Chuen},
  journal={Computer-Aided Design},
  volume = {86},
  number = {C},
  pages = {12--25},
  year={2017}
}

```
## Copyright
All rights about the program are reserved by Lianping Xing, Charlie C.L. Wang and Kin-Chuen Hui at the Department of Mechanical and Automation Engineering, The Chinese University of Hong Kong. In no event shall the author be liable to any party for direct, indirect, special, incidental, or consequential damage arising out of the use of this program.
