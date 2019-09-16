#include <ctime>						// clock
#include <cmath>						// math routines
#include <cstring>						// C string ops
#include <fstream>						// file I/O
#include <vector>

#include <stdio.h>
#include <Windows.h>


#include "CSRS.h"


#define CSRS_PNT_DIM 3

enum Search_Method {
	GENERAL,
	DATAPNTS,
	NEAREST
};

void PrepareRandomData(float*& data_pnts, float*& query_pnts, float& query_radius, struct CSRS_Attributes attr) {
	//--------------------------------------------------------------------------------------
	//	Generate data sets
	srand((unsigned int)(time(NULL)));
	//--------------------------------------------------------------------------------------
	data_pnts = (float*)malloc(sizeof(float) * attr.data_nb * attr.dim);		//	Data points
	query_pnts = (float*)malloc(sizeof(float) * attr.query_nb * attr.dim);	//	Query points
	for (int i = 0; i < attr.data_nb; i++) { for (int j = 0; j < attr.dim; j++) { data_pnts[attr.dim * i + j] = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f; } }
	for (int k = 0; k < attr.query_nb; k++) { for (int j = 0; j < attr.dim; j++) { query_pnts[attr.dim * k + j] = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f; } }

	//--------------------------------------------------------------------------------------
	//	Calculate bbx and set query radius - r
	float* bnds_lo = new float[attr.dim];
	float* bnds_hi = new float[attr.dim];
	for (int d = 0; d < attr.dim; d++) {		// find smallest enclosing rectangle
		float lo_bnd = data_pnts[attr.dim * 0 + d];		// lower bound on dimension d
		float hi_bnd = data_pnts[attr.dim * 0 + d];;		// upper bound on dimension d
		for (int j = 0; j < attr.data_nb; j++) {
			if (data_pnts[attr.dim * j + d] < lo_bnd) lo_bnd = data_pnts[attr.dim * j + d];
			else if (data_pnts[attr.dim * j + d] > hi_bnd) hi_bnd = data_pnts[attr.dim * j + d];
		}
		bnds_lo[d] = lo_bnd;	bnds_hi[d] = hi_bnd;
	}
	float sum = 0.0;
	for (int d = 0; d < attr.dim; d++) {
		sum += (bnds_hi[d] - bnds_lo[d]) * (bnds_hi[d] - bnds_lo[d]);
	}
	float bbxDiagonalLength = sqrt(sum);
	query_radius = 0.01f * bbxDiagonalLength;
	printf("BBX-DiagonalL=%.6f   Query-Radius=%.6f\n", bbxDiagonalLength, query_radius);
}

bool run_search(float* data_pnts, float* query_pnts, float query_radius, int*& ret_indexes, float*& ret_dists, int*& ret_neigh, Search_Method method, struct CSRS_Attributes attr, int iter) {

	CSRS_Search csrs;
	switch (method) {
	case Search_Method::GENERAL:
		return csrs.CSRS_GeneralSearch(data_pnts, query_pnts, query_radius, ret_indexes, ret_dists, ret_neigh, attr, iter);		
	case Search_Method::DATAPNTS:
		return csrs.CSRS_SearchByDataPnts(data_pnts, query_pnts, query_radius, ret_indexes, ret_dists, ret_neigh, attr, iter);
	case Search_Method::NEAREST:
		return csrs.CSRS_SearchByNearestNeightbor(data_pnts, query_pnts, query_radius, ret_indexes, ret_dists, ret_neigh, attr, iter);
	}
	
}



int main(int argc, char** argv)
{
	//--------------------------------------------------------------------------------------
	//Settings
	//--------------------------------------------------------------------------------------
	Search_Method method = NEAREST;	 //GENERAL, DATAPNTS, NEAREST

	struct CSRS_Attributes csrs_attr;
		csrs_attr.data_nb = 100000;				// Data point number
		csrs_attr.query_nb = 100000;				// Query point number
		csrs_attr.dim = CSRS_PNT_DIM;		// Dimension of points
		csrs_attr.bucket_size = 20;
		csrs_attr.max_neighbor_num = (method == NEAREST) ? 1 : 350;
		 
	int iterations = 200;


	//--------------------------------------------------------------------------------------
	//Prepare data
	//--------------------------------------------------------------------------------------
	float* data_pnts;
	float* query_pnts;
	float query_radius;
	PrepareRandomData(data_pnts, query_pnts, query_radius, csrs_attr);


	//--------------------------------------------------------------------------------------
	//Run Search
	//--------------------------------------------------------------------------------------
	int* ret_indexes;
	float* ret_dists;
	int* ret_neigh;
	if (run_search(data_pnts, query_pnts, query_radius, ret_indexes, ret_dists, ret_neigh, method, csrs_attr, iterations)) {
		//output Results
		FILE* fp = fopen("CSRS_result.txt", "w");
		for (int j = 0; j < csrs_attr.query_nb; j++) {
			if (method == NEAREST) {
				fprintf(fp, "%d %.6f\n", ret_indexes[j], sqrt(ret_dists[j]));
			}
			else {
				fprintf(fp, "%d ", ret_neigh[j]);
				for (int jj = 0; jj < ret_neigh[j]; jj++) {
					fprintf(fp, "%d %.6f ", (ret_indexes[j * csrs_attr.max_neighbor_num + jj]), sqrt(ret_dists[j * csrs_attr.max_neighbor_num + jj]));
				}
				fprintf(fp, "\n");
			}
		}
		fclose(fp);		
		//--------------------------------------------------------------------------------------
		free(ret_indexes);	free(ret_dists);	free(ret_neigh);
		printf("Finished.\n\n\n");
	}



	free(data_pnts);	free(query_pnts);
	return 1;
}
