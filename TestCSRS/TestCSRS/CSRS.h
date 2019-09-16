#ifndef	_CSRS
#define	_CSRS

#include <Windows.h>

#ifdef DLLDIR_EX
#define DLLDIR  __declspec(dllexport)   // export DLL information

#else
#define DLLDIR  __declspec(dllimport)   // import DLL information

#endif 

class DLLDIR CSRS_Attributes
{
public:
	int query_nb;		// Query point number
	int data_nb;
	int	dim;
	int	max_neighbor_num;
	int bucket_size;
};

class DLLDIR CSRS_Search
{
public:
	CSRS_Search(void) {};	
	~CSRS_Search(void) {};
	
	bool CSRS_GeneralSearch(float* data_points,
							float* query_points,
							float query_radius, 
							int*& ret_indexes, 
							float*& ret_dists,
							int*& ret_neigh,
							CSRS_Attributes attr,
							int iter);

	bool CSRS_SearchByDataPnts(float* data_points,
							   float* query_points,
							   float query_radius,
							   int*& ret_indexes,
							   float*& ret_dists,
							   int*& ret_neigh,
							   CSRS_Attributes attr,
							   int iter);
	
	bool CSRS_SearchByNearestNeightbor(float* data_points,
									   float* query_points,
									   float query_radius,
									   int*& ret_indexes,
									   float*& ret_dists,
										int*& ret_neigh,
										CSRS_Attributes attr,
										int iter);

	void test();

};

#endif