#include <stddef.h>
#include <iostream>
class BigInt{
public:
    BigInt() = default;
    BigInt(char* symbols_, size_t length_){
        if (symbols_[0] == '-') {
            isPositive = false;
            length = length_ - 1;
            symbols = new char[length];
            for(int j = 0;j<length;++j ){
                symbols[j] = symbols_[j+1]-'0';
            }
        }
        else{
            isPositive = true;
            length = length_;
            symbols = new char[length];
            for(int j = 0;j<length;++j ){
                symbols[j] = symbols_[j]-'0';
            }
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
        if(((this->isPositive==false)&&(other.isPositive==true)) || ((this->isPositive==true)&&(other.isPositive==false)) ) {
            
        }
        if(((this->isPositive==false)&&(other.isPositive==false)) || ((this->isPositive==true)&&(other.isPositive==true)) ){
            //delete[] this->symbols;
            
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
        }
        
        return *this;
    }

    BigInt& operator-=(const BigInt& other) {
        bool isgreatrer;
        if(this->length == other.length){
            for(int j=0;j<=length-1;j++){
                if(symbols[j] > other.symbols[j]){
                    isgreatrer = true;
                    break;
                }
                else{
                    isgreatrer = false;
                    isPositive = false;
                    break;
                }
            }
        }
        if(this->length > other.length){
            isgreatrer = true;
        }
        if(this->length < other.length){
            std::cout << "this->length < other.length" << std::endl;
            isgreatrer = false;
            isPositive = false;
        }
        int maxLen = std::max(this->length, other.length);
        int carry = 0;
        
        char* result = new char[maxLen];
        int i = this->length - 1;
        int j = other.length - 1;
        int k = maxLen-1;
        
        int sum;
        while (i >= 0 || j >= 0 ) {
          //  std::cout << "i " << i << std::endl;
          //  std::cout << "j " << j << std::endl;
          //  std::cout << "carry " << carry << std::endl;
            int a = (i >= 0) ? this->symbols[i] : 0;
            int b = (j >= 0) ? other.symbols[j] : 0;
            if(isgreatrer == true){
                std::cout << "true"<<std::endl;
                sum = a - b  + carry;
            }
            else{
                std::cout << "false"<<std::endl;
                sum = b - a  + carry;
            }
            std::cout <<"sum: " << sum << std::endl;
            if (sum < 0){
                sum += 10;
                carry = -1;
                //this->symbols[i-1] -= 1;
            }
            else{
                carry = 0;
            }
               // std::cout << "(k!=0)&&(sum!=0)" << std::endl;
            result[k] = sum;
            std::cout<<"k "<<k<<"result[k] " <<(char)(result[k]+'0') <<std::endl;
            std::cout << "carry: " << carry << std::endl;
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
        delete[] this->symbols;
        this->symbols = result;
        if(maxLen >length){
            this->length+=(maxLen-length);
        }
        //++this->length;
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
        int k =1;
        if (isPositive==false){
            std::cout << "-";
        }
        for (int i=0; i<(this->length);++i){
           // std::cout << i<<std::endl;
            if ((this->symbols[i] == 0) && (k == 1)){
            }
            else{
                std::cout <<(char)(this->symbols[i]+'0');
                k = 0;
            }
        }
    }
    
private:
    char * symbols;
    size_t length;
    bool isPositive;
};

int main(){
  //  String s = {"abc",3};
  //  String b = s;
    BigInt s1 = {"18",2};
    BigInt s2 = {"55",2};
    s1 -= s2;
   // std::cout << "hello"<<std::endl;
    s1.Print();
    return 1;
}
