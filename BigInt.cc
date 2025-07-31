#include <stddef.h>
#include <iostream>
class BigInt{
public:
    BigInt() = default;
    BigInt(char* symbols_, size_t length_):length(length_){
        symbols = new char[length];
        for(int j = 0;j<length;++j ){
            symbols[j] = symbols_[j]-'0';
           // std::cout <<symbols[j]+'0'<<" "<<symbols_[j]  << std::endl;
        }
    }
    BigInt(const BigInt& string){
        create_array(string);
    }
    BigInt& operator=(const BigInt& string){
        delete[] symbols;
        create_array(string);
        return *this;
    }
    ~BigInt(){
        delete[] symbols;
    }
    BigInt& operator+=(const BigInt& other) {
        int maxLen = std::max(this->length, other.length);
        int carry = 0;

        char* result = new char[maxLen];
        int i = this->length - 1;
        int j = other.length - 1;
        int k = maxLen-1;

        while (i >= 0 || j >= 0 ) {
            std::cout << "i " << i << std::endl;
            std::cout << "j " << j << std::endl;
            std::cout << "carry " << carry << std::endl;
            int a = (i >= 0) ? this->symbols[i] : 0;
            int b = (j >= 0) ? other.symbols[j] : 0;
            int sum = a + b + carry;
            std::cout <<"sum: " << sum << std::endl;
            carry = sum / 10;
            sum = sum % 10;
            result[k] = sum;
            std::cout<<"k"<<k<<"result[k] " <<(char)(result[k]+'0') <<std::endl;
            std::cout << "carry: " << carry << std::endl;
            k--;
            i--;
            j--;
        }
        std::cout << "carry: " << carry << std::endl;
        int resultLen = maxLen;
        if (carry == 1) {
            std::cout << "huuuu" << std::endl;
            char* newSymbols = new char[maxLen + 1];
            newSymbols[0] = carry;
            std::cout << "newSymbols[0]" <<newSymbols[0]<<std::endl;
            for (size_t i = 0; i < maxLen; ++i){
                newSymbols[i + 1] = (char)(result[i]);
                std::cout << "newSymbols[i + 1]" <<(char)(newSymbols[i + 1]+'0')<<std::endl;
            }
            delete[] this->symbols;
            this->symbols = newSymbols;
            ++this->length;
        }
        else{
            std::cout << "fuuuu" << std::endl;
            delete[] this->symbols;
                  this->symbols = new char[resultLen];
                  for (int m = 0; m < resultLen; ++m)
                      this->symbols[m] = result[m];
                  this->length = resultLen;

            delete[] result;
        }
        
        return *this;
    }

    BigInt& operator-=(const BigInt& other) {
        int maxLen = std::max(this->length, other.length);
        int carry = 0;

        char* result = new char[maxLen];
        int i = this->length - 1;
        int j = other.length - 1;
        int k = maxLen-1;

        while (i >= 0 || j >= 0 ) {
            std::cout << "i " << i << std::endl;
            std::cout << "j " << j << std::endl;
           // std::cout << "carry " << carry << std::endl;
            int a = (i >= 0) ? this->symbols[i] : 0;
            int b = (j >= 0) ? other.symbols[j] : 0;
            int min = a - b;
            if (min<0){
                min  = 10 + a -b;
                this->symbols[i-1] -=1;
            }
            std::cout <<"min: " << min << std::endl;
            result[k] = min;
            k--;
            i--;
            j--;
        }
      /*  std::cout << "carry: " << carry << std::endl;
        int resultLen = maxLen;
        if (carry == 1) {
            std::cout << "huuuu" << std::endl;
            char* newSymbols = new char[maxLen + 1];
            newSymbols[0] = carry;
            std::cout << "newSymbols[0]" <<newSymbols[0]<<std::endl;
            for (size_t i = 0; i < maxLen; ++i){
                newSymbols[i + 1] = (char)(result[i]);
                std::cout << "newSymbols[i + 1]" <<(char)(newSymbols[i + 1]+'0')<<std::endl;
            }
            delete[] this->symbols;
            this->symbols = newSymbols;
            ++this->length;
        }
        else{
            std::cout << "fuuuu" << std::endl;
            delete[] this->symbols;
                  this->symbols = new char[resultLen];
                  for (int m = 0; m < resultLen; ++m)
                      this->symbols[m] = result[m];
                  this->length = resultLen;

            delete[] result;
        }*/
        
        return *this;
    }
    
    void create_array(const BigInt& string){
        this->length = string.length;
        this->symbols = new char[this->length];
        for(int j = 0;j<this->length;++j ){
            symbols[j] = string.symbols[j];
        }
    }
    void Print(){
        //std::cout << "hello"<<std::endl;
        for (int i=0; i<(this->length);++i){
           // std::cout << i<<std::endl;
            std::cout <<(char)(this->symbols[i]+'0');
        }
    }
    
private:
    char * symbols;
    size_t length;
};

int main(){
  //  String s = {"abc",3};
  //  String b = s;
    BigInt s1 = {"14",2};
    BigInt s2 = {"5",1};
   s1 -= s2;
   // std::cout << "hello"<<std::endl;
    s1.Print();
    return 1;
}
