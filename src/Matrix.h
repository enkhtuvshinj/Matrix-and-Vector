#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <cstring>
#include "Vector.h"

namespace atlatec {

	template <typename T>
	class Matrix {
	private:
		unsigned int rows;
		unsigned int cols;
		unsigned int size;
		T* elements;

	public:
		Matrix(unsigned int rows, unsigned int columns) : rows(rows), cols(columns) {
#ifdef MATRIX_DEBUGGING
			std::cerr << "MatConstructor initialize" << std::endl;
#endif
			size = rows * columns;
			elements = new T[size];	
		}
		
		Matrix(const Matrix& B) : rows(B.getRows()), cols(B.getCols()) {
#ifdef MATRIX_DEBUGGING
			std::cerr << "MatConstructor copy" << std::endl;
#endif
			size = B.getSize();
			elements = new T[size];
			std::memcpy(elements, B.elements, size * sizeof(T));
		}
		
		~Matrix() {
#ifdef MATRIX_DEBUGGING
			std::cerr << "MatDeconstructor" << std::endl;
#endif
			if (elements) {	
				delete[] elements;	
			}	
		};


		/***************************
		 * Matrix Element access
		 **************************/
		T& operator()(unsigned int row, unsigned int column) {
#ifdef MATRIX_DEBUGGING
			std::cerr << "  MatOperater element access" << std::endl;
#endif
			if (row >= rows || column >= cols) {
				throw std::out_of_range("Index out of range");
			}
			return elements[row * cols + column];
		}

		const T& operator()(unsigned int row, unsigned int column) const {
#ifdef MATRIX_DEBUGGING
			std::cerr << "  MatOperater element access Const" << std::endl;
#endif
			if (row >= rows || column >= cols) {
				throw std::out_of_range("Index out of range");
			}
			return elements[row * cols + column];
		}


		/***************************
		 * Matrix Scalar operations 
		 **************************/
		Matrix& operator+=(T scalar) {
#ifdef MATRIX_DEBUGGING
			std::cerr << "  MatOperater scalar +=" << std::endl;
#endif
			for (unsigned int i = 0; i < rows; i++) {
				for (unsigned int j = 0; j < cols; j++) {
					elements[i*cols + j] = elements[i*cols + j] + scalar;
				}
			}
			return *this;
		}

		Matrix& operator*=(T scalar) {
#ifdef MATRIX_DEBUGGING
			std::cerr << "  MatOperater scalar *=" << std::endl;
#endif
			for (unsigned int i = 0; i < rows; i++) {
				for (unsigned int j = 0; j < cols; j++) {
					elements[i*cols + j] = elements[i*cols + j] * scalar;
				}
			}
			return *this;
		}

		Matrix operator+(T scalar) {
#ifdef MATRIX_DEBUGGING
			std::cerr << "  MatOperater scalar +" << std::endl;
#endif
			Matrix result(*this);
			result += scalar;
			return result;
		}

		Matrix operator*(T scalar) {
#ifdef MATRIX_DEBUGGING
			std::cerr << "  MatOperater scalar *" << std::endl;
#endif
			Matrix result(*this);
			result *= scalar;
			return result;
		}

		Matrix operator-(T scalar) {
#ifdef MATRIX_DEBUGGING
			std::cerr << "  MatOperater scalar -" << std::endl;
#endif
			Matrix result(*this);
			result += -1*scalar;
			return result;
		}

		/****************************
		 * Matrix Matrix operations
		 ****************************/
		Matrix& operator+=(const Matrix& B) {
#ifdef MATRIX_DEBUGGING
			std::cerr << "  MatOperater matrix +=" << std::endl;
#endif
			if (rows != B.getRows() || cols != B.getCols()) {
				throw std::length_error("Matrices shapes mismatch");
			}
			for (auto i = 0; i < getSize(); i++) {
				this->elements[i] = this->elements[i] + B.elements[i];
			}
			return *this;
		}

		Matrix operator+(const Matrix& B) {
#ifdef MATRIX_DEBUGGING
			std::cerr << "  MatOperater matrix +" << std::endl;
#endif
			if (rows != B.getRows() || cols != B.getCols()) {
				throw std::length_error("Matrices shapes mismatch");
			}
			Matrix result(*this);
			result += B;
			return result;
		}

		Matrix operator-(Matrix& B) {
#ifdef MATRIX_DEBUGGING
			std::cerr << "  MatOperater scalar -" << std::endl;
#endif
			Matrix result(*this);
			result += B*(-1);
			return result;
		}

		Matrix operator*(const Matrix& B) {
			if (cols != B.getRows() || rows != B.getCols()) {
				throw std::length_error("Matrices shapes mismatch");
			}
			Matrix result(rows, B.getCols());
			int sum;
			for (auto i = 0; i < rows; i++) {
				for (auto j = 0; j < B.getCols(); j++) {
					sum = 0;
					for (auto k = 0; k < rows; k++) {
						sum += this->operator()(i, k) * B(k, j);
					}
					result(i, j) = sum;
				}
			}
			return result;
		}

		Vector<T> operator*(const Vector<T>& B) {
			if (cols != B.getRows()) {
				throw std::length_error("Matrix and Vector shapes mismatch");
			}
			Vector<T> result(rows);
			int sum;
			for (auto i = 0; i < rows; i++) {
				sum = 0;
				for (auto j = 0; j < cols; j++) {
					sum += this->operator()(i, j) * B(j);
				}
				result(i) = sum;
			}
			return result;
		}

		void operator=(const Matrix& B)	{
#ifdef MATRIX_DEBUGGING
			std::cerr << "  MatOperater =" << std::endl;
#endif
			if (&B != this) {
				if (size == B.getSize()) {
					std::memcpy(elements, B.elements, B.getSize() * sizeof(T));
				}
				else {
					delete[] elements;
					elements = new T[B.getSize()];
					std::memcpy(elements, B.elements, B.getSize() * sizeof(T));
				}
				rows = B.getRows();
				cols = B.getCols();
			}
		}


		void show() {
			std::string space=" ";
			for (auto i = 0; i < rows; i++) {
				for (auto j = 0; j < cols; j++) {
					std::cout << std::to_string(elements[i * cols + j]) << space;
				}
				std::cout << std::endl;
			}
			std::cout << "--------------" << std::endl;
		}

		unsigned getRows() const { return rows; }
		unsigned getCols() const { return cols; }
		unsigned getSize() const { return size; }
	};
}

#endif