#ifndef VECTOR_H
#define VECTOR_H

namespace atlatec {
	
	template <typename T>
	class Vector {
	private:
		unsigned rows;
		T* elements;

	public:
		Vector(unsigned int rows) : rows(rows) {
#ifdef VECTOR_DEBUGGING
			std::cerr << "VecConstructor initialize" << std::endl;
#endif
			elements = new T[rows];
		}

		Vector(const Vector& B) : rows(B.getRows()) {
#ifdef VECTOR_DEBUGGING
			std::cerr << "VecConstructor copy" << std::endl;
#endif
			elements = new T[B.getRows()];
			std::memcpy(elements, B.elements, B.getRows() * sizeof(T));
		}

		~Vector() {
#ifdef VECTOR_DEBUGGING
			std::cerr << "VecDeconstructor" << std::endl;
#endif
			if (elements) {
				delete[] elements;
			}
		}


		T& operator()(unsigned int row) {
#ifdef VECTOR_DEBUGGING
			std::cerr << "  VecOperater element access" << std::endl;
#endif
			if (row >= rows) {
				throw std::out_of_range("Index out of range");
			}
			return elements[row];
		}

		const T& operator()(unsigned int row) const {
#ifdef VECTOR_DEBUGGING
			std::cerr << "  VecOperater element access" << std::endl;
#endif
			if (row >= rows) {
				throw std::out_of_range("Index out of range");
			}
			return elements[row];
		}

		Vector& operator+=(T scalar) {
#ifdef VECTOR_DEBUGGING
			std::cerr << "  VecOperater scalar +=" << std::endl;
#endif
			for (unsigned int i = 0; i < this->getRows(); i++) {
				elements[i] = elements[i] + scalar;
			}
			return *this;
		}

		Vector& operator*=(T scalar) {
#ifdef VECTOR_DEBUGGING
			std::cerr << "  VecOperater scalar *=" << std::endl;
#endif
			for (unsigned int i = 0; i < this->getRows(); i++) {
				elements[i] = elements[i] * scalar;
			}
			return *this;
		}

		Vector operator+(T scalar) {
#ifdef VECTOR_DEBUGGING
			std::cerr << "  VecOperater scalar +" << std::endl;
#endif
			Vector result(*this);
			result += scalar;
			return result;
		}

		Vector operator*(T scalar) {
#ifdef VECTOR_DEBUGGING
			std::cerr << "  VecOperater scalar *" << std::endl;
#endif
			Vector result(*this);
			result *= scalar;
			return result;
		}

		Vector operator-(T scalar) {
#ifdef VECTOR_DEBUGGING
			std::cerr << "  VecOperater scalar -" << std::endl;
#endif
			Vector result(*this);
			result += -1 * scalar;
			return result;
		}

		void operator=(const Vector& B) {
#ifdef MATRIX_DEBUGGING
			std::cerr << "  MatOperater =" << std::endl;
#endif
			if (&B != this) {
				if (rows == B.getRows()) {
					std::memcpy(elements, B.elements, B.getRows() * sizeof(T));
				}
				else {
					delete[] elements;
					elements = new T[B.getRows()];
					std::memcpy(elements, B.elements, B.getRows() * sizeof(T));
				}
				rows = B.getRows();
			}
		}

		void show() {
			for (auto i = 0; i < rows; i++) {
				std::cout << std::to_string(elements[i]) << std::endl;
			}
			std::cout << "------" << std::endl;
		}

		unsigned getRows() const { return rows; }
	};

}

#endif
