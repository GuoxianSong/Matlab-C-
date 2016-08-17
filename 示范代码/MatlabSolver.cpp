#include "StdAfx.h"
#include "MatlabSolver.h"
#include <string>
#include <cassert>
#include <cstdio>
#include <sstream>


void	CMatlabSolverBase::EndEngine()
{
	if(m_ep)
	{
		engClose(m_ep);
		m_ep=NULL;
	}
}

void CMatlabSolverBase::StartEngine()
{
	m_ep = engOpen(NULL);
}

void		CMatlabSolverBase::DispVariable(const char *pName)
{
			string   sText("disp(");
			sText+=pName;
			sText+=");";
			engEvalString(m_ep,sText.c_str());
}


void		CMatlabSolverBase::GetVectorOut(const char *pName,vector<double> &vec_x)
{
			mxArray *p_mxArray; 
			p_mxArray=engGetVariable(m_ep,pName);
			double *temp;
			temp = mxGetPr(p_mxArray);
			int m, n;
			m = mxGetM(p_mxArray);
			n = mxGetN(p_mxArray);
			vec_x = vector<double>(m*n);
			int k = 0;
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
				{
					vec_x[k] = temp[i + j*m];
					k++;
				}
			}
			//for(int i=0;i<nSize;++i)
			//{
			//		vec_x[i]=(double)*(mxGetPr(p_mxArray)+i);
			//}

			mxDestroyArray(p_mxArray);
}

void		CMatlabSolverBase::GetVectorOut(const char *pName,vector<int> &vec_x)
{
	mxArray *p_mxArray; 
	p_mxArray=engGetVariable(m_ep,pName);
	double *temp;
	temp = mxGetPr(p_mxArray);
	int m, n;
	m = mxGetM(p_mxArray);
	n = mxGetN(p_mxArray);
	vec_x = vector<int>(m*n);
	int k = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			vec_x[k] = temp[i + j*m];
			k++;
		}
	}
	//for(int i=0;i<nSize;++i)
	//{
	//	vec_x[i]=*(mxGetPr(p_mxArray)+i);
	//}

	mxDestroyArray(p_mxArray);
}



void		CMatlabSolverBase::GetVariable(const char *pName,double &dval)
{
			mxArray *p_mxArray; 
			p_mxArray=engGetVariable(m_ep,pName);
			dval=*mxGetPr(p_mxArray);
			mxDestroyArray(p_mxArray);
}

void CMatlabSolverBase::PutMatrixIn(const char *pName, double **pData, int nrow, int ncol)
{
	mxArray *p_mxArray; 
	p_mxArray = mxCreateDoubleMatrix(nrow, ncol, mxREAL);

	int matrix_id = 0;
	for (int col_id = 0; col_id < ncol; ++col_id)
	{	
		for (int row_id = 0; row_id < nrow; ++row_id)
		{
			*(mxGetPr(p_mxArray) + matrix_id) = pData[row_id][col_id];
			++matrix_id;
		}
	}
	engPutVariable(m_ep, pName, p_mxArray);  
	mxDestroyArray(p_mxArray);
}

// pData 里面的数据按照行存储
void CMatlabSolverBase::PutMatrixIn_Row(const char *pName, double *pData, int nrow, int ncol)
{
	mxArray *p_mxArray; 
	p_mxArray = mxCreateDoubleMatrix(nrow, ncol, mxREAL);

	int matrix_id = 0;
	for (int col_id = 0; col_id < ncol; ++col_id)
	{	
		for (int row_id = 0; row_id < nrow; ++row_id)
		{
			*(mxGetPr(p_mxArray) + matrix_id) = pData[row_id * ncol + col_id];
			++matrix_id;
		}
	}


	engPutVariable(m_ep, pName, p_mxArray);  
	mxDestroyArray(p_mxArray);
}

// pData里面的数据按照列存储
void CMatlabSolverBase::PutMatrixIn_Col(const char *pName, double *pData, int nrow, int ncol)
{
	mxArray *p_mxArray; 
	p_mxArray = mxCreateDoubleMatrix(nrow, ncol, mxREAL);

	int matrix_id = 0;
	for (int col_id = 0; col_id < ncol; ++col_id)
	{	
		for (int row_id = 0; row_id < nrow; ++row_id)
		{
			*(mxGetPr(p_mxArray) + matrix_id) = pData[matrix_id];
			++matrix_id;
		}
	}

	engPutVariable(m_ep, pName, p_mxArray);  
	mxDestroyArray(p_mxArray);
}

//class template function
void CMatlabSolverBase::PutVectorIn(const char *pName, vector<double> pData)
{
	mxArray *p_mxArray; 
	size_t nSize = pData.size();
	p_mxArray=mxCreateDoubleMatrix(nSize,1,mxREAL);


	for(int i=0;i<nSize;++i)
	{
		*(mxGetPr(p_mxArray)+i) = pData[i];
	}
	engPutVariable(m_ep,pName,p_mxArray);  
	mxDestroyArray(p_mxArray);
	//OutPutMessage();
}

void CMatlabSolverBase::PutVectorIn(const char *pName, vector<int> pData)
{
	mxArray *p_mxArray; 
	size_t nSize = pData.size();
	p_mxArray=mxCreateDoubleMatrix(nSize,1,mxREAL);


	for(int i=0;i<nSize;++i){
		*(mxGetPr(p_mxArray)+i) = pData[i];
	}

	engPutVariable(m_ep,pName,p_mxArray);  
	mxDestroyArray(p_mxArray);
}
