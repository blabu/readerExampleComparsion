#ifndef BUFFERINTERFACE_H
#define BUFFERINTERFACE_H

template <typename T>
class myVector : public std::vector<T> {
public:
    myVector(std::size_t size):std::vector<T>(size){}
    myVector(const myVector<T>& bytes):std::vector<T>(bytes){}
    myVector(const std::string& str):std::vector<T>(str.size()){
        std::size_t count = 0;
        for(auto it = str.cbegin(); it!= str.cend(); ++it,count++) (*this)[count] = static_cast<T>(*it);

    }

    myVector(const char* c_str):std::vector<T>() {
        std::size_t i =0;
        while(c_str[i] != '\0') {this->push_back(static_cast<unsigned char>(c_str[i])); ++i;}
    }

    myVector():std::vector<T>(){}

    std::size_t find(T elem) const{
        std::size_t position = 0;
        for(auto it = this->cbegin(); it != this->cend(); ++it){
            if(*it == elem) break;
            position++;
        }
        return position;
    }

    myVector<T>& operator+ (const myVector<T>& vect1){
        for(auto it = vect1.cbegin(); it != vect1.cend(); ++it){
            this->push_back(*it);
        }
        return *this;
    }

    myVector<T>& operator+ (const T& elem){
        this->push_back(elem);
        return *this;
    }

    myVector<T>& operator+= (const T& elem){
        this->push_back(elem);
        return *this;
    }

    myVector<T>& operator+= (const myVector<T>& vect){
        for(auto it = vect.cbegin(); it!=vect.cend(); ++it) this->push_back(*it);
        return *this;
    }

    std::string toString() const {
        std::string str;
        for(auto it = this->begin(); it != this->end(); ++it) str.push_back(static_cast<char>(*it));
        return str;
    }

    std::string ToString() const {
    	return std::string(this->cbegin(),this->cend());
    }

    unsigned int toInt() const {
        unsigned int res = 0;
        signed char j = (sizeof(res))<<1;
        for(auto it = this->cbegin(); it != this->cend(); ++it) {
            if(static_cast<char>(*it & 0xFF) >= '0' &&
               static_cast<char>(*it & 0xFF) <= '9') {
                res <<= 4;
                res |= static_cast<char>(*it & 0xFF) - '0';
                j--;
            }
            else if(static_cast<char>(*it & 0xFF) >= 'A' &&
                    static_cast<char>(*it & 0xFF) <= 'F'){
                res <<= 4;
                res |= static_cast<char>(*it & 0xFF)-'A'+10;
                j--;
            }
            else if(res != 0) break;
            if(j<0) break;
        }
        return res;
    }
};

typedef myVector<unsigned char> byteVector;
typedef std::shared_ptr<byteVector> byteVector_ptr;

#endif // BUFFERINTERFACE_H
