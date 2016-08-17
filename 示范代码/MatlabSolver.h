//////////////////////////////////////////////////////////////////////////
/*
用于处理C与Matlab的数据交换,使得可以使用Matlab来处理数据



*/
//////////////////////////////////////////////////////////////////////////

#ifndef     _MATLAB_SOLVER_
#define     _MATLAB_SOLVER_
#include "StdAfx.h"
#include <engine.h>
#include <vector>
#include <iostream>
using namespace std;
#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libeng.lib" )


class	   CMatlabSolverBase
{
public:
			//若无特殊情况 都使用Global Engine ，甚至可以说，只会有一个Engine出现
			CMatlabSolverBase():m_ep(NULL){}
			void				StartEngine();
			void				EndEngine();
			Engine* GetEngine()
			{
				return m_ep;
			}

			void PutVectorIn(const char *pName, vector<double> pData);
			void PutVectorIn(const char *pName, vector<int> pData);
			
//protected:
		
			template<typename T>
			void				PutVectorIn(const char *pName, vector<T> pData);
			template<typename T>
			void                GetVectorOut(const char *pName, vector<T>& vec);
			//void				PutRowMatIn(const char *pName,const numc::RowMat<double> &rowmat,int nMatCol); //rowmat 不一定是方阵
			void				GetVectorOut(const char *pName, vector<double> &vec_x);
			void		        GetVectorOut(const char *pName, vector<int> &vec_x);
			void				GetVariable(const char *pName, double &dval);
			void				PutMatrixIn(const char *pName, double **pData, int nrow, int ncol);
			void				PutMatrixIn_Row(const char *pName, double *pData, int nrow, int ncol);	
			void 				PutMatrixIn_Col(const char *pName, double *pData, int nrow, int ncol);
			void				DispVariable(const char *pName);	

protected:
			Engine				*m_ep;

};
//class template function
template<typename T>
void		CMatlabSolverBase::PutVectorIn(const char *pName,vector<T> pData)
{
			mxArray *p_mxArray; 
			size_t nSize = pData.size();
			p_mxArray=mxCreateDoubleMatrix(nSize,1,mxREAL);

			for(int i=0;i<nSize;++i)
			{
				*(mxGetPr(p_mxArray)+i)=pData[i];
			}
			engPutVariable(m_ep,pName,p_mxArray);  
			mxDestroyArray(p_mxArray);			
};

template<typename T>
void        CMatlabSolverBase::GetVectorOut(const char *pName, vector<T>& vec)
{
	mxArray *p_mxArray; 
	p_mxArray=engGetVariable(m_ep,pName);
	double *temp;
	temp = mxGetPr(p_mxArray);
	int m, n;
	m = mxGetM(p_mxArray);
	n = mxGetN(p_mxArray);
	vec = vector<T>(m*n);
	int k = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			vec[k] = temp[i + j*m];
			k++;
		}
	}
	/*for(int i=0;i<nSize;++i)
	{
		vec[i]=(T)*(mxGetPr(p_mxArray)+i);
	}*/

	mxDestroyArray(p_mxArray);
}
#endif